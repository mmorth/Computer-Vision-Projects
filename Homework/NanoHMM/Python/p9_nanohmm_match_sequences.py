import nanohmm
import numpy as np

# Display observation sequences
O1 = [4, 2, 5, 1, 5, 1, 5, 3, 2, 3, 2, 0, 1, 0, 0, 4, 4, 3, 0, 1]
O2 = [3, 2, 3, 3, 5, 5, 5, 5, 1, 0, 1, 4, 2, 4, 3, 0, 5, 3, 1, 0]
O3 = [4, 3, 0, 3, 4, 0, 1, 0, 2, 0, 5, 3, 2, 0, 0, 5, 5, 3, 5, 4]
O4 = [3, 4, 2, 0, 5, 4, 4, 3, 1, 5, 3, 3, 2, 3, 0, 4, 2, 5, 2, 4]
O5 = [2, 0, 5, 4, 4, 2, 0, 5, 5, 4, 4, 2, 0, 5, 4, 4, 5, 5, 5, 5]
Os = [O1, O2, O3, O4, O5]
s1 = []
s2 = []
s3 = []
s4 = []
s5 = []
seqs = [s1, s2, s3, s4, s5]

# HMM 1:
A = [[0.33, 0, 0, 0.67, 0],
      [0.67, 0, 0.33, 0, 0],
      [0, 1.0, 0.0, 0, 0],
      [0, 0, 0, 0.25, 0.75],
      [0.0, 0.0, 0.6, 0, 0.4]]
B = [[0.67, 0, 0, 0, 0, 0.33],
      [0.0, 1.0, 0, 0, 0, 0],
      [0.5, 0, 0, 0, 0, 0.5],
      [0, 0, 0, 0.25, 0.75, 0],
      [0, 0.0, 0.6, 0.4, 0, 0.0]]
pi = [0.0, 0.0, 0.0, 1.0, 0.0]
for i in range(0, len(Os)):
    lambda_ = nanohmm.hmm_t(A, B, pi)
    f = nanohmm.forward_t(lambda_)
    LL = nanohmm.forward(f, Os[i])
    seqs[i].append(LL)

# HMM 2:
A = [[0.0, 0.0, 1.0, 0, 0.0],
      [0.0, 0, 0.0, 0.0, 1.0],
      [0.38, 0.0, 0.23, 0.38, 0.0],
      [0.0, 0.31, 0.0, 0.69, 0],
      [0.0, 0.75, 0.0, 0.25, 0.0]]
B = [[0.0, 0.0, 1.0, 0.0, 0.0, 0.0],
      [0.0, 0.6, 0.2, 0.2, 0.0, 0.0],
      [0.0, 0.0, 0, 1.0, 0.0, 0],
      [0, 0.0, 0, 0.22, 0.0, 0.78],
      [0.6, 0.0, 0.0, 0.0, 0.4, 0.0]]
pi = [0.0, 0.0, 1.0, 0.0, 0.0]
for i in range(0, len(Os)):
    lambda_ = nanohmm.hmm_t(A, B, pi)
    f = nanohmm.forward_t(lambda_)
    LL = nanohmm.forward(f, Os[i])
    seqs[i].append(LL)

# HMM 3:
A = [[0, 0.0, 0.32, 0.18, 0.5],
      [0.0, 0.0, 0.0, 1.0, 0.0],
      [0, 0.0, 0, 0.0, 1.0],
      [0, 0.64, 0, 0.0, 0.36],
      [1.0, 0.0, 0, 0, 0]]
B = [[0.0, 0.17, 0.33, 0.0, 0.0, 0.5],
      [0.0, 0.0, 0.0, 1.0, 0.0, 0.0],
      [0.47, 0.0, 0.0, 0.0, 0.0, 0.53],
      [0.27, 0.0, 0.0, 0.0, 0.73, 0.0],
      [0.66, 0.0, 0.0, 0.33, 0.0, 0.0]]
pi = [0.0, 0.0, 0.0, 1.0, 0.0]
for i in range(0, len(Os)):
    lambda_ = nanohmm.hmm_t(A, B, pi)
    f = nanohmm.forward_t(lambda_)
    LL = nanohmm.forward(f, Os[i])
    seqs[i].append(LL)

# HMM 4:
A = [[0.0, 0.0, 1.0, 0, 0.0],
      [0.0, 0, 0.62, 0, 0.38],
      [0.0, 0.5, 0.0, 0.5, 0.0],
      [0.0, 0.23, 0.0, 0.0, 0.77],
      [0.0, 0, 0, 1.0, 0]]
B = [[0.0, 0.0, 0.0, 1.0, 0.0, 0.0],
      [0.0, 0.0, 0.62, 0, 0.38, 0.0],
      [0, 0.0, 0.0, 0.0, 1, 0],
      [0, 0.0, 0, 0.41, 0.18, 0.41],
      [0.31, 0.16, 0.37, 0.16, 0, 0.0]]
pi = [1.0, 0.0, 0.0, 0.0, 0]
for i in range(0, len(Os)):
    lambda_ = nanohmm.hmm_t(A, B, pi)
    f = nanohmm.forward_t(lambda_)
    LL = nanohmm.forward(f, Os[i])
    seqs[i].append(LL)

# HMM 5:
A = [[0.5, 0.33, 0, 0.17, 0.0],
      [0.0, 0.0, 0.0, 0.0, 1.0],
      [0.75, 0.0, 0.25, 0.0, 0.0],
      [0.0, 0.0, 0, 1.0, 0.0],
      [0.0, 0.0, 1.0, 0.0, 0.0]]
B = [[0.0, 0.0, 0.0, 0.0, 1.0, 0],
      [0.0, 0.0, 1.0, 0.0, 0.0, 0.0],
      [0.0, 0.0, 0.0, 0.0, 0, 1.0],
      [0.0, 0.0, 0.0, 0.0, 0, 1.0],
      [1.0, 0.0, 0.0, 0.0, 0.0, 0.0]]
pi = [0.0, 1.0, 0.0, 0.0, 0.0]
for i in range(0, len(Os)):
    lambda_ = nanohmm.hmm_t(A, B, pi)
    f = nanohmm.forward_t(lambda_)
    LL = nanohmm.forward(f, Os[i])
    seqs[i].append(LL)

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
        row += "logL=" + str(seqs[i][j]) + "\t\t\t\t"
    print(row)
