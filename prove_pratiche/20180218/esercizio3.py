import os, sys

processes = {}

if __name__ == "__main__":
    threshold = int(sys.argv[1])

    dirs = os.listdir("/proc/")
    for dir in dirs:
        if dir.isdigit():
            processes[dir] = len(os.listdir("/proc/"+dir+"/fd/"))  


    for key in processes.keys():
        if(processes[key] > threshold):
            print("proc: ",key," num descrittori: ",processes[key])
