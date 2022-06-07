#!/usr/bin/env python3

import os

if __name__ == "__main__":
    l = os.listdir(".")
    l2 = []
    for el in l:
        l2.append(el.split("."))
    l3 = []
    for element in l2:
        l3.append(element[0][::-1])
    l3.sort()
    for element in l3:
        print(element[::-1])

