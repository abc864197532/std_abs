import sys

filename = sys.argv[1]
minlength = 0
linenumber = 0
exitcode = 0
f = open(filename, "r")

for line in f:
    length = 0
    linenumber += 1
    for i in range(len(line)):
        if line[i] == '\t':
            print("%s line %d: tab found!" % (filename, linenumber))
            exitcode = 1
        if line[i] != ' ':
            break
        length += 1
    if length == 0:
        continue
    if minlength == 0 or length < minlength:
        minlength = length
    if length % 2 == 1:
        print("%s line %d: space width is odd!" % (filename, linenumber))
        exitcode = 1

if minlength != 0 and minlength != 2:
    print("%s: minimum space width is not 2!" % (filename))
    exitcode = 1

sys.exit(exitcode)