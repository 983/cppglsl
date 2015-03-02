#!/usr/bin/python2

import re, os, sys

def fix_out(s):
    s = re.sub("inout\s", "out ", s)

    def repl(s):
        return s.group(1) + "INOUT(" + s.group(2) + ") "

    # one char that is not variable name
    # out
    # whitespaces
    # a variable name
    # whirespace
    pattern = "([^a-zA-Z0-9])out\s+([a-zA-Z0-9]+)\s"

    return re.sub(pattern, repl, s)

if __name__ == "__main__":
    n = len(sys.argv)

    if n != 3:
        print "usage: ./fix_out.py input.hpp output.hpp"
    else:
        f = open(sys.argv[1])
        src = f.read()
        f.close()
        
        dst = fix_out(src)
        
        f = open(sys.argv[2], "w")
        f.write(dst)
        f.close()
    