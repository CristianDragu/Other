#!/usr/bin/python

import os
from stat import *

class File():
  def __init__(self, name, size):
    self.name = name
    self.size = size
    self.files = []

  def __str__(self):
    return "{" + self.name + ", " + str(self.size) + "}"

  @staticmethod
  def printFiles(files):
    for file in files:
      print file
      if not file.files == []:
        File.printFiles(file.files)

  @staticmethod
  def findFile(files, filename):
    for file in files:
      if file.name == filename:
        return file
    return None

  @staticmethod
  def getFileStruct(rec_dir, dirname):
    files = []
    for file in os.listdir(dirname):
      pathname = os.path.join(dirname, file)
      stat = os.stat(pathname)
      mode = stat.st_mode
      cur_file = File(pathname, stat.st_size)
      if S_ISDIR(mode):
          File.getFileStruct(cur_file, pathname)
      files.append(cur_file)

    if rec_dir is not None:
      rec_dir.files = files
      return []
    else:
      return files