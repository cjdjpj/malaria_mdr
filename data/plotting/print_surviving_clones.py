import csv

file_path = '../g_freqs.csv'

with open(file_path, newline='') as csvfile:
    reader = csv.reader(csvfile)
    data = list(reader)

last_row = data[-1]

print("Surviving clones (at last gen):")
for clone_num, frequency in enumerate(last_row):
    if float(frequency) > 0.005:
        print(f"Clone {clone_num}: {frequency}")
