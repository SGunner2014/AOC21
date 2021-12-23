from os import error
from math import floor


file = open("sam.txt", "r")
lines = file.readlines()
file.close()


def parse_line(line):
    last_type = []
    # (, [, {, <
    counts = [0, 0, 0, 0]
    pairs = {")": "(", "]": "[", "}": "{", ">": "<"}

    for i in range(0, len(line)):
        char = line[i]
        if char == "(":
            last_type.insert(0, char)
        elif char == "[":
            last_type.insert(0, char)
        elif char == "{":
            last_type.insert(0, char)
        elif char == "<":
            last_type.insert(0, char)
        else:
            last_char = last_type.pop(0)
            if pairs[char] != last_char:
                return None
    return last_type


points = {"(": 1, "[": 2, "{": 3, "<": 4}
total = []

for line in lines:
    returned = parse_line(line.strip())
    if returned != None:
        tempScore = 0
        for element in returned:
            tempScore *= 5
            tempScore += points[element]
        total += [tempScore]

total.sort()

print("Total: " + str(total[floor(len(total) / 2)]))
