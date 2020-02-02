:- module(krystian_grabowski_tests, [tests/5]).

:- op(200, fx, ~).
:- op(500, xfy, v).

tests(excluded_middle, validity, [p v ~p], 500, solution([(p,t)])).

tests(singleton, validity, [p], 500, solution([(p,t)])).
tests(neg_singleton, validity, [~p], 500, solution([(p,f)])).
tests(sprzeczne_v2, validity, [p, ~p] , 500, count(0)).
tests(jedno_wart, validity, [p, r] , 500, count(1)).
tests(tautologiasprz, validity, [p v ~p, ~p ,p] , 500, count(0)).

tests(prosty, validity, [p v ~p, r] , 500, solution([(p,f),(r,t)])).
tests(zanegowane, validity, [p v ~r], 500, solution([(p,t),(r,f)])).
tests(popular, validity, [p v r] , 500, count(3)).
tests(pusta, validity, [] , 500, count(0)).
tests(negacje, validity, [~p v ~r], 500, solution([(p,t),(r,f)])).

tests(id_ng, validity, [~p v ~p], 500, count(1)).
tests(sprzeczne, validity, [p v r, ~p, ~r] , 500, count(0)).
tests(prosty_v2, validity, [p v ~p v ~r], 1000, solution([(p,f),(r,t)])).
tests(total_neg, validity, [~p v ~r v ~l], 2000, solution([(p,t),(r,t),(l,f)])).
tests(zanegowanev2, validity, [p v ~r, ~p] , 1500, solution([(p,f),(r,f)])).

tests(rezolwenta, validity, [p v r , p v ~r], 1500, solution([(p,t),(r,f)])).
tests(rezolwenta_v2, validity, [p v r ,~r v u], 2000, solution([(p,t),(r,t),(u,t)])).
tests(horn, validity, [p v ~r v ~l , ~r v ~l], 3000, solution([(p,t),(r,t),(l,f)])).
tests(mieszanka , validity, [p v ~p v l v ~l], 2000,  solution([(p,f),(r,f)])).
tests(pozycyjna, validity, [~p v r, p v ~r], 2000, solution([(p,t),(r,t)])).


tests(odwrotne_2, validity, [p v r v l, ~p v ~r v ~l], 4000, solution([(p,f),(r,f),(l,t)])).
tests(dowod_v2 , validity, [p v ~r, ~p v l ,r], 4000, solution([(l,t),(p,t),(r,t)])).
tests(rezol_sprzecz , validity, [p v r, ~p v r, p v ~r, ~p v ~r], 7000, count(0)).
tests(rezol_sprzecz_v2 , validity, [p v r, l v u, ~r v ~u, l v r,~p v ~l, u v p], 10000, count(0)).

tests(wydajnosc_v1, performance, [p v a v b v c v d v e v f v g v h v r], 10000, count(1023)).
tests(wydajnosc_v2, performance, [p v r v u v o v l v n v k v h v e,   ~p v ~r v ~u v ~o v ~l v ~n v ~k v ~h v ~e ], 10000, count(510)).
tests(wydajnosc_v3, performance, [a v b , c v d, e v f, g v h, i v j, p v r, k v f, n v z,  ~b,~d,~f,~g,~i,~p,~k,~n ], 10000, count(1)).


