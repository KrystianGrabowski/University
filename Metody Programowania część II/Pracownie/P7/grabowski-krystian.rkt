#lang racket

;; expressions

(define (const? t)
  (number? t))

(define (op? t)
  (and (list? t)
       (member (car t) '(+ - * /))))

(define (op-op e)
  (car e))

(define (op-args e)
  (cdr e))

(define (op-cons op args)
  (cons op args))

(define (op->proc op)
  (cond [(eq? op '+) +]
        [(eq? op '*) *]
        [(eq? op '-) -]
        [(eq? op '/) /]))

(define (let-def? t)
  (and (list? t)
       (= (length t) 2)
       (symbol? (car t))))

(define (let-def-var e)
  (car e))

(define (let-def-expr e)
  (cadr e))

(define (let-def-cons x e)
  (list x e))

(define (let? t)
  (and (list? t)
       (= (length t) 3)
       (eq? (car t) 'let)
       (let-def? (cadr t))))

(define (let-def e)
  (cadr e))

(define (let-expr e)
  (caddr e))

(define (let-cons def e)
  (list 'let def e))

(define (var? t)
  (symbol? t))

(define (var-var e)
  e)

(define (var-cons x)
  x)

(define (arith/let-expr? t)
  (or (const? t)
      (and (op? t)
           (andmap arith/let-expr? (op-args t)))
      (and (let? t)
           (arith/let-expr? (let-expr t))
           (arith/let-expr? (let-def-expr (let-def t))))
      (var? t)))

;; let-lifted expressions

(define (arith-expr? t)
  (or (const? t)
      (and (op? t)
           (andmap arith-expr? (op-args t)))
      (var? t)))

(define (let-lifted-expr? t)
  (or (and (let? t)
           (let-lifted-expr? (let-expr t))
           (arith-expr? (let-def-expr (let-def t))))
      (arith-expr? t)))

;; generating a symbol using a counter

(define (number->symbol i)
  (string->symbol (string-append "x" (number->string i))))

;; environments (could be useful for something)

(define empty-env
  null)

(define (add-to-env x v env)
  (cons (list x v) env))

(define (find-in-env x env)
  (cond [(null? env) (error "undefined variable" x)]
        [(eq? x (caar env)) (cadar env)]
        [else (find-in-env x (cdr env))]))

;; the let-lift procedure
(define (combo ll)
  (if (null? (cdr ll))
      (car ll)
      (append (car ll) (combo (cdr ll)))))

(define (let-lift e)
  (define (lets-expr ex)
    (cond [(var?   ex) (cons null ex)]
          [(const? ex) (cons null ex)]
          [(op?    ex) (let* ([f-args (map (lambda (x) (lets-expr x)) (op-args ex))]
                              [operator  (op-op ex)]
                              [arg-def (map car f-args)]
                              [arg-expr (map cdr f-args)]
                               )
                         (cons (combo arg-def) (cons operator arg-expr)))]
          [(let?  ex)  (let ([var (let-def-var (let-def ex))]
                             [var-expr (lets-expr (let-def-expr (let-def ex)))]
                             [expr (lets-expr (let-expr ex))])
                         (cons
                          (append
                           (append (list (list var (cdr var-expr))) (car var-expr))
                           (car expr))
                          (cdr expr)))]))
  
  (define (transform lets acc)
    (if (null? lets)
        acc
        (transform (cdr lets) (let-cons (car lets) acc))))
  
  (let* ([div (lets-expr (rename e))]
         [lets (car div)]
         [expr (cdr div)])
    (transform lets expr)))

(define (max-f ls)
  (define (help ls max)
    (if (null? ls)
        max
        (if (< max (car ls))
            (help (cdr ls) (car ls))
            (help (cdr ls) max))))
  (if (null? ls)
      #f
      (help (cdr ls) (car ls))))
             
(define (rename e)
  (define (change old new ex)
    (cond [(var?   ex) (if (eq? old ex)
                           new
                           ex)]
          [(const? ex) ex]
          [(op?    ex) (let* ([f-args (map (lambda (x) (change old new x)) (op-args ex))]
                              [operator  (op-op ex)])
                         (cons operator f-args))]
          [(let?  ex)  (if (eq? (let-def-var(let-def ex)) old)
                           ex
                           (let ([var (let-def-var(let-def ex))]
                                 [var-expr (change old new (let-def-expr(let-def ex)))]
                                 [expr (change old new (let-expr ex))])
                             (let-cons (list var var-expr) expr)))]))
  
  (define (op-sep ex i acc)
    (if (null? ex)
        acc
        (let ([x (search (car ex) i)])
          (op-sep (cdr ex) (cdr x) (append acc (list x))))))
  
  (define (search ex i)
    (cond [(var?   ex) (cons ex i)]
          [(const? ex) (cons ex i)]
          [(op?    ex) (let* ([f-args (op-sep (op-args ex) i null)]
                              [operator  (op-op ex)]
                              [f-args-first (map car f-args)]
                              [f-args-iter (max-f (map cdr f-args))])
                         (cons (cons operator f-args-first) f-args-iter))]
          [(let?  ex) (let* ([new (number->symbol i)]
                            [var-expr (let-def-expr(let-def ex))]
                            [expr (change (let-def-var(let-def ex)) new (let-expr ex))]
                            [search-var-expr (search var-expr (+ i 1))]
                            [search-expr (search expr (cdr search-var-expr))])
                        (cons (let-cons
                               (list new (car search-var-expr))
                               (car search-expr))
                              (max-f (list (cdr search-var-expr) (cdr search-expr)))))]))
  (car (search e 0)))




(define (test)
  (define (prt nr x)
        (printf "[~v] ~v ~v ~%" nr x (if (let-lifted-expr? x)
                                         "OK"
                                         "FALSE")))

  (prt 1 (let-lift '(let (x 3) x)))
  (prt 2 (let-lift '(let (x 3) (- x x))))
  (prt 3 (let-lift '(let (x 3) (let (y 2) (- x y)))))
  (prt 4 (let-lift '(let (x 3) (let (x 66) (+ x x)))))
  (prt 5 (let-lift '(let (x (let (x 4) x)) (* x 2))))
  (prt 6 (let-lift '(let (a 3)
                      (let (b 66)
                        (let (c 56)
                          (let (d 99) (+ a b c d)))))))
  (prt 7 (let-lift '(let (x 3)
                      (let (x 66)
                        (let (x 56)
                          (let (x 99) (+ x x x x)))))))
  (prt 8 (let-lift '(let (x 3)
                      (let (x 66)
                        (let (x 56) (- x 
                                       (let (x 99) x)))))))
  (prt 9 (let-lift '(- (let (a 8) (+ a a))
                       (let (b 3) (+ b b)))))
  (prt 10 (let-lift '(+ (+ (let (x 1) (+ x x))
                           (let (y 2) (+ y y)))
                        (+ (let (x 11) (+ x x))
                           (let (y 12) (+ y y))))))
  (prt 11 (let-lift '(* 12 (let (x (+ 15 15))
                                   (+ (let (x 21) (* x x))
                                      (let (x 23) (/ x x))
                                      (let (x 22) (+ x x))
                                      (let (x 25) (- x (let (x 9912) (let (x 1) x))))
                                      (let (x 24) (+ x x))
                                      (let (x 26) (+ x x))))))))