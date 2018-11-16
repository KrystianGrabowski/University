#lang typed/racket
;;length
(: length (-> (Listof Any) Nonnegative-Integer))
(define (length xs)
  (if (null? xs)
      0
      (+ 1 (length (cdr xs)))))


;;append
(: append (All (A) (-> (Listof A) (Listof A) (Listof A))))
(define (append xs ys)
  (if (null? xs)
      ys
      (cons (car xs) (append (cdr xs) ys))))

;;map
(: map (All (A B) (-> (-> A B) (Listof A) (Listof B))))
(define (map f xs)
  (if (null? xs)
      null
      (cons (f (car xs)) (map f (cdr xs))))) 

;;fold-right
(: fold-right (All (A B) (-> (-> A B B) B (Listof A) B)))
(define (fold-right f nval xs)
  (if (null? xs)
      nval
      (f (car xs)
         (fold-right f nval (cdr xs)))))
      