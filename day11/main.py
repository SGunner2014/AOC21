from typing import Dict


def parse_line(line):
    return list(map(int, [char for char in line.strip()]))


file = open("sam.txt", "r")
lines = list(map(parse_line, file.readlines()))
file.close()

max_x = len(lines) - 1
max_y = len(lines[0]) - 1

flash_count = 0


# Prints the grid in an easy-to-read format
def print_grid():
    for i in range(0, len(lines)):
        print("".join(list(map(str, lines[i]))))


# Increases all local values near this position
def increase_local_values(x, y):
    for i in range(max(0, x - 1), min(max_x + 1, x + 2)):
        for j in range(max(0, y - 1), min(max_y + 1, y + 2)):
            if lines[i][j] != 0:
                lines[i][j] += 1


# Handles one location increase
def handle_flash(x, y):
    global flash_count
    flash_count += 1

    for i in range(max(0, x - 1), min(max_x + 1, x + 2)):
        for j in range(max(0, y - 1), min(max_y + 1, y + 2)):
            if lines[i][j] > 9:
                increase_local_values(i, j)
                lines[i][j] = 0
                handle_flash(i, j)


# Simulates one round of increases
def simulate_round():
    count = flash_count
    # First, increase all locations by 1
    for i in range(0, len(lines)):
        for j in range(0, len(lines[i])):
            lines[i][j] += 1

    # Then, perform a pass over the values and handle any flashes
    for i in range(0, len(lines)):
        for j in range(0, len(lines[i])):
            if lines[i][j] > 9:
                increase_local_values(i, j)
                lines[i][j] = 0
                handle_flash(i, j)

    for i in range(0, len(lines)):
        for j in range(0, len(lines[i])):
            if lines[i][j] != 0:
                return None

    if flash_count - count == (max_x + 1) * (max_y + 1):
        return True
    return None


print_grid()
for i in range(0, 200000):
    result = simulate_round()
    print("")
    print_grid()
    if result != None:
        break

print("Flash count: " + str(flash_count))
print("First round: " + str(i + 1))
