import os,sys
import subprocess


if __name__ == "__main__":
    homes = {}
    
    data = subprocess.run(["getent", "passwd"], stdout=subprocess.PIPE)
    s = data.stdout.decode('ascii')
    l = s.split("\n")
    for field in l:
        pos = field.find("/home/")
        if pos == -1:
            continue
        pos2 = field.find("/", pos+6)
        subdir = field[pos:pos2]
        homes.setdefault(subdir, 0)     #se esiste ok, altrimenti crea e setta a 0
        homes[subdir] += 1
    for key, val in homes.items():
        print(key+"\t"+str(val))