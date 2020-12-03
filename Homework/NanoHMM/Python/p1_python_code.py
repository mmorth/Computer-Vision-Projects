from __future__ import print_function

import nanohmm


# This function implements the slow forward algorithm
def slowForwardAlgorithm(A, B, p, O):
    # Store necessary variables
    prob = 0
    numStates = len(A)
    pos = len(O)-1
    stateSeq = [0]*len(O)

    # Continue looping until all possible state sequences have been traversed
    while pos >= 0:
        curProb = p[stateSeq[0]] * B[stateSeq[0]][O[0]]
        for i in range(1,len(stateSeq)):
            curProb *= A[stateSeq[i-1]][stateSeq[i]] * B[stateSeq[i]][O[i]]
        prob += curProb

        if stateSeq[pos] < numStates-1:
            stateSeq[pos] += 1
        else:
            while stateSeq[pos] == numStates-1 and pos >= 0:
                stateSeq[pos] = 0
                pos -= 1
            if pos < 0:
                break
            else:
                stateSeq[pos] += 1
                pos = len(O)-1

    return prob


A = [[0.66, 0.34], [1.0, 0.0]]
B = [[0.5, 0.25, 0.25], [0.1, 0.1, 0.8]]
p = [0.8, 0.2]
O = [0, 1, 0, 2, 0, 1, 0]
result = slowForwardAlgorithm(A, B, p, O)
print(result)

# lambda_ = nanohmm.hmm_t(A, B, pi)
#
#
# print("Forward:")
# O = [0, 1, 0, 2, 0, 1, 0]
# f = nanohmm.forward_t(lambda_)
# LL = nanohmm.forward(f, O)
# print(LL)
