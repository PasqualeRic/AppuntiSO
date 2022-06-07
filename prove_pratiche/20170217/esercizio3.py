import os

allFiles = {}

if __name__ == "__main__":
    path = "./"
    for root, dirs, files in os.walk(path):
        for file in files:
            list = file.split(".")
            if len(list) == 1:
                if "none" in allFiles:
                    allFiles.get("none").append(file)
                else:
                    allFiles["none"] = [file]
            else:
                if list[len(list)-1] in allFiles:
                    allFiles.get(list[len(list)-1]).append(file) 
                else:
                    allFiles[list[len(list)-1]] = [file]
    
    for key,elem in allFiles.items():
        if key != "none":
            print("suffisso: ",key," files: ", elem)
    print("\n")
    print("senza suffisso: ", allFiles.get("none"))