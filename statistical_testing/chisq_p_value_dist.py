# Must have the 'ent' randomness tester utility installed
# https://www.fourmilab.ch/random/

import os
import subprocess
import sys

from matplotlib import pyplot

if __name__ == "__main__":
    rand_bytes_filename = sys.argv[1]
    num_bytes = sys.argv[2]

    subprocess.run(['split', '-b', num_bytes, rand_bytes_filename, 'split_rand_'])

    split_rand_filenames = [x for x in os.listdir('.') if x[:11] == 'split_rand_']

    print(len(split_rand_filenames))

    num_list = []

    for filename in split_rand_filenames:
        cmd_out = subprocess.run(['ent', filename],stdout=subprocess.PIPE, encoding='ISO-8859-1').stdout
        line = cmd_out.split('\n')[6]
        num = float(line.split(' ')[4])
        num_list.append(num)

    for filename in split_rand_filenames:
        subprocess.run(['rm', filename])

    fig, ax = pyplot.subplots(1)
    ax.hist(num_list, range=(0.0, 100.0), density=True)

    pyplot.savefig('phist.png')
