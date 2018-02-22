#lang racket

(define (cube-root x)

  (define (distance a b)
    (abs (- a b)))

  (define (square a)
    (* a a))

  (define (cube a)
    (* a a a))

  (define (div-by-three a b)
    (/ (+ a b) 3))

  (define (double-val a)
    (+ a a))
  
  (define (betteraprox approximation)
    (div-by-three (/ x (square approximation)) (double-val approximation)))

  (define (isgood? approximation)
    (< (distance x (cube approximation)) 0.00001))

  (define (cube-iter approximation)
    (cond
      [(isgood? approximation) approximation]
      [ else   (cube-iter (betteraprox approximation))]))
  
  (cube-iter 1.0))






(define (test-function x)
  (define (compare)
        (< (abs (- (expt x (/ 1 3)) (cube-root x))) 0.00001))

  (printf "~v ~%Value:     ~v~%Cube-root: ~v isGood?:~v ~%"
          x (expt x (/ 1 3)) (cube-root x) (compare) ))

(test-function 6)
(test-function 2)
(test-function 3)
(test-function 5)
(test-function 8)
(test-function 12)
(test-function 64)
(test-function 66)
(test-function 99)
(test-function 61)
(test-function 23)
(test-function 55)
(test-function 1000)