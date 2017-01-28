#!/usr/bin/python

# Local classes
from User import User
from File import File

# Python packages
import signal, SocketServer, sys
import cPickle as pickle
from threading import Lock

user_map = []
auth_lock = Lock()

users = []
user_lock = Lock()

class ServerHandler(SocketServer.BaseRequestHandler):

  def handle(self):
    auth = self.request.recv(1048576)
    auth = auth.rstrip('\n').split(' ')

    isAuth = False
    with auth_lock:
      if auth[:2] in user_map:
        isAuth = True

    if isAuth:
      self.request.sendall("ok")
      self.createUser(self.request, self.client_address[0], auth[0], auth[2])
      self.serve(self.request, auth)
    else:
      self.request.sendall("gtfo")
      self.request.close()

  def createUser(self, request, addr, name, port):
    data = request.recv(1048576)
    files = pickle.loads(data)
    user = User(name,addr,int(port),files)
    User.printUsers([user])
    with user_lock:
      users.append(user)

  def serve(self, request, auth):
    while True:
      req = request.recv(1048576)
      action = req[:6].rstrip(' ')
      if action == "users":
        self.listUsers(request, auth[0])
      elif action == "files":
        username = req[6:].rstrip(' ')
        self.listFiles(request, username)
      elif action == "discn"  or action == "":
        self.discnUser(request, auth[0])
        return
      elif action == "updat":
        data = req[6:]
        self.updatUser(request, auth[0], data)
      else:
        print "Dafuq is this m8? " + action

  def listUsers(self, request, name):
    with user_lock:
      users_ = [x for x in users if not x.name == name]
      data = pickle.dumps(users_, -1)
      request.sendall(data)

  def listFiles(self, request, name):
    with user_lock:
      files = User.findUser(users, name).files
      data = pickle.dumps(files, -1)
      request.sendall(data)

  def discnUser(self, request, name):
    with user_lock:
      users.remove(User.findUser(users, name))

  def updatUser(self, request, name, data):
    files = pickle.loads(data)
    with user_lock:
      user = User.findUser(users, name)
      user.files = files

class ThreadedServer(SocketServer.ThreadingMixIn, SocketServer.TCPServer):
  pass

def signal_handler(signum, frame):
  print "Exiting..."
  sys.exit(0)

if __name__ == "__main__":

  if len(sys.argv) != 3:
    print "Usage: " + sys.argv[0] + " <ip> <port>"
    sys.exit(1)

  signal.signal(signal.SIGINT, signal_handler)

  user_map_s = open('.passwd', 'r').read()
  user_map_s = user_map_s.split('\n')
  for user in user_map_s:
    user_map.append(user.split(' '))

  HOST = sys.argv[1]
  PORT = int(sys.argv[2])

  server = ThreadedServer((HOST, PORT), ServerHandler)
  server.allow_reuse_address = True
  server.serve_forever()
