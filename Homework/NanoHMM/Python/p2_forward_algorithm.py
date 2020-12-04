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


# Print results for Part 3A
A = [[0.66, 0.34], [1.0, 0.0]]
B = [[0.5, 0.25, 0.25], [0.1, 0.1, 0.8]]
p = [0.8, 0.2]
O = [0, 1, 0, 2, 0, 1, 0]
alpha, prob = forwardAlgorithm(A, B, p, O)
print("Part 3A Results")
print(str(alpha))
print("Likelihood = {}".format(prob))

# Print results for Part 3B
A = [[0.8, 0.1, 0.1],
     [0.4, 0.2, 0.4],
     [0, 0.3, 0.7]]
B = [[0.66, 0.34, 0],
     [0, 0, 1],
     [0.5, 0.4, 0.1]]
p = [0.6, 0, 0.4]
alpha, prob = forwardAlgorithm(A, B, p, O)
print("Part 3B Results")
print(str(alpha))
print("Likelihood = {}".format(prob))

# Print results for Part 6
O1 = [1, 0, 0, 0, 1, 0, 1]
O2 = [0, 0, 0, 1, 1, 2, 0]
O3 = [1, 1, 0, 1, 0, 1, 2]
O4 = [0, 1, 0, 2, 0, 1, 0]
O5 = [2, 2, 0, 1, 1, 0, 1]
A = [[0.6, 0.4],
     [1, 0]]
B = [[0.7, 0.3, 0],
     [0.1, 0.1, 0.8]]
pi = [0.7, 0.3]
alpha, prob = forwardAlgorithm(A, B, p, O1)
print("Likelihood for O1 = {}".format(prob))
alpha, prob = forwardAlgorithm(A, B, p, O2)
print("Likelihood for O2 = {}".format(prob))
alpha, prob = forwardAlgorithm(A, B, p, O3)
print("Likelihood for O3 = {}".format(prob))
alpha, prob = forwardAlgorithm(A, B, p, O4)
print("Likelihood for O4 = {}".format(prob))
alpha, prob = forwardAlgorithm(A, B, p, O5)
print("Likelihood for O5 = {}".format(prob))
