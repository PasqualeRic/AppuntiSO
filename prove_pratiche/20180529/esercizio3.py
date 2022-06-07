import os

if __name__ == "__main__":
    dirs = os.listdir("/proc/")
    for dir in dirs:
        if dir.isdigit():
            content = open("/proc/"+dir+"/status","r")
            lines = content.readlines()
            numbers = []
            pid = ""
            for line in lines:
                pid = dir
                if "Uid:" in line:
                    for word in line.split():
                        if word != "Uid:":
                            numbers.append(int(word))

            if max(numbers)>0:
                print (pid," ", numbers)
