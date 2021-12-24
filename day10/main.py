def process_line(line):
    return list(map(int, [char for char in line.strip()]))


file = open("input.txt", "r")
lines = list(map(process_line, file.readlines()))
file.close()

print(lines)
