# RMQ-With-Shift
In thetraditional RMQ (Range Minimum Query) problem, we have a static array A. Then for each query (L, R) (L<=R), we report the minimum value among A[L], A[L+1], …, A[R]. Note that the indices start from 1, i.e. the left-most element is A[1].
In this problem, the array A is no longer static: we need to support another operation shift(i1, i2, i3, …, ik) (i1<i2<...<ik, k>1): we do a left “circular shift” of A[i1], A[i2], …, A[ik].
For example, if A={6, 2, 4, 8, 5, 1, 4}, then shift(2, 4, 5, 7) yields {6, 8, 4, 5, 4, 1, 2}. After that, shift(1,2) yields {8, 6, 4, 5, 4, 1, 2}.
