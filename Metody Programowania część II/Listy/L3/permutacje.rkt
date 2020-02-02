#lang racket
(define (flatmap proc seq)
  (accumulate append null (map proc seq)))

(define (accumulate op initial sequence)
  (if (null? sequence)
      initial
      (op (car sequence)
          (accumulate op initial (cdr sequence)))))

(define (permutations sequence)
  (if (null? sequence)
      (list null)
      (flatmap (lambda(x)
               (map (lambda(p) (cons x p))
                    (permutations (remove x sequence))))
               sequence)))
                 