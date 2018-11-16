#lang racket
;;#######1#######
(define/contract (suffixes xs)
  (let ([a (new-∀/c 'a)])
    (-> (listof a) (listof (listof a))))
  (if (null? xs)
      null
      (cons xs (suffixes (cdr xs)))))

;;######2######
(define/contract foo number? 42)

(define/contract (dist x y)
  (-> number? number? number?)
  (abs (- x y)))

(define/contract (average x y)
  (-> number? number? number?)
  (/ (+ x y) 2))

(define/contract (square . x)
  (-> number? number?)
  (* x x))



(define/contract (sqrt x)
  (->i ([a any/c])
       ; [y (x) positive?])
        [result (a) (if (>= a 1) ;;x z wejścia
                        (<=/c a)
                        (>/c a))])
  ;; lokalne definicje
  ;; poprawienie przybliżenia pierwiastka z x
  (define (improve approx)
    (average (/ x approx) approx))
  ;; nazwy predykatów zwyczajowo kończymy znakiem zapytania
  (define (good-enough? approx)
    (< (dist x (square approx)) 0.0001))
  ;; główna procedura znajdująca rozwiązanie
  (define (iter approx)
    (cond
      [(good-enough? approx) approx]
      [else                  (iter (improve approx))]))
  
  (iter 1.0))

;;######3######

(define/contract kol any/c
  2)

;(let ([a (new-∀/c 'a)])
;    (-> (-> a (or/c a #f)) (listof a) (listof a)))

(define/contract (filter f xs)
  (->i ([f (-> any/c boolean?)]
        [xs list?])
       [result list?]
       #:post (result xs)
       (and (list? result)
            (<= (length result) (length xs))))
             
  (if (null? xs)
      null
      (if (f (car xs))
          (cons (car xs) (filter f (cdr xs)))
          (filter f (cdr xs)))))

(define (test x . y)
  (+ x (car y)))