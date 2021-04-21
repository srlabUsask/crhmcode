import filecmp
import os
import json
import argparse
from os import listdir

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKCYAN = '\033[96m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'


parser = argparse.ArgumentParser(
    description='Compares CRHM output .obs files to determine if they are consistant across runs.'
)
parser.add_argument('directory')

arguments = parser.parse_args()

# set your obs files directory here
files_dir = arguments.directory

# Get obs files in the directory
files = []
for file in os.listdir(files_dir):
    if file.endswith(".obs"):
        files.append(file)

file_count = len(files)
same_files = []
all_same_files = []

# Compare files and make categories
i = 0
while i < file_count:
    j = 0
    same_files.append(files[i])
    while j < file_count:
        if i != j:
            same = filecmp.cmp(files_dir + files[i], files_dir + files[j])
            if same:
                same_files.append(files[j])
        j+=1
    all_same_files.append(sorted(same_files))
    same_files = []
    i+=1

all_same_files = set(tuple(x) for x in all_same_files)

if len(all_same_files) == 1:
    print("All output files are the same.")
    print(bcolors.OKGREEN + "Test Passed." + bcolors.ENDC)
else:
    print(bcolors.FAIL + "There are differences in output:" + bcolors.ENDC)
    print('There are ', len(all_same_files),' Categories: ')
    for i in all_same_files:
        print(i, 'Length: ', len(i))
    print(bcolors.FAIL + "Test Failed" + bcolors.ENDC)
