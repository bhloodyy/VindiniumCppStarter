#!/usr/bin/python

import os
import sys
import re
from pathlib import Path

currentPath = sys.argv[1]
paths = [currentPath+"/", currentPath+"/inc/", currentPath+"/src/", currentPath+"/util/"]
includes = []

def include(inputFileName):
    if inputFileName not in includes:
        includes.append(inputFileName)
        for path in paths:
            if os.path.isfile(os.path.join(path, inputFileName)):
                with open(os.path.join(path, inputFileName), 'r') as inputFile:
                    data = inputFile.read()
                data = re.sub("#include \"(.*?)\"", lambda match: include(os.path.basename(match.group(1))) + include(os.path.basename(os.path.splitext(match.group(1))[0]) + ".cpp"), data)
                return data
    return ""

result = include(currentPath+"/src/main.cpp")

with open(currentPath+"/bin/bundled.cpp", 'w') as outFile:
    outFile.write("#pragma GCC optimize \"Ofast,omit-frame-pointer,inline\"\n")
    outFile.write(result)
