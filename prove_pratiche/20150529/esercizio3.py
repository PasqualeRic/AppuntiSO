import sys, os

couples =  []

def getcompressed(lines):
    toret = []
    for line in lines:
        elements = line.split(" ")
        toadd = []
        for elem in elements:
            if(elem != " " and elem != "\t" and elem != "\n" and elem != ""):
                toadd.append(elem)
        toret.append(toadd)
    return toret

if __name__ == "__main__":
    path = sys.argv[1]
    for root,dirs,files in os.walk(path):
        for file in files:
            content = open(os.path.join(root,file),"r")
            lines = content.readlines()
            compressedLines = getcompressed(lines)
            i = 1
            for compressedline in compressedLines[:len(compressedLines)-2]:
                j = i+1
                for compressedline2 in compressedLines[i:]:
                    if(compressedline == compressedline2 and compressedline != []):
                        print(compressedline, compressedline2)
                        couples.append([os.path.join(root,file), i, j])
                    j=j+1
                i = i+1
    
    for element in couples:
        print(element)