import nanohmm


def train(A, B, pi, T, O, numRestarts, numIters):
    N = len(A)
    M = len(B)
    bestA = [[0]*N]*M
    bestB = [[0]*N]*M
    bestPi = [0]*N
    bestLL = float('-inf')

    while numRestarts > 0:
        for ix in range(0, N):
            pi[ix] = 
        numRestarts -= 1



O1 = [4, 2, 5, 1, 5, 1, 5, 3, 2, 3, 2, 0, 1, 0, 0, 4, 4, 3, 0, 1]
O2 = [3, 2, 3, 3, 5, 5, 5, 5, 1, 0, 1, 4, 2, 4, 3, 0, 5, 3, 1, 0]
O3 = [4, 3, 0, 3, 4, 0, 1, 0, 2, 0, 5, 3, 2, 0, 0, 5, 5, 3, 5, 4]
O4 = [3, 4, 2, 0, 5, 4, 4, 3, 1, 5, 3, 3, 2, 3, 0, 4, 2, 5, 2, 4]
O5 = [2, 0, 5, 4, 4, 2, 0, 5, 5, 4, 4, 2, 0, 5, 4, 4, 5, 5, 5, 5]

# Part 10A
# Follow through the Virtirbi and Baum-Welch algorithm to determine the new values for A, B, and pi


# Continue this process, using the reestimated parameters, until the change in parameter values is small (converged)


print("Baum--Welch:")
# A = [[0.33, 0.33, 0.33], [0.33, 0.33, 0.33], [0.33, 0.33, 0.33]]
# B = [[0.33, 0.33, 0.33], [0.33, 0.33, 0.33], [0.33, 0.33, 0.33]]
# pi = [0.33, 0.33, 0.33]
# TODO: Create a method that supports random restarts to find global maximum
A = [[0.33, 0.33, 0.33], [0.33, 0.33, 0.33], [0.33, 0.33, 0.33]]
B = [[0.16, 0.16, 0.16, 0.16, 0.16, 0.16], [0.16, 0.16, 0.16, 0.16, 0.16, 0.16], [0.16, 0.16, 0.16, 0.16, 0.16, 0.16]]
pi = [0.33, 0.33, 0.33]

lambda_ = nanohmm.hmm_t(A, B, pi)
bw = nanohmm.baumwelch_t(lambda_)
LL, lambda_ = nanohmm.baumwelch(bw, O1, 100)
print("LL =", LL)
print("Trained HMM:")
print("A = ", lambda_.A)
print("B = ", lambda_.B)
print("pi = ", lambda_.pi)
