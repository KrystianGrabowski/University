#lang racket
;;(list-ref '(1 2 3) 2)
;;> 3

(define (append xs ys)
  (if (null? xs)
      ys
      (cons (car xs) (append (cdr xs) ys))))

(define (map f xs)
  (if (null? xs)
      null
      (cons (f (car xs))
            (map f (cdr xs)))))


;#####1######
(define (make-rat num den)
  (let ([g (gcd num den)])
    (list (/ num g) (/ den g)))
  )

(define (rat-num r)
  (car r)
  )

(define (rat-den r)
  (cadr r)
  )

(define (rat? r)
  (and (list? r)
       (= (length r) 2)
       (not (= (rat-den r) 0))))

;#####2######
(define (make-point x y)
  (cons x y))

(define (point-x p)
  (car p))

(define (point-y p)
  (cdr p))

(define (point? p)
  (and (pair? p)
       (not (or (null? (point-x p))
                (null? (point-y p))))))

(define (make-vect p1 p2)
  (cons p1 p2))

(define (vect-begin v)
  (car v))

(define (vect-end v)
  (cdr v))

(define (vect? v)
  (and (pair? v)
       (point? (vect-begin v))
       (point? (vect-end v))))


(define (square x)
  (* x x))

(define (vect-length v)
  (let ([ve (vect-end v)]
        [vb (vect-begin v)])
    (sqrt (+ (square (- (point-x ve) (point-x vb)))
             (square (- (point-y ve) (point-y vb)))))))

(define (vect-scale v k)
  (let ([x0 (point-x (vect-begin v))]
        [y0 (point-y (vect-begin v))]
        [dx (- (point-x (vect-end v))
               (point-x (vect-begin v)))]
        [dy (- (point-y (vect-end v))
               (point-y (vect-begin v)))])
    (make-vect (make-point x0 y0) (make-point (+ x0 (* dx k)) (+ y0 (* dy k))))))
;; punkt(0,0) to x0 y0 a wynikowy to (x0 + (* x1 k))

(define (vect-translate v p)
  (let ([dx (- (point-x (vect-end v))
               (point-x (vect-begin v)))]
        [dy (- (point-y (vect-end v))
               (point-y (vect-begin v)))])
    (make-vect p (make-point (+ (point-x p) dx)
                             (+ (point-y p) dy)))))





;#####4######
(define (reverse-rec xs)
  (if (null? xs)
      null
      (append (reverse-rec (cdr xs)) (list (car xs)))))


(define (reverse-iter xs)
  (define (reverse-iter-help ls acc)
    (if (null? ls)
        acc
        (reverse-iter-help (cdr ls) (cons (car ls) acc))))
  (reverse-iter-help xs null))


;#####5#####
;(define (insert x xs)
;  (cond [(null? xs) (cons x null)]
;        [(< x (car xs)) (cons x xs)]
;        [else (cons (car xs) (insert x (cdr xs)))]))

;#####6######

(define (permi xs)
  (define (permi-helper ls)
    (if (null? ls)
        (list null)
        (permi-insert-all (car ls) (permi-helper (cdr ls)))))
  (define (permi-insert-all x ls)
    (if (null? ls)
        null
        (append
         (permi-in x (car ls) 0 (length (car ls)))
         (permi-insert-all x (cdr ls)))))
  (define (permi-in x ls i len)
    (if (> i len)
        null
        (cons (insert x i ls) (permi-in x ls (+ i 1) len))))
  (define (insert x poz ls)
    (if (or (= 0 poz) (null? ls))
        (cons x ls)
        (cons (car ls) (insert x (- poz 1) (cdr ls)))))
  (permi-helper xs)
      )






      



