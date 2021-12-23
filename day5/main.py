from os import error
import re

file = open("input.txt", "r")
lines = file.readlines()
file.close()


# Parse this line of input using regex
def convert_line(line):
    toReturn = []

    matches = re.match(r"([0-9]+),([0-9]+) -> ([0-9]+),([0-9]+)", line)
    if matches != None:
        toReturn.append(int(matches.group(1)))
        toReturn.append(int(matches.group(2)))
        toReturn.append(int(matches.group(3)))
        toReturn.append(int(matches.group(4)))
    else:
        error("Cannot parse line: " + str(line))
    return toReturn


# Is the line diagonal?
def is_not_diagonal(line):
    return line[0] == line[2] or line[1] == line[3]


lines = list(map(convert_line, lines))
grid = dict()

for line in lines:
    if line[0] == line[2]:  # Is this a horizontal line?
        if line[1] <= line[3]:
            yS = line[1]
            yF = line[3]
        else:
            yS = line[3]
            yF = line[1]
        x = line[0]
        for y in range(yS, yF + 1):
            if (x, y) in grid:
                grid[(x, y)] += 1
            else:
                grid[(x, y)] = 0
    elif line[1] == line[3]:  # Is this a vertical line?
        y = line[1]
        if line[0] <= line[2]:
            xS = line[0]
            xF = line[2]
        else:
            xS = line[2]
            xF = line[0]
        for x in range(xS, xF + 1):
            if (x, y) in grid:
                grid[(x, y)] += 1
            else:
                grid[(x, y)] = 0
    else:  # Is this a diagonal line?
        if line[0] > line[2]:
            xPoints = list(range(line[0], line[2] - 1, -1))
        else:
            xPoints = list(range(line[0], line[2] + 1))
        if line[1] > line[3]:
            yPoints = list(range(line[1], line[3] - 1, -1))
        else:
            yPoints = list(range(line[1], line[3] + 1))
        for i in range(len(xPoints)):
            x = xPoints[i]
            y = yPoints[i]
            if (x, y) in grid:
                grid[(x, y)] += 1
            else:
                grid[(x, y)] = 0


count = 0

for key, value in grid.items():
    if value > 0:
        count += 1

print(count)
