import numpy as np
import matplotlib.pyplot as plt
import re


def get_cmap(n, name='hsv'):
    '''Returns a function that maps each index in 0, 1, ..., n-1 to a distinct
    RGB color; the keyword argument name must be a standard mpl colormap name.'''
    return plt.cm.get_cmap(name, n)


arr = np.array([])
xs = np.array([])
ys = np.array([])
color_ids = np.array([])

with open('normal_output.txt') as f:
    for line in f:
        # line is in format: 1.23   4.56    7
        nums = re.split(r'\t+', line.rstrip('\t\n'))
        x = float(nums[0])
        y = float(nums[1])
        color_id = float(nums[2])
        xs = np.append(xs, x)
        ys = np.append(ys, y)
        color_ids = np.append(color_ids, color_id)

for j in range(len(xs)):
    plt.plot(xs[j], ys[j])

plt.scatter(xs, ys, c=color_ids)
plt.savefig('normal_clusters.png')
