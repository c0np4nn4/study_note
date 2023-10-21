fact(0, 1).
fact(N, M) :-
    N > 0,
    N1 is N - 1,
    fact(N1, M1),
    M is N * M1.


append([1, 2, 3], [4, 5, 6, 7], L).
append([[1, 2, 3], [4, 5], [6, 7]], L).

