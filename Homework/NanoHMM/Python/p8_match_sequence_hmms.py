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


# Compute the likelihood for each sequence
O1 = [1, 0, 0, 0, 1, 0, 1]
O2 = [0, 0, 0, 1, 1, 2, 0]
O3 = [1, 1, 0, 1, 0, 1, 2]
O4 = [0, 1, 0, 2, 0, 1, 0]
O5 = [2, 2, 0, 1, 1, 0, 1]
Os = [O1, O2, O3, O4, O5]
s1 = []
s2 = []
s3 = []
s4 = []
s5 = []
seqs = [s1, s2, s3, s4, s5]

# HMM 1:
A = [[1.0, 0.0], [0.5, 0.5]]
B = [[0.4, 0.6, 0.0], [0.0, 0.0, 1.0]]
p = [0.0, 1.0]
for i in range(0, len(Os)):
    alpha, prob = forwardAlgorithm(A, B, p, Os[i])
    seqs[i].append(prob)

# HMM 2:
A = [[0.25, 0.75], [1.0, 0.0]]
B = [[0, 1.0, 0], [0.66, 0.0, 0.34]]
p = [1.0, 0.0]
for i in range(0, len(Os)):
    alpha, prob = forwardAlgorithm(A, B, p, Os[i])
    seqs[i].append(prob)

# HMM 3:
A = [[0.0, 1.0], [1.0, 0.0]]
B = [[1.0, 0.0, 0.0], [0.0, 0.66, 0.34]]
p = [1.0, 0.0]
for i in range(0, len(Os)):
    alpha, prob = forwardAlgorithm(A, B, p, Os[i])
    seqs[i].append(prob)

# HMM 4:
A = [[1, 0], [0.44, 0.56]]
B = [[0.36, 0.42, 0.22], [1.0, 0, 0]]
p = [0, 1.0]
for i in range(0, len(Os)):
    alpha, prob = forwardAlgorithm(A, B, p, Os[i])
    seqs[i].append(prob)

# HMM 5:
A = [[0.0, 1.0], [1.0, 0.0]]
B = [[0.25, 0.75, 0.0], [1.0, 0.0, 0.0]]
p = [1.0, 0.0]
for i in range(0, len(Os)):
    alpha, prob = forwardAlgorithm(A, B, p, Os[i])
    seqs[i].append(prob)

# Determine max of each sequence
maxIndices = []
for seq in seqs:
    maxIndices.append(np.argmax(np.array(seq)))

# Print results
print("\tHMM1\t\t\tHMM2\t\t\tHMM3\t\t\tHMM4\t\t\tHMM5")
for i in range(0, len(seqs)):
    row = "O" + str(i+1) + "\t"
    for j in range(0, len(seqs[i])):
        if j == maxIndices[i]:
            row += "*"
        row += "L=" + str(seqs[i][j]) + "\t\t\t\t"
    print(row)
