import numpy as np


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


# This function implements the backward algorithm
def backwardAlgorithm(A, B, O):
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


# Compute the Likelihood for each time segment for Part 7
O1 = [1, 0, 0, 0, 1, 0, 1]
O2 = [0, 0, 0, 1, 1, 2, 0]
O3 = [1, 1, 0, 1, 0, 1, 2]
O4 = [0, 1, 0, 2, 0, 1, 0]
O5 = [2, 2, 0, 1, 1, 0, 1]
A = [[0.6, 0.4],
     [1, 0]]
B = [[0.7, 0.3, 0],
     [0.1, 0.1, 0.8]]
p = [0.7, 0.3]
print("\tt=1\t\t\t\t\t\t\tt=2\t\t\t\t\t\tt=3\t\t\t\t\t\tt=4\t\t\t\t\t\t\tt=5\t\t\t\t\t\tt=6\t\t\t\t\t\t\tt=7")
alpha, prob = forwardAlgorithm(A, B, p, O1)
beta = backwardAlgorithm(A, B, O1)
likelihood = np.array(alpha).transpose().dot(np.array(beta))[len(O1)-1]
print("O1\tL={}\tL={}\tL={}\tL={}\tL={}\tL={}\tL={}".format(likelihood[0], likelihood[1], likelihood[2], likelihood[3], likelihood[4], likelihood[5], likelihood[6]))

alpha, prob = forwardAlgorithm(A, B, p, O2)
beta = backwardAlgorithm(A, B, O2)
likelihood = np.array(alpha).transpose().dot(np.array(beta))[len(O2)-1]
print("O2\tL={}\tL={}\tL={}\tL={}\tL={}\tL={}\tL={}".format(likelihood[0], likelihood[1], likelihood[2], likelihood[3], likelihood[4], likelihood[5], likelihood[6]))

alpha, prob = forwardAlgorithm(A, B, p, O3)
beta = backwardAlgorithm(A, B, O3)
likelihood = np.array(alpha).transpose().dot(np.array(beta))[len(O3)-1]
print("O3\tL={}\tL={}\tL={}\tL={}\tL={}\tL={}\tL={}".format(likelihood[0], likelihood[1], likelihood[2], likelihood[3], likelihood[4], likelihood[5], likelihood[6]))

alpha, prob = forwardAlgorithm(A, B, p, O4)
beta = backwardAlgorithm(A, B, O4)
likelihood = np.array(alpha).transpose().dot(np.array(beta))[len(O4)-1]
print("O4\tL={}\tL={}\tL={}\tL={}\tL={}\tL={}\tL={}".format(likelihood[0], likelihood[1], likelihood[2], likelihood[3], likelihood[4], likelihood[5], likelihood[6]))

alpha, prob = forwardAlgorithm(A, B, p, O5)
beta = backwardAlgorithm(A, B, O5)
likelihood = np.array(alpha).transpose().dot(np.array(beta))[len(O5)-1]
print("O5\tL={}\tL={}\tL={}\tL={}\tL={}\tL={}\tL={}".format(likelihood[0], likelihood[1], likelihood[2], likelihood[3], likelihood[4], likelihood[5], likelihood[6]))
