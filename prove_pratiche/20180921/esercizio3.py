import os
import sys


def dirwalk(path):
    for root, dirs, files in os.walk(path):
        for name in files:
            content = (open(os.path.join(root,name)).read()).decode("UTF-8")
            l = content.split("\n")
            if l[0].find("#!") == 0:
                if l[0] in dict:
                    dict.get(l[0]).append(os.path.join(root,name))
                else:
                    dict[l[0]] =  [os.path.join(root,name)]

dict = {}

if __name__ == "__main__":
    path = sys.argv[1]
    dirwalk(path)
    for key,elem in dict.items():
        print(key, elem)