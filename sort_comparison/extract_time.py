import sys

# python extract_time.py out/clang.debug.make/time.txt | xclip -sel clip

time_file = sys.argv[1]

with open(time_file, 'r') as f:
    lines = f.readlines()
    
# get lines after line starting with "Benchmark"
index = 0
for line in lines:
    if line.startswith("Benchmark"):
        break
    index += 1
    
lines = lines[index+2:]

# print(lines)
times = [
    # two digit precision
    # ns -> ms
    float(line.split()[1]) / 1000000
    for line in lines
]
times = [str(round(time, 2)).replace(".",",") for time in times]

print("\t".join(times))