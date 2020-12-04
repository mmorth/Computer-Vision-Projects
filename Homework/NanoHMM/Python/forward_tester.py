import numpy as np


def forward(V, a, b, initial_distribution):
    alpha = np.zeros((V.shape[0], a.shape[0]))
    alpha[0, :] = initial_distribution * b[:, V[0]]

    for t in range(1, V.shape[0]):
        for j in range(a.shape[0]):
            # Matrix Computation Steps
            #                  ((1x2) . (1x2))      *     (1)
            #                        (1)            *     (1)
            alpha[t, j] = alpha[t - 1].dot(a[:, j]) * b[j, V[t]]

    return alpha


A = np.array(((0.66, 0.34), (1.0, 0.0)))
B = np.array(((0.5, 0.25, 0.25), (0.1, 0.1, 0.8)))
p = np.array((0.8, 0.2))
O = np.array((0, 1, 0, 2, 0, 1, 0))
alpha = forward(O, A, B, p)
print(alpha)

A = np.array(((0.8, 0.1, 0.1),
              (0.4, 0.2, 0.4),
              (0, 0.3, 0.7)))
B = np.array(((0.66, 0.34, 0),
              (0, 0, 1),
              (0.5, 0.4, 0.1)))
p = np.array((0.6, 0, 0.4))
alpha = forward(O, A, B, p)
print(alpha)

