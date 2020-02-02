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
    (< (distance x (cube approximation)) 0.000001))

  (define (cube-iter approximation)
    (cond
      [(isgood? approximation) approximation]
      [ else   (cube-iter (betteraprox approximation))]))

  ;; nie działa dla wszystkich ujemnych więc dodaję warunek
  (cond
    [(>= x 0) (cube-iter 1.0)]
    [else (* -1 (cube-root (* x -1)))]))


(define (test-function x)
  ;; obliczanie rzeczywistej wartości pierwiastka
  ;; również dla ujemnych porównywalny
  (define (real)
    (cond
      [(>= x 0) (expt x (/ 1 3))]
      [ else (* -1 (expt (* -1 x) (/ 1 3)))]))
  
  (define (compare)
        (<= (abs (- (real) (cube-root x))) 0.000001))

  (printf "~v ~%Value:     ~v~%Cube-root: ~v isGood?:~v ~%"
          x (real) (cube-root x) (compare) ))


;;możemy policzyć pierwiastki stopnia nieparzystego z liczb ujemnych
(test-function -0.75)
(test-function -6 )
(test-function -2 )
(test-function -3 )
(test-function -4 )
(test-function -8 )
(test-function -13 )
(test-function -77 )
(test-function -41 )
(test-function -91 )
(test-function -61 )
(test-function -666 )

(test-function 0.98)
(test-function 6 )
(test-function 2 )
(test-function 3 )
(test-function 5 )
(test-function 8 )
(test-function 12 )
(test-function 99 )
(test-function 61 )
(test-function 23 )
(test-function 55 )
(test-function 100 )
(test-function 1000 )