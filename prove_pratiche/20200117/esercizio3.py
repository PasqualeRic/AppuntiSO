import sys, subprocess

if __name__ == "__main__":
    s = " ".join(sys.argv[1:])
    cmdl = s.split("//")
    children = []
    for cmd in cmdl:
        l = cmd.split(" ")
        for el in l:
            if el == "":
                l.remove(el)
        print("l: ",l,"\n")
        p = subprocess.Popen(l)
        children.append(p)

    for child in children:
        child.wait()
