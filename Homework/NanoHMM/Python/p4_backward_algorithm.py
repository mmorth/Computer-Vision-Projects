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


# Test part 5A
A = [[0.66, 0.34], [1.0, 0.0]]
B = [[0.5, 0.25, 0.25], [0.1, 0.1, 0.8]]
O = [0, 1, 0, 2, 0, 1, 0]
beta = backwardAlgorithm(A, B, O)
print("Part 5A Beta Values:")
print(str(beta))

# Test part 5B
A = [[0.8, 0.1, 0.1],
     [0.4, 0.2, 0.4],
     [0, 0.3, 0.7]]
B = [[0.66, 0.34, 0],
     [0, 0, 1],
     [0.5, 0.4, 0.1]]
beta = backwardAlgorithm(A, B, O)
print("Part 5B Beta Values:")
print(str(beta))
