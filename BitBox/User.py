#!/usr/bin/python

class User():
  def __init__(self, name, ip, port, files):
    self.name = name
    self.ip = ip
    self.port = port
    self.files = files

  def __str__(self):
    return self.name + "-> " + self.ip + ":" +str(self.port)

  @staticmethod
  def findUser(users, username):
    for user in users:
      if user.name == username:
        return user
    return None

  @staticmethod
  def printUsers(users):
    for user in users:
      print user
