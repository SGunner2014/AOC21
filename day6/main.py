file = open("input.txt", "r")
line = file.readline()
file.close()

fish = list(map(int, line.split(",")))

daysOld = [0, 0, 0, 0, 0, 0, 0, 0, 0]

for item in fish:
    daysOld[item] += 1


def rotate_fish():
    first = daysOld[0]
    for i in range(0, len(daysOld) - 1):
        daysOld[i] = daysOld[i + 1]
    daysOld[8] = 0
    daysOld[6] += first
    daysOld[8] += first


simLength = int(input("How many days to simulate?: "))

for i in range(0, simLength):
    rotate_fish()

print("Total fish after " + str(simLength) + " days: " + str(sum(daysOld)))
