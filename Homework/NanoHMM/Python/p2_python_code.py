from __future__ import print_function

import nanohmm


# This function implements the forward algorithm
def forwardAlgorithm(A, B, p, O):
    # Store useful variables for easier readability
    numStates = len(A)
    T = len(O)

    # 1) Initialization of alpha values
    alpha = []
    for i in range(0, numStates):
        alpha.append([])

    for i in range(0, numStates):
        alpha[i].append(p[i] * B[i][O[i]])

    # 2) Induction step
    for t in range(0, T-1):
        alpha.append([])
        for j in range(0, numStates):
            alpha[j].append(0)
            for i in range(0, numStates):
                alpha[j][t+1] += alpha[i][t] * A[i][j]
            alpha[j][t+1] *= B[j][O[t+1]]

    # 3) Termination
    prob = 0;
    for i in range(0, numStates):
        prob += alpha[i][T-1]

    return alpha, prob


A = [[0.66, 0.34], [1.0, 0.0]]
B = [[0.5, 0.25, 0.25], [0.1, 0.1, 0.8]]
p = [0.8, 0.2]
O = [0, 1, 0, 2, 0, 1, 0]
alpha, prob = forwardAlgorithm(A, B, p, O)
print(str(alpha))
print(prob)

# lambda_ = nanohmm.hmm_t(A, B, p)
#
#
# print("Forward:")
# O = [0, 1, 0, 2, 0, 1, 0]
# f = nanohmm.forward_t(lambda_)
# LL = nanohmm.forward(f, O)
# print(LL)
