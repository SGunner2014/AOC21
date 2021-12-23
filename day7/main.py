from math import floor

file = open("input.txt", "r")
positions = list(map(int, file.readline().split(",")))
file.close()

positions.sort()
# best_pos = positions[int(len(positions) / 2)]
best_pos = floor(sum(positions) / len(positions))

total_fuel = 0

for pos in positions:
    diff = abs(best_pos - pos)
    if diff <= 1:
        total_fuel += diff
        continue
    total_fuel += int((diff * (diff + 1)) / 2)

print("Total fuel used: " + str(total_fuel))
