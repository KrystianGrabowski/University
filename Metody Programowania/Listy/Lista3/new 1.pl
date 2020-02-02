select_min([H|T], M, R):-
  select_min(T, M, RE, [], H),
  reverse(RE, R).

select_min([], M, R, R, M).
select_min([H|T], M, R, A, C):-
  H >= C, !,
  select_min(T, M, R, [H|A], C).
select_min([H|T], M, R, A, C):-
  H < C,
  select_min(T, M, R, [C|A], H).

sel_sort([],[]):-!.
sel_sort(List, [M|O]):-
  select_min(List, M, R),
  sel_sort(R, O).