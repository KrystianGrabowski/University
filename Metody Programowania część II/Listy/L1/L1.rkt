#lang racket
;; Zadanie 4
(define (square x)
  (* x x))

(define (sum-of-squares x y)
  (+ (square x) (square y)))

(define (func a b c)
  (cond[(and (< a b) (< a c)) (sum-of-squares b c)]
       [(and (< b a) (< b c)) (sum-of-squares a c)]
       [else (sum-of-squares a b)]))

;; Zadanie 8

(define (power-close-to b n)
  (pct b 0 n))

(define (pct b e n)
  (if (> (expt b e) n)
      e
      (pct b (+ e 1) n)))

(define (power-close-to2 b n)
  
  (define (pct e)
    (if (> (expt b e) n)
        e
        (pct(+ e 1))))

  (pct 0))