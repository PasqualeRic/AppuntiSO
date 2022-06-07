#!/usr/bin/env python3

import subprocess

if __name__ == "__main__":
    while True:
        try:
            cmd = input()
            if cmd == "logout":
                print("Exiting...")
                exit(1)
            args = cmd.split(" ")
            subprocess.run(args, shell=False)
        except EOFError:
            print("Exiting...")
            exit(1)