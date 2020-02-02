#lang racket

;;zadanie1
(define (make-rat n d)
  (let ([c (gcd n d)])
    (cons (/ n c) (cons (/ d c) null))))

(define (rat-num l)
  (car l))

(define (rat-den l)
  (car(cdr l)))

;;(define (rat? l)
(define (rat? l)
  (and (pair? l)
       (null? (cdr(cdr l)))
       (not (= (rat-den l) 0))))
       ;;(= 1 (gcd (rat-num l)
       ;;          (rat-den l)))))

;;zadanie2
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

;; cw6
(define (permi L acc)
  (if (null? L)
      (cons L L)
      (cons (per (car L) (cdr L)) (permi (cdr L)  ))))

(define (per e L)
  (define (permi2 L acc)
    (if (null? L)
        (cons (append acc (cons e null) )null)
        (cons (append acc (cons e L)) (permi2 (cdr L) (append  acc (cons  (car L) null) )))))
  (permi2 L null))

(define (append xs ys)
  (if (null? xs)
      ys
      (cons (car xs) (append (cdr xs) ys))))

(permi (cons 1 (cons 2 (cons 3 null))))