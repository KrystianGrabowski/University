#lang racket

;; pomocnicza funkcja dla list tagowanych o określonej długości

(define (tagged-tuple? tag len p)
  (and (list? p)
       (= (length p) len)
       (eq? (car p) tag)))

(define (tagged-list? tag p)
  (and (pair? p)
       (eq? (car p) tag)
       (list? (cdr p))))
;;

(define (node l r)
  (list 'node l r))

(define (node? n)
  (tagged-tuple? 'node 3 n))

(define (node-left n)
  (second n))

(define (node-right n)
  (third n))

(define (leaf? n)
  (or (symbol? n)
      (number? n)
      (null? n)))

;;

(define (res v s)
  (cons v s))

(define (res-val r)
  (car r))

(define (res-state r)
  (cdr r))

;;

(define (rename t)
  (define (rename-st t i)
    (cond [(leaf? t) (res i (+ i 1))]
          [(node? t)
           (let* ([rl (rename-st (node-left t) i)]
                  [rr (rename-st (node-right t) (res-state rl))])
             (res (node (res-val rl) (res-val rr))
                  (res-state rr)))]))
  (res-val (rename-st t 0)))

;;

(define (st-app f x y)
  (lambda (i)
    (let* ([rx (x i)]
           [ry (y (res-state rx))])
      (res (f (res-val rx) (res-val ry))
           (res-state ry)))))


(define get-st
  (lambda (i)
    (res i i)))

(define (modify-st f)
  (lambda (i)
    (res null (f i))))

;;

(define (inc n)
  (+ n 1))

(define (rename2 t)
  (define (rename-st t)
    (cond [(leaf? t)
           (st-app (lambda (x y) x)
                   get-st
                   (modify-st inc))]
          [(node? t)
           (st-app node
                   (rename-st (node-left  t))
                   (rename-st (node-right t)))]))
  (res-val ((rename-st t) 0)))

;;####TEST
(define (my-rename t)
  (define (help t i)
    (cond [(leaf? t) (res i (+ i 1))]
          [(node? t) (let* ([f1 (help (node-left t) i)]
                            [f2 (help (node-right t) (res-state f1))])
                       (res (node (res-val f1) (res-val f2)) (res-state f2)))]))
  (res-val (help t 0)))

(define (my-st-app f x y)
  (lambda(i)
    (let* ([x1 (x i)]
           [x2 (y (res-state x1))])
      (res (f (res-val x1) (res-val x2))
           (res-state x2)))))

(define (my-rename2 t)
  (define (helper t)
    (cond [(leaf? t) (st-app2
                      (lambda (x y) x)
                      (list (lambda (x) (res x (+ 1 x)))
                      (lambda (x) (res x x))))]
                      
           [(node? t) (st-app2
                       node
                       (list (helper (node-left t))
                       (helper (node-right t))))]))
  (res-val ((helper t) 0)))

;;#####TEST2

(define (help f st xs)
  (cond [(null? xs) (res null st) ]
        [else (let* ([r ((car xs) st)]
                     [sth (help f (res-state r) (cdr xs))])
                (res (cons (res-val r) (res-val sth))
                     (res-state sth)))]))
                


(define (st-app2 f xs)
  (lambda (i)
    (let* ([rest (help f i xs)]
           )
        (res (apply f (res-val rest)) (res-state rest)))))

;######2######

(define (rand max)
   (lambda (seed)
      (let ([v (modulo (+ (* 1103515245 seed) 12345) (expt 2 32))])
         (res (modulo v max ) v))))

(define (rand-val t)
  (define (help t)
    (cond [(leaf? t) (st-app2 (lambda (x y) x)
                              (list (lambda (i) (res (car ((rand 100) i)) (+ i 2)))
                                    (lambda (i) (res i i))))]
          [(node? t) (st-app2 node
                              (list (help (node-left t))
                                    (help (node-right t))))]
        ))
  (res-val ((help t) 0)))
  