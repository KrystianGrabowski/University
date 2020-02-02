:- module(krystian_grabowski_tests, [tests/3]).


tests(bledy, input("main A = 1"), no).
tests(bledy_v2, input("def main A ="), no).
tests(pusta, input(""), yes).
tests(nawiasowanie, input("def main A = 123"), no).
tests(nawiasowanie_v1b, input("def main((_)) = 2"), yes).
tests(nawiasowanie_v2, input("def main((A), B) = A"), yes).
tests(nawiasowanie_v3, input("def main((A, B), (C, D)) = 1"), yes).


tests(polaczenie, input("def main(_, A) = 1"), yes).
tests(dwie_definicje, input("def main1(A) = 1 def main2(B) = 2"), yes).
tests(ify, input("def main(A, B) = if A > B then 1 else 2"), yes).
tests(ify_v2a, input("def main(A, B) = if A > B else 1"), no).
tests(ify_v2b, input("def main(A, B) = if A > B then 1"), no).
tests(ify_funk, input("def main(A, B) = if A < B then 1 else main1(A, B) def main1(A, B) = 2"), yes).
tests(ify_ifow, input("def main(A, B) = if A + B    then 1 else if A < B then 2 else 1"), yes).
tests(lety, input("def main(A) = let A = 1 in 123"), yes).

tests(wielkiehalo,input("def half_adder(A, B) = A & B, A ^ B"), yes).
tests(funkcja , input("def main(_) = funckja(Par1 + Par2)"), yes).
tests(operat_1 , input("def main(_) = -3 , 7"), yes).
tests(operat_2 , input("def main(A, B) = A = B"), yes).
tests(operat_3 , input("def main(_) = x <> y"), yes).
tests(operat_4 , input("def main(A, B) = a[2 + 3]"), yes).
tests(operat_666 , input("def main(A) = 2 + test[A..B]"), yes).
tests(operat_6 , input("def main(_) = 3 ^ 2"), yes).
tests(operat_7 , input("def main(A, B) = A | B"), yes).
tests(operat_8 , input("def main(_) = 3 + (5 - 2)"), yes).
tests(operat_9 , input("def main(A) = 4 - 5"), yes).
tests(operat_10 , input("def main(A, B) = A & B"), yes).
tests(operat_11 , input("def main(A, B) = A * B"), yes).
tests(operat_12 , input("def main(A, B) = A / B"), yes).
tests(operat_13 , input("def main(A) = A % 3"), yes).
tests(operat_5 , input("def main(A, B) = A @ B"), yes).

tests(mir_1 , input("def main(A, Pad) = -3 ^ A * #Pad"), yes).
tests(mir_2 , input("def main(A, B) = ~A = -B % A = 9"), yes).
tests(mir_3 , input("def main(A) = -A + 4 - 5"), yes).
tests(mir_3b , input("def main(A) = 4 ^ A & ~B"), yes).
tests(mir_4 , input("def main(A, B, Pad) = 9 * ~A / B % 10 | Pad"), yes).
tests(mir_5 , input("def main(A) = A <= ~-#3"), yes).
tests(mir_13 , input("def main(A) = 3 / 10 ^ A *"), no).
tests(mir_144 , input("def main(A, B) = = -B * A"), no).

tests(niedoz , input("def main(A) = #A ="), no).
tests(unar , input("def main(A) = ~~~~~~~~~~"), no).
tests(binar , input("def main(A) = */%"), no).
tests(wybor_bit , input("def main(A) = p[3 < 4]"), yes).
tests(wybor_bits , input("def main(A, B) = -2[1..9]"), yes).
tests(naw , input("def main(A, B) = (if A > B then 1 else 2)"), yes).
tests(vector , input("def main(_) = []"), yes).
tests(poj_bit , input("def main(A) = [3 ^ 6]"), yes).
tests(wewnn , input("def main(_) = [(-3)]"), yes).

tests(plik_2 , file("dobro.hdml"), yes).
tests(plik_23 , file("dobro1.hdml"), yes).
tests(plik_24 , file("dobro2.hdml"), yes).
tests(plik_51 , file("zlo.hdml"), no).
tests(plik_52 , file("zlo1.hdml"), no).
tests(plik_53 , file("szlo.hdml"), no).


