import os

total_time = 0
search_time = 0
total_probes = 0

RESULT_FOLDER = "./twentyfour_thread_result"

solution_lenghts = []

for filename in os.listdir(RESULT_FOLDER):
    if filename == ".DS_Store":
        continue
    file = open(os.path.join(RESULT_FOLDER, filename))
    lines = file.readlines()
    initialize_timing = lines[0].split()[0]
    timing = lines[1].split()[0]
    probes = lines[5].split()[-1]
    total_time += int(timing)
    search_time += int(timing) - int(initialize_timing)
    total_probes += int(probes)
    solution_length = int(lines[7].split()[-1])
    solution_lenghts.append(solution_length)
    print(filename, int(timing) / (1000), " solution length " , solution_length)

print("total time in s ", total_time / 1000)
print("search time in s ", search_time / 1000)
print("total probes to closed list ", total_probes)
