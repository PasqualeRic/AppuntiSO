import sys
import os



def getNameFromLine(line):
    pos = line.find("__NR_")
    posfinal = line.find(" ",pos) 
    syscall = line[pos+5:posfinal]
    return syscall



if __name__ == "__main__":
    file  = sys.argv[1]

    s = "char *syscall_name[] = {"
    content = (open(file,'r').read()).decode('UTF-8')
    l = content.split("\n")
    l = l[3:len(l)-3]

    i = 0
    for line in l:
        s1 = getNameFromLine(line);
        if i < len(l)-1:
            s += "\n\t"+"\""+str(s1)+"\""
            s += ","
        else:
            s += "\n\t"+"\""+str(s1)+"\""+"\n"
        i += 1
    s+= "}"
    file = open("./syslist.c",'w')
    file.write(s)
