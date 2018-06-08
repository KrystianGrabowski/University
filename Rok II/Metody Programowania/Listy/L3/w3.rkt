#lang racket
;;ułamki
(define (make-rat n d)
  (let ([c (gcd n d)])
        (cons (/ n c) (/ d c))))

(define (rat-numer l)
  (car l))

(define (rat-denom l)
  (cdr l))

(define (rat? l)
  (and (pair? l)
       (not (= (rat-denom l) 0))
       (= 1 (gcd (rat-numer l)
                 (rat-denom l)))))

(define (mult-frac l1 l2)
  (let ([n (* (rat-numer l1)
              (rat-numer l2))]
        [d (* (rat-denom l1)
              (rat-denom l2))])
    (make-rat n d)))

(define (zero? l)
  (= (rat-numer l) 0))

(define (integer->rational n)
  (make-rat n 1))
(define (div-rat l1 l2)
  (let ([n (* (rat-numer l1) (rat-denom l2))]
        [d (* (rat-denom l2) (rat-numer l1))])
    (make-rat n d)))

;;listy
(define (list? x)
  (or (null? x)
      (and (pair? x)
           (list? (cdr x)))))

(define (length xs)
  (if (null? xs)
      0
      (+ 1 (length (cdr xs)))))

(define (append xs ys)
  (if (null? xs)
      ys
      (cons (car xs) (append (cdr xs) ys))))

;;ciagi
;;accumulate v2

(define (gen-seg start next end)
  (if (> start end)
      null
      (cons start (gen-seg (next start) next end))))

(define (map f xs)
  (if (null? xs)
      null
      (cons (f (car xs)) (map f (cdr xs)))))

(define (sumlist xs)
  (if (null? xs)
      0
      (+ (car xs) (sumlist (cdr xs)))))

(define (fold-rigth op nval xs)
  (if (null? xs)
      nval
      (op (car xs) (fold-rigth op nval (cdr xs)))))

