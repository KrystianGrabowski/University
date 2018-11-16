#lang racket

(define (lcons x f)
  (cons x f))

(define (lhead l)
  (car l))

(define (ltail l)
  ((cdr l)))

(define (nats-from m)
  (lcons
   m
   (lambda () (nats-from (+ m 1)))))

(define nats
  (nats-from 0))

(define (take n l)
  (if (or (null? l) (= n 0))
      null
      (cons (lhead l)
            (take (- n 1) (ltail l)))))

(define (filter p l)
  (cond [(null? l) null]
        [(p (lhead l))
         (lcons (lhead l)
                (lambda ()
                  (filter p (ltail l))))]
        [else (filter p (ltail l))]))

(define (prime? n)
  (define (div-by m)
    (cond [(= m n) true]
          [(= (modulo n m) 0) false]
          [else (div-by (+ m 1))]))
  (if (< n 2)
      false
      (div-by 2)))

;;######1######

(define (fib-from m n)
  (lcons
   (+ m n)
   (lambda () (fib-from n (+ m n)))))

(define fib
  (fib-from 1 0))

(define (int-from n)
  (lcons
   n 
   (cond [(= n 0) (lambda () (int-from 1))]
         [(> n 0) (lambda () (int-from (* n -1)))]
         [else     (lambda () (int-from (+ (* n -1) 1)))])))

(define int
  (int-from 0))

;;