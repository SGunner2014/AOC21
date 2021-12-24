# scan for
file = open("sam.txt", "r")
lines = file.readlines()
file.close()

burrows = [[], [], [], []]
desired_burrows = {"A": 0, "B": 1, "C": 2, "D": 3}

for i in range(2, 4):
    line = lines[i]
    burrows[0].insert(0, line[3])
    burrows[1].insert(0, line[5])
    burrows[2].insert(0, line[7])
    burrows[3].insert(0, line[9])

correct = []

for i in range(0, len(burrows)):
    char = burrows[i][0]
    if desired_burrows[char] == i:
        correct.append(char)


print(burrows)
print(correct)
