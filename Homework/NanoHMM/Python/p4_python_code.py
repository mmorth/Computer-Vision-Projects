from __future__ import print_function

import nanohmm


# This function implements the backward algorithm
def backwardAlgorithm(A, B, p, O):
    # Store useful variables for easier readability
    numStates = len(A)
    T = len(O)

    # 1) Initialization of beta values
    beta = []
    for i in range(0, numStates):
        beta.append([])
        for j in range(0, T):
            beta[i].append(0)

    for i in range(0, numStates):
        beta[i][T-1] = 1

    # 2) Induction step
    for t in range(T-2, -1, -1):
        for i in range(0, numStates):
            for j in range(0, numStates):
                beta[i][t] += A[i][j] * B[j][O[t+1]] * beta[j][t+1]

    return beta


A = [[0.66, 0.34], [1.0, 0.0]]
B = [[0.5, 0.25, 0.25], [0.1, 0.1, 0.8]]
p = [0.8, 0.2]
O = [0, 1, 0, 2, 0, 1, 0]
beta = backwardAlgorithm(A, B, p, O)
print(str(beta))

# lambda_ = nanohmm.hmm_t(A, B, p)
#
#
# print("Forward:")
# O = [0, 1, 0, 2, 0, 1, 0]
# f = nanohmm.forward_t(lambda_)
# LL = nanohmm.forward(f, O)
# print(LL)
