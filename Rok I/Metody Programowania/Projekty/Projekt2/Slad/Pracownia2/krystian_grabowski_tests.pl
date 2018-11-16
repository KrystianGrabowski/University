:- module(krystian_grabowski_tests, [resolve_tests/5, prove_tests/4]).

:- op(200, fx, ~).
:- op(500, xfy, v).


resolve_tests(esencja, p, p v r, ~p v r, r).
resolve_tests(esencja_v2, p, p v r, ~p v t, r v t).
resolve_tests(pusta, r , r, ~r, []).
resolve_tests(negacja, p, p v r, ~p v ~r, r v ~r).
resolve_tests(dezor, p, p, ~p v p, p).
resolve_tests(powtarzacz, p , p v p v p, ~p v ~p v ~p, []).
resolve_tests(negacja_v2, p, p v r, ~p v ~t, r v ~t).
resolve_tests(negacja_v3, p, p v ~r, ~p v ~t, ~r v ~t).
resolve_tests(pojed, u, u v r, ~u, r).
resolve_tests(pojed_neg, t, t, ~t v ~r, ~r).
resolve_tests(troj, r, r v p, ~r v o v l, p v o v l).
resolve_tests(konce, p, ~o v a v p, r v t v ~p, ~o v a v r v t).

prove_tests(singleton, validity, [~p], sat).
prove_tests(sprzecznosc, validity, [p, ~p], unsat).
prove_tests(wylaczony_srodek, validity, [p v ~p], sat).
prove_tests(negowane, validity, [p v r, ~p v ~r], sat).
prove_tests(negowane_v2, validity, [p v r, ~p, ~r], unsat).
prove_tests(falsz, validity, [p v r, ~p v r, ~r], unsat).
prove_tests(jednopoprawne, validity, [p v ~r, ~p v l ,r], sat).
prove_tests(magiczna_trojka, validity,[p v r, ~p v t, ~r v ~t],unsat).
prove_tests(dowod_v1, validity, [~p v q, ~q v r, p, ~r],unsat).
prove_tests(dowod_v2, validity, [~p v ~r v q, ~p v ~r v t, p, r, ~t],unsat).
prove_tests(dowod_v3, validity, [~p v ~r, p v ~r, ~p v r, p v r], unsat).
prove_tests(dowod_v4, validity, [~p v u, ~p v ~o v t, ~u v o, p, ~t], unsat).
prove_tests(dowod_v5,validity, [p v r, ~r v ~t, o v t, o v r, ~p v ~o, t v p ], unsat).
prove_tests(niesprzeczne,validity, [p v t v r, ~r v ~t v ~p, ~t v r, ~r v p], sat).
prove_tests(duzy,validity, [p v r v u v o v l v n v k v h v e,   ~p v ~r v ~u v ~o v ~l v ~n v ~k v ~h v ~e ], sat).
prove_tests(duzy_v2, validity, [a v b , c v d, e v f, g v h, i v j, p v r, k v f, n v z,  ~b,~d,~f,~g,~i,~p,~k,~n,~z ], unsat).
prove_tests(wydajnosc, performance, [a v b v c v d v e v f v g v h v i v j v k v p v q v r v u v t v z, ~a, ~b, ~c, ~d, ~e, ~f, ~g, ~h, ~i, ~j, ~k, ~p, ~q, ~r, ~u, ~t, ~z], unsat).
prove_tests(wydajnosc_v2, performance, [a v b v c v d v e v f v g v h v i v j v k v p v q v r v u v t v z, ~a, ~b, ~c, ~d, ~e, ~f, ~g, ~h, ~i, ~j, ~k, ~p, ~q, ~r, ~u, ~t, z], sat).
prove_tests(wydaj_max, performance, [a v b v c v d v e v f v g v h v i v j v k v l v m v n v o v p v r v s v t v u v w v y v z,  ~a v ~b v ~c v ~d v ~e v ~f v ~g v ~h v ~i v ~j v ~k v ~l v ~m v ~n v ~o v ~p v ~r v ~s v ~t v ~u v ~w v ~y v ~z],sat).


