import os
import sys

class Obj(object):

    def __init__(self,path,length):
        self.path = path
        self.length = length

filesLength = []

def dirwalkToCount(rootdir):
    for root, dirs, files in os.walk(rootdir):
        for filename in files:
            if ".c" in filename or ".mk" in filename or ".h" in filename:
                content = (open(os.path.join(root,filename), 'r').read()).decode("UTF-8")
                content = str(content)
                length = len(content)
                filesLength.append(Obj(os.path.join(root,filename),length))

if __name__ == "__main__":
    rootdir = sys.argv[1]
    dirwalkToCount(rootdir)
    for elem in filesLength:
        print("path: ",elem.path, "length: ", elem.length)
    tot = 0
    for elem in filesLength:
        if ".c" in elem.path:
            tot += elem.length
    print("c files total length: ", tot)
    tot = 0
    for elem in filesLength:
        if ".mk" in elem.path:
            tot += elem.length
    print("mk files total length: ", tot)
    tot = 0
    for elem in filesLength:
        if ".h" in elem.path:
            tot += elem.length
    print("h files total length: ", tot)
