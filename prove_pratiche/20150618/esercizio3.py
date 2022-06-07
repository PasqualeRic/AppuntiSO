import sys, os

paths = {}

if __name__ == "__main__":
    path = sys.argv[1]
    paths["excec"] = []
    for root, dirs, files in os.walk(path):
        for file in files:
            lines = (open(os.path.join(root,file), "r")).readlines()
            if (lines != []):
                pos = lines[0].find("#!")
                if(pos != -1):
                    foundPath = lines[0][pos+2:]
                    if(foundPath in paths):
                        paths.get(foundPath).append(os.path.join(root,file)) 
                    else:    
                        paths[foundPath] = [os.path.join(root,file)]
                else:
                    paths.get("excec").append(os.path.join(root,file)) 
            else:
                paths.get("excec").append(os.path.join(root,file))

    for key, elem in paths.items():
        print(key,len(elem))
                    