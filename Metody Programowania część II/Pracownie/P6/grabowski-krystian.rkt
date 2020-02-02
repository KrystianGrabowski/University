#lang racket

(define (const? t)
  (number? t))

(define (binop? t)
  (and (list? t)
       (= (length t) 3)
       (member (car t) '(+ - * /))))

(define (binop-op e)
  (car e))

(define (binop-left e)
  (cadr e))

(define (binop-right e)
  (caddr e))

(define (binop-cons op l r)
  (list op l r))

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

(define (hole? t)
  (eq? t 'hole))

(define (arith/let/holes? t)
  (or (hole? t)
      (const? t)
      (and (binop? t)
           (arith/let/holes? (binop-left  t))
           (arith/let/holes? (binop-right t)))
      (and (let? t)
           (arith/let/holes? (let-expr t))
           (arith/let/holes? (let-def-expr (let-def t))))
      (var? t)))

(define (num-of-holes t)
  (cond [(hole? t) 1]
        [(const? t) 0]
        [(binop? t)
         (+ (num-of-holes (binop-left  t))
            (num-of-holes (binop-right t)))]
        [(let? t)
         (+ (num-of-holes (let-expr t))
            (num-of-holes (let-def-expr (let-def t))))]
        [(var? t) 0]))

(define (arith/let/hole-expr? t)
  (and (arith/let/holes? t)
       (= (num-of-holes t) 1)))


(define (var-exist? x var-list)
  (if (null? var-list)
      #f
      (if (eq? (car var-list) x)
          #t
          (var-exist? x (cdr var-list)))))

(define (add-var x var-list)
  (if (var-exist? x var-list)
      var-list
      (cons x var-list)))
  
  
(define (hole-context e)
  (cond [(hole? e) null]
        [(binop? e)
         (let ([left  (hole-context (binop-left  e))]
               [right (hole-context (binop-right e))])
         (cond [(void? left ) right]
               [(void? right) left ]))] 
        [(let? e)
         (cond
           [(hole? (let-def-expr (let-def e))) null]
           [(hole? (let-def-var (let-def e))) null]
           [(list? (hole-context (let-expr e)))
            (add-var (let-def-var (let-def e))
                     (hole-context (let-expr e)))]
           [else (hole-context (let-def-expr (let-def e)))])]))




(define (test)
  (define (check x y)
    (if (null? x )
        #t
        (if (var-exist? (car x) y)
            (check (cdr x) y)
            #f))
    )
  (define (compare x y)
    (if (and (= (length x)
                (length y))
             (check x y))
        (printf "~v~%" true)
        (printf "~v~%" false)))
    
  ;;Własne przyklady
  (compare (hole-context 'hole) '())
  (compare (hole-context '(let (g (+ 3 hole)) 2)) '())
  (compare (hole-context '(let (g (+ 5 4)) hole)) '(g))
  (compare (hole-context '(let (g (+ (let (x 8) 2) 4)) hole)) '(g))
  (compare (hole-context '(let (g (+
                                   (let (k 2) jablko)
                                   (let (l 1) ziemniak)))
                            hole))
           '(g))
  (compare (hole-context '(let (g (+
                                   (let (k 2) jablko)
                                   (let (l 1)
                                     (/ 2 1))))
                            hole))
           '(g))
  (compare (hole-context '(let (g (+
                                   (let (k 2) jablko)
                                   (let (l 1)
                                     hole)))
                            6))
           '(l))

  (compare (hole-context '(let (g 666) (+
                                        (let (k 2) jablko)
                                        (let (l 1)
                                          hole))))
           '(g l))
  (compare (hole-context '(let (a 660)
                            (let (b 661)
                              (let (c 662)
                                (let (d 663)
                                  (let (e 664)
                                    (let (f hole)
                                      (let (g 666)
                                        ))))))))
           '(a b c d e))
  (compare (hole-context '(+
                           (- (let (g 6) x)
                              (let (k 9)) y)
                           (- (let (p 2) z)
                              (let (a 2) hole))))
           '(a))
  (compare (hole-context '(+
                           (+
                            (+
                             (+
                              (+ (let (x 2) hole)
                                 b)
                              c)
                             d)
                            e)
                           a))                   
           '(x))
  (compare (hole-context '(* (let (x 2) (let (y hole) (let (z 4))))
                             (let (t 2) (let (l 3) (let (e 4))))))
           '(x))

  (compare (hole-context '(let (przykrywka 8) (let (przykrywka 5) hole)))
           '(przykrywka))
 
  )
