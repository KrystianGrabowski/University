#lang racket

#|
(define y 2)
(define x 5)
(define z 4)

(let ([x 3])
   (+ x y))

(let ([x 1]
       [y (+ x 2)])
   (+ x y))

(let ([x 1])
   (let ([y (+ x 2)])
      (* x y)))

(lambda (x y)
   (* x y z))

(let ([ x 1])
   (lambda (y z)
      (* x y z)))
|#

(define (inc x)
  (+ x 1))

(define (square x)
  (* x x))

(define (compose f g)
  (lambda (x) (f (g x))))

#|
> ((compose square inc) 5)
(lambda (5) (square (inc x)))
(lambda (5) (square (+ x 1)))
(lambda (5) (* (+ x 1) (+ x 1)))
(* (+ 5 1) (+ 5 1))
(* 6 6)
36
debug
(lambda (5) (square (inc x)))
(square (inc 5))
(square (+ 5 1))
(square 6)
(* 6 6)
36



> ((compose inc square) 5)
(lambda (5) (inc (square x)))
(lambda (5) (inc (* x x)))
(lambda (5) (+ (* x x) 1))
(+ (* 5 5) 1)
(+ 25 1)
26

debug
(lambda (5) (inc (square x)))
(inc (square 5))
(inc (* 5 5))
(inc 25)
(+ 25 1)
26
|#

;--------------------------------------------
;####3####
(define (repeated p n)
  (cond [(= n 0) (lambda(x) (x))]
        [(= n 1) p]
        [else (repeated (compose p p) (- n 1))])) ;;ŹLE

(define (repeated2 p n)
  (cond [(= n 0) (lambda(x) x)]
        [else (compose p (repeated2 p (- n 1)))]))

;####4####
(define (product term next a b)
  (cond [(> a b) 1]
        [else (* (term a) (product term next (next a) b))]))

(define (product-iter term next a b w)
  (cond [(> a b) w]
        [else (product-iter term next (next a) b (* w (term a)))]))

(define (zwei x)
  (+ x 2))

(define (gen x)
  (/ (* x (zwei x)) (square (inc x))))

(define (pi-product)
  ;;(* 4 (product gen zwei 2.0 10000))
  (* 4 (product-iter gen zwei 2.0 10000 1)))

;;####5####

(define accumulate
  (lambda (combiner null-value term a next b)
    (if (> a b)
        null-value
        (combiner (term a) (accumulate combiner null-value term (next a) next b)))))

(define (accumulate-iter combiner null-value term a next b)
  (define (accumulate-iter a acc)
    (if (> a b)
        acc
        (accumulate-iter (next a) (combiner acc (term a)))))
  
  (accumulate-iter a null-value))
         
;;####6####
(define (cont-frac num den k)
  (define (cont-frac2 acc)
    (cond [(= acc k) 0]
          [else (/ (num acc) (+ (den acc) (cont-frac2 (+ acc 1))))]))
  (cont-frac2 0))

(define (cont-frac-it num den k)
  (define (cont-frac2 acc w)
    (cond [(= acc 0) w ]
          [else (cont-frac2 (- acc 1) (/ (num acc) (+ (den acc) w)))]))
  (cont-frac2 k 0))
