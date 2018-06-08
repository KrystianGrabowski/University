#lang racket
(define (distance x y)
  (abs (- x y)))

(define (square x)
  (* x x))

(define (average x y)
  (/ (+ x y) 2))



(define (sqrt x)
  
  (define (betteraprox approximation)
    (average (/ x approximation) approximation))

  (define (isgood? approximation)
    (< (distance x (square approximation)) 0.00001))

  (define (sqrt-iter approximation)
    (cond
      [(isgood? approximation) approximation]
      [ else   (sqrt-iter (betteraprox approximation))]))
  
  (sqrt-iter 1.0))



