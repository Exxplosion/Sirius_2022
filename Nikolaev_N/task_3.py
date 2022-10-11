import matplotlib.pyplot as plt
import numpy as np



def load_array_from_file(filepath : str):
    result = []

    with open(filepath, 'r') as f:
        data = f.read()
        rows = data.split('\n')

        for row in rows:
            row = row.strip()
            if len(row) == 0:
                continue
            elems = row.split(' ')
            result += [[float(e) for e in elems]]

    return result

def make_plot(array : np.array, x_y_atack, R):
    fig, ax = plt.subplots(figsize=(18, 18))

    ax.scatter(array[:, 0], array[:, 1])
    circle = plt.Circle((x_y_atack[1], x_y_atack[2]), R, color='r', alpha=0.25)
    ax.add_patch(circle)
    get_red_points(array, x_y_atack[1], x_y_atack[2], R, ax)
    plt.axis('scaled')
    plt.show()
    plt.savefig('targets_grid.png')

def max_cot_get(array : np.array, i_x, j_y):
    max_cost = 0
    for (i, j, v) in (array):
        if np.sqrt((i - i_x)**2 + (j - j_y)**2) <= R:
            max_cost += v
        else:
            continue
    return [max_cost, i_x, j_y]


def get_red_points(array: np.array, i_x, j_y, R, ax):
    for (i, j, v) in (array):
        if np.sqrt((i - i_x)**2 + (j - j_y)**2) <= R:
            ax.scatter(i, j, color = 'r')
        else:
            continue


array_targets = np.array(load_array_from_file('./targets.txt'))


R = np.float64(10.)

maxes_cost = [[]]
for i_x in np.arange(0, 100.5, 1):
    for j_y in np.arange(0, 100.5, 1):
        maxes_cost.append(max_cot_get(array_targets, i_x, j_y))

max_cost_i = np.argmax(maxes_cost, axis = 0)

make_plot(array_targets, maxes_cost[max_cost_i], R)


print(maxes_cost[max_cost_i])