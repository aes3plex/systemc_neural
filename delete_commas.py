with open("dataset1.txt") as infile, open("dataset.txt", "w") as outfile:
    for line in infile:
        outfile.write(line.replace(".0", ""))