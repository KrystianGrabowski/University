#lang racket
(require racket/contract)

;(define x 23)
;x
;(begin (set! x 130)
;       (- x 131))
;x

(define/contract foo number? '2) ;ma zwracac number?

(define/contract (average x y)
  (-> number? number? number?) ;f z dwóch number w number
  (/ (+ x y) 2))

(define/contract (dist a b)
  (-> number? number? number?)
  (abs (- a b)))

(define/contract (square x)
  (-> number? number?)
  (* x x))

(define/contract (sqrt x)
  (-> positive? positive?)
  ;; lokalne definicje
  ;; poprawienie przybliżenia pierwiastka z x
  (define (improve approx)
    (average (/ x approx) approx))
  ;; nazwy predykatów zwyczajowo kończymy znakiem zapytania
  (define (good-enough? approx)
    (< (dist x (square approx)) 0.0001))
  ;; główna procedura znajdująca rozwiązanie
  (define (iter approx)
    (cond
      [(good-enough? approx) approx]
      [else                  (iter (improve approx))]))
  
  (iter 1.0))