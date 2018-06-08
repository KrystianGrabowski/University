#lang racket
(define (inc i)
  (+ i 1))

;;silnia
(define (fact n)
  (if (= n 0)
      1
      (* n (fact (- n 1)))))

(define (fact-iter n i c)
  (if (= n i)
      c
      (fact-iter n (inc i) (* c (inc i)))))

;;fibbonaci
(define (fib n)
  (cond [(= n 0) 1]
        [(= n 1) 1]
        [(+ (fib (- n 1)) (fib (- n 2)))]))

;;sumowanie
(define (sum-ints s e)
  (if (> s e)
      0
      (+ s (sum-ints (inc s) e))))

(define (cube x)
  (* x x x))

(define (sum-cubes s e)
  (if (> s e)
      0
      (+ (cube s) (sum-cubes (inc s) e))))

(define (sum-pi n e)
  (if (> n e)
      0
      (+ (/ 1 (* n (+ n 2))) (sum-pi (+ n 4) e))))

(define (sum term next s e)
  (if (> s e)
      0
      (+ (term s) (sum term next (next s) e))))

(define (sum-pi-alt n e)
  (define (sum-pi-term s)
    (/ 1 (* s(+ s 2))))
  (define (sum-pi-next s)
    (+ s 4))
  (sum sum-pi-term sum-pi-next n e))

(define (sum-pi-altv2 n e)
  (define (sum-pi-term s)
    (/ 1 (* s(+ s 2))))
  (sum sum-pi-term (lambda(s) (+ s 4)) n e))

;;lambda
(define square
  (lambda (x) (* x x)))

;;lety
(let
    ((x 3)
     (y (square 5)))
  (* x y))

(define lm
  (lambda (x y)
    (* x y)))

;;punkty stałe f(x)

(define (goodenough? a b)
  (< (abs(- a b)) 0.00001))

(define (fix-point f x0)
  (let ((x1 (f x0)))
    (if (goodenough? x0 x1)
        x0
        (fix-point f x1))))

;;tłumienie przez uśrednienie
(define (average-damp f)
  (lambda (x) (/ (+ x (f x)) 2 )))


(define (sqrt x)
  (fix-point (average-damp (lambda (y) (/ x y))) 1.0))

;;pochodna
(define (deriv f)
  (let ((dx 0.0000001))
    (lambda (x) (/ (- (f (+ x dx)) (f x)) dx))))

(define (newton-transform f)
  (lambda (x) (- x (/ (f x) ((deriv f) x)))))







