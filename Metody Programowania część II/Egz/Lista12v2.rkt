#lang typed/racket

(: prefixes (All (A) (-> (Listof A) (Listof (Listof A)))))
(define (prefixes xs)
  (: help (All (A) (-> (Listof A) (Listof (Listof A)) (Listof (Listof A)))))
  (define (help lst acc)
    (if (null? lst)
        acc
        (help (cdr lst) (cons (cons (car lst) (car acc))  acc))))
  (if (null? xs)
      null
      (help (cdr xs) (list (list (car xs))))))