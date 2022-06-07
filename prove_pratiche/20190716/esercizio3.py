import os
import sys

class File_object(object):
    def __init__(self, content, path):
        self.paths = []
        self.content = content
        self.paths.append(path) 

collectedFiles = []

def dirwalkForContent(rootdir):
    for root, dirs, files in os.walk(rootdir):
        for name in files:
            content = (open(os.path.join(root,name), 'r').read()).decode("UTF-8")
            found = 0
            for elem in collectedFiles:
                if elem.content == content:
                    found = 1
                    elem.paths.append(os.path.join(root,name))
            if found == 0:
                object = File_object(content, os.path.join(root,name))
                collectedFiles.append(object)

if __name__ == "__main__":
    rootdir = sys.argv[1];
    dirwalkForContent(rootdir);

    for elem in collectedFiles:
        if len(elem.paths) >= 2:
            recordedPath = elem.paths[0]
            for i in range(0,len(elem.paths)):
                if i > 0:
                    os.remove(elem.paths[i])
                    os.link(recordedPath, elem.paths[i])


