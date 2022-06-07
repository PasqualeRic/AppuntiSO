import sys, os

if __name__ == "__main__":
    path = sys.argv[1]
    count = 0
    for root, dirs, files in os.walk(path):
        for file in files:
            if os.path.islink(os.path.abspath(file)):
                print("sym link found:",file)
            else:
                count = count + 1
        for dir in dirs:
            count = count+ 1
    print("\nfiles count: ",count)