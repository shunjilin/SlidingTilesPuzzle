import os

total_time = 0

for filename in os.listdir("15puzzle_results"):
    if filename == ".DS_Store":
        continue
    file = open(os.path.join("15puzzle_results", filename))
    lines = file.readlines()
    timing = lines[1].split()[0]
    total_time += int(timing)
    print(filename, int(timing) / (1000))

print("total time in s ", total_time / 1000)
