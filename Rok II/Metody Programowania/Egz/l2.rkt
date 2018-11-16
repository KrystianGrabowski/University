#lang racket

(define (change x)
  (change-problem x 5))

(define (change-problem amount number)
  (cond [(= amount 0) 1]
        [(< amount 0) 0]
        [(if (= number 0)
             0
             (+ (change-problem (- amount (give-coin number)) number)
                (change-problem amount (- number 1) )))]))

(define (give-coin number)
  (cond [(= number 1) 1]
        [(= number 2) 5]
        [(= number 3) 10]
        [(= number 4) 25]
        [(= number 5) 50]))


(define tolerance 0.00001)
(define (fixed-point f x)
  (define (good-enough? x y)
    (< (abs (- x y)) tolerance))
  (define (try guess)
    (let ([next (f guess)])
      (if (good-enough? guess next)
          next
          (try next))))
  (try x))


;;######3######
(define (compose f g)
  (lambda (x) (f (g x))))

(define (repeated p n)
  (if (= n 0)
      (lambda (x) (identity x))
      (compose p (repeated p (- n 1)))))

;;######4######

(define (product-rec term a next b)
  (if (> a b)
      1
      (* (term a) (product-rec term (next a) next b))))

(define (product-iter term a next b)
  (define (product-help a acc)
    (if (> a b)
        acc
        (product-help (next a) (* acc (term a)))))
  (product-help a 1))

(define (square x)
  (* x x))

(define (inc x)
  (+ x 1))

(define (zwei x)
  (+ x 2))

(define (gen x)
  (/ (* (+ x 1) (- x 1)) (square x)))

;;(* 4 (product-rec gen 3.0 zwei 1000000))
;;(* 4 (product-iter gen 3.0 zwei 1000000))

;;#######5#######

(define (accumulate-rec combiner null-value term a next b)
  (if (> a b)
      null-value
      (combiner (term a) (accumulate-rec combiner null-value term (next a) next b))))

(define (accumulate-iter combiner null-value term a next b)
  (define (iter-help a acc)
    (if (> a b)
        acc
        (iter-help (next a) (combiner (term a) acc))))
  (iter-help a null-value))

;;######6######

(define (cont-frac num den k)
  (define (help acc)
    (if (= k acc)
        0
        (/ (num acc) (+ (den acc) (help (+ acc 1))))))
  (help 1))

(define (cont-frac-iter num den k)
  (define (cont-frac-helper i acc)
    (if (= i 0)
        acc
        (cont-frac-helper (- i 1) ( / (num i) (+ acc (den i))))))
  (cont-frac-helper k 0))

(define (fix-point f x0)
  (let ((x1 (f x0)))
    (if (goodenough? x0 x1)
        x0
        (fix-point f x1))))

(define (average-damp f)
  (lambda (x) (/ (+ x (f x)) 2 )))
(define (goodenough? a b)
  (< (abs(- a b)) 0.000000001))



;( cont-frac ( lambda ( i ) 1.0) ( lambda ( i ) 1.0) 1000 )
(+ 3.0 (cont-frac-iter (lambda (x) (square (+ 1 (* (- x 1) 2)))) (lambda (x) 6) 100))
(+ 3.0 (cont-frac (lambda (x) (square (+ 1 (* (- x 1) 2)))) (lambda (x) 6) 100))
