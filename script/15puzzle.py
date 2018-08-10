# run all 15 puzzle instances

import subprocess
import os
import shutil

FIFTEEN_PUZZLE_RESULTS_FOLDER = "15puzzle_results"
FIFTEEN_PUZZLE_FOLDER = "./Korf100/"

if os.path.basename(os.getcwd()) != "script":
    print("Script is running in the wrong folder!")
    exit()

if os.path.exists(FIFTEEN_PUZZLE_RESULTS_FOLDER):
    # remove folder if exists
    shutil.rmtree(FIFTEEN_PUZZLE_RESULTS_FOLDER)

os.makedirs(FIFTEEN_PUZZLE_RESULTS_FOLDER)

ignore_files = ['prob059', 'prob081', 'prob087']

for filename in os.listdir(FIFTEEN_PUZZLE_FOLDER):
    if (filename in ignore_files):
        print(filename, "ignored")
        continue
    file = open(os.path.join(FIFTEEN_PUZZLE_FOLDER, filename))
    lines = file.readlines()
    initial_state = lines[1]  # read initial states

    output_filename = os.path.join(FIFTEEN_PUZZLE_RESULTS_FOLDER, filename)
    output_file = open(output_filename, "w")
    subprocess.call(["../build/src/Solver", "-s", "astar",
                     "-i", initial_state], stdout=output_file)
