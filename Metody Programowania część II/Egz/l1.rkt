#lang racket
(define (square x)
  (* x x))

(define (sum-of-squares x y)
  (+ (square x) (square y)))

(define (sum-of-bigger a b c)
  (cond [(and (< a b) (< a c)) (sum-of-squares b c)]
        [(and (< b a) (< b c)) (sum-of-squares a c)]
        [else (sum-of-squares a b)]))


(define (power-close-to b n)
  (define (power-close-help iter)
    (if (> (expt b iter) n)
        iter
        (power-close-help (+ iter 1))))
  (power-close-help 0))