from os import error
import re


def parse_line(line):
    parts = line.split("|")
    if parts != None:
        return [parts[0].strip().split(" "), parts[1].strip().split(" ")]
    else:
        error("Encountered invalid line: " + str(line))


file = open("input.txt", "r")
lines = list(map(parse_line, file.readlines()))
file.close()

print(lines)
