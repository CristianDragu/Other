#!/usr/bin/python

# Local classes
from File import File
from User import User

# Python packages
from threading import Thread, Lock
import sys, os, socket, signal, SocketServer
import cPickle as pickle

s = None
users = []
user_files = []
transfers = []
p2pserver = None
dest_dir = ""

# Client - Server functions
def connect(host):
  HOST = host
  PORT = 4242
  global s
  s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
  s.connect((HOST, PORT))
  return s

def auth(username, passw, port):
  s.sendall(username + " " + passw + " " + str(port))
  res = s.recv(4)
  if res == "ok":
    return True
  else:
    return False

def getUsers():
  global users
  s.sendall("users")
  data = s.recv(1048576)
  users = pickle.loads(data)
  return users

def getFiles(user):
  s.sendall("files " + user)
  data = s.recv(1048576)
  files = pickle.loads(data)
  return files

def setFiles(path):
  user_files = File.getFileStruct(None, path)

def discn():
  s.sendall("discn")
  server_closer = ServerInitializer(1,p2pserver)
  server_closer.start()
  server_closer.join()

def updateFiles():
  data = pickle.dumps(user_files,-1)
  s.sendall("updat " + data)

def comm():
  global users
  while True:
    inp = raw_input("Enter desired command:\n")
    inp = inp.rstrip('\n')
    if inp == "users":
      users = getUsers()
      User.printUsers(users)
    elif inp == "files":
      username = raw_input("Enter username:").rstrip('\n')
      files = getFiles(username)
      findUser(users, username).files = files
      File.printFiles(files)
    elif inp == "discn":
      discn()
      return
    elif inp == "updat":
      updateFiles()
    elif inp == "transfer":
      startTransfer()
    else:
      print "Dafuq is this m8?"

# Peer-to-Peer server
class ServerHandler(SocketServer.BaseRequestHandler):
  def handle(self):
    filename = self.request.recv(1048576).rstrip('\n')
    file = open(filename, 'r')
    while True:
      chunk = file.read(4096)
      if chunk == "":
        break
      self.request.sendall(chunk)


class ThreadedServer(SocketServer.ThreadingMixIn, SocketServer.TCPServer):
  pass

class ServerInitializer(Thread):
  def __init__(self, mode, port=0, o_server=None):
    super(ServerInitializer, self).__init__()
    self.mode = mode
    self.port = port
    self.o_server = o_server

  def run(self):
    if self.mode == 0:
      global p2pserver
      HOST = '0'
      PORT = self.port
      p2pserver = ThreadedServer((HOST, PORT), ServerHandler)
      p2pserver.allow_reuse_address = True
      p2pserver.serve_forever()
      print "Server down..."
    elif self.mode == 1:
      print "Closing server..."
      self.o_server.shutdown()

# Peer-to-Peer client
def startTransfer():
  global users
  global transfers
  getUsers()
  User.printUsers(users)
  username = raw_input("From which user?").rstrip('\n')
  user = User.findUser(users, username)
  File.printFiles(user.files)
  filename = raw_input("Which file?").rstrip('\n')
  file = File.findFile(user.files, filename)
  transfer = Transfer(user, file)
  transfers.append(transfer)
  transfer.start()

class Transfer(Thread):
  def __init__(self, user, file):
    super(Transfer, self).__init__()
    self.user = user
    self.file = file
    self.progress = 0
    self.total = file.size
    self.data_lock = Lock()
  def getProgress(self):
    with self.data_lock:
      progress = (float(self.progress)/float(self.total))
    return float(progress)
  def run(self):
    HOST = self.user.ip
    PORT = int(self.user.port)
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((HOST, PORT))
    s.sendall(self.file.name)

    file = open(os.path.join(dest_dir,os.path.basename(self.file.name)), 'w')

    done = False
    while not done:
      chunk = s.recv(4096)
      self.progress += len(chunk)
      file.write(chunk)
      with self.data_lock:
        if not self.progress < self.total:
          done = True

    file.close()
    s.close()
    #self.join()


def signal_handler(signum, frame):
  print "Exiting..."
  try:
    server_closer = ServerInitializer(1,o_server=p2pserver)
    server_closer.start()
    server_closer.join()
  except AttributeError:
    pass
  sys.exit(0)

if __name__ == "__main__":

  if len(sys.argv) != 7:
    print "Usage: " + sys.argv[0] + " <server-ip> <user> <pass> <dir> <dest-dir> <local-port>"
    sys.exit(1)

  signal.signal(signal.SIGINT, signal_handler)

  s = connect(sys.argv[1])

  if not auth(sys.argv[2], sys.argv[3], sys.argv[6]):
    print "Authentication failed..."
    sys.exit(0)

  user_files = File.getFileStruct(None, sys.argv[4])
  File.printFiles(user_files)
  
  s.sendall(pickle.dumps(user_files,-1))

  dest_dir = sys.argv[5]
  server_init = ServerInitializer(0, int(sys.argv[6]))
  server_init.start()
  comm()
