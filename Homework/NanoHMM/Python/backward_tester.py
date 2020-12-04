import numpy as np


def backward(V, a, b):
    beta = np.zeros((V.shape[0], a.shape[0]))

    # setting beta(T) = 1
    beta[V.shape[0] - 1] = np.ones((a.shape[0]))

    # Loop in backward way from T-1 to
    # Due to python indexing the actual loop will be T-2 to 0
    for t in range(V.shape[0] - 2, -1, -1):
        for j in range(a.shape[0]):
            beta[t, j] = (beta[t + 1] * b[:, V[t + 1]]).dot(a[j, :])

    return beta


A = np.array(((0.66, 0.34), (1.0, 0.0)))
B = np.array(((0.5, 0.25, 0.25), (0.1, 0.1, 0.8)))
O = np.array((0, 1, 0, 2, 0, 1, 0))
beta = backward(O, A, B)
print(beta)

A = np.array(((0.8, 0.1, 0.1),
              (0.4, 0.2, 0.4),
              (0, 0.3, 0.7)))
B = np.array(((0.66, 0.34, 0),
              (0, 0, 1),
              (0.5, 0.4, 0.)))
beta = backward(O, A, B)
print(beta)
