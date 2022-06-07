from posixpath import abspath
import sys, os
import time
import stat
from shutil import move


files1 = []
files2 = []

if __name__ == "__main__":
    path1 = sys.argv[1]
    path2 = sys.argv[2]
    dest = sys.argv[3]

    for root,dirs,files in os.walk(path1):
        for file in files:
            files1.append(abspath(os.path.join(path1,file)))
    for root2,dirs2,files_2 in os.walk(path2):
        for file in files_2:
            if abspath(os.path.join(path1,file)) in files1:
                stat1 = os.stat(os.path.join(path1,file))
                stat2 = os.stat(os.path.join(path2,file))
                if time.ctime(stat1 [ stat.ST_MTIME ]) < time.ctime(stat2 [ stat.ST_MTIME ]):
                    files1.remove(abspath(os.path.join(path1,file)))
                    files2.append(abspath(os.path.join(path2,file)))
            else:
                files2.append(abspath(os.path.join(path2,file)))
    print(files1)
    print(files2)
    for element in files1:
        move(element, dest)
    for element in files2:
        move(element, dest)
