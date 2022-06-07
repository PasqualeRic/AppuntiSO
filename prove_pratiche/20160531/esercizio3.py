import os, sys
import subprocess

if __name__ == "__main__":
    path = sys.argv[1]
    j = 0
    children = []
    for file in os.listdir(path):
        words = file.split(".")
        if words[len(words)-1].isnumeric(): 
            print(j+1,"started with pid:" )
            p=subprocess.Popen(["sleep",str(0.001 * int(words[len(words)-1]))])
            print(p.pid)
            children.append(p)
            j=j+1
    for c in children:
        (pid,status) = os.wait()
        print("finished: ", pid)
