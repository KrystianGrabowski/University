#lang racket

;; arithmetic expressions

(define (const? t)
  (number? t))

(define (binop? t)
  (and (list? t)
       ;(= (length t) 3) ;;zad6
       (member (car t) '(+ - * /))))

(define (binop-op e)
  (car e))

(define (binop-left e)
  (cadr e))

(define (binop-right e)
  (caddr e))

(define (binop-cons op l r)
  (list op l r))

(define (arith-expr? t)
  (or (const? t)
      (and (binop? t)
           (arith-expr? (binop-left  t))
           (arith-expr? (binop-right t)))))

;; calculator

(define (op->proc op)
  (cond [(eq? op '+) +]
        [(eq? op '*) *]
        [(eq? op '-) -]
        [(eq? op '/) /]))

(define (eval-arith e)
  (cond [(const? e) e]
        [(binop? e)
         ((op->proc (binop-op e))
            (eval-arith (binop-left  e))
            (eval-arith (binop-right e)))]))

;; let expressions

;(define (let-def? t)
;  (and (list? t)
;       (= (length t) 2)
;       (symbol? (car t))))
;
;(define (let-def-var e)
;  (car e))
;
;(define (let-def-expr e)
;  (cadr e))
;
;(define (let-def-cons x e)
;  (list x e))
;
;(define (let? t)
;  (and (list? t)
;       (= (length t) 3)
;       (eq? (car t) 'let)
;       (let-def? (cadr t))))
;
;(define (let-def e)
;  (cadr e))
;
;(define (let-expr e)
;  (caddr e))

;(define (let-cons def e)
; (list 'let def e))

;(define (var? t)
;  (symbol? t))

;(define (var-var e)
;  e)
;
;(define (var-cons x)
;  x)

;(define (arith/let-expr? t)
;  (or (const? t)
;      (and (binop? t)
;           (arith/let-expr? (binop-left  t))
;           (arith/let-expr? (binop-right t)))
;      (and (let? t)
;           (arith/let-expr? (let-expr t))
;           (arith/let-expr? (let-def (let-def-expr t))))
;      (var? t)))

;; evalation via substitution

(define (subst e x f)
  (cond [(const? e) e]
        [(binop? e)
         (binop-cons
           (binop-op e)
           (subst (binop-left  e) x f)
           (subst (binop-right e) x f))]
        [(let? e)
         (let-cons
           (let-def-cons
             (let-def-var (let-def e))
             (subst (let-def-expr (let-def e)) x f))
           (if (eq? x (let-def-var (let-def e)))
               (let-expr e)
               (subst (let-expr e) x f)))]
        [(var? e)
         (if (eq? x (var-var e))
             f
             (var-var e))]))

(define (eval-subst e)
  (cond [(const? e) e]
        [(binop? e)
         ((op->proc (binop-op e))
            (eval-subst (binop-left  e))
            (eval-subst (binop-right e)))]
        [(let? e)
         (eval-subst
           (subst
             (let-expr e)
             (let-def-var (let-def e))
             (eval-subst (let-def-expr (let-def e)))))]
        [(var? e)
         (error "undefined variable" (var-var e))]))

;; evaluation via environments

(define empty-env
  null)

(define (add-to-env x v env)
  (cons (list x v) env))

(define (find-in-env x env)
  (cond [(null? env) (error "undefined variable" x)]
        [(eq? x (caar env)) (cadar env)]
        [else (find-in-env x (cdr env))]))

(define (eval-env e env)
  (cond [(const? e) e]
        [(if-zero? e) (if-zero
                       (eval-env (if-cond e) env)
                       (if-a e)
                       (if-b e)
                       env)]
        [(binop? e)
         (apply
          (op->proc (binop-op e))
            (map (lambda (x) (eval-env x env)) (op-args e)))]
        [(let? e)
         (eval-env
           (let-expr e)
           (env-let (let-def e) env))]
        [(var? e) (find-in-env (var-var e) env)]))


(define (eval e)
  (eval-env e empty-env))

;;#######1#######

(define (arith-rpn xs)
  (define (onp lst acc)
    (cond [(const? lst) (cons lst acc)] 
          [(binop? lst) (onp (cadr lst) (onp (caddr lst) (cons (binop-op lst) acc)))]))
  (onp xs null))

;;######2#######

(define (stack? s)
  (list? s))

(define (push x stack)
  (cons x stack))

(define (pop stack)
  (if (null? stack)
      null
      (cons (car stack) (cdr stack))))

;;#######3########

(define (eval-rpn expr)
  (define (eval-rpn-help e stack)
    (cond [(null? e) (car stack)]
          [(const? (car e))
           (eval-rpn-help (cdr e) (push (car e) stack))]
          [(member (car e) '(+ - * /))
           (eval-rpn-help (cdr e) (push
                                   ((op->proc (car e)) (cadr stack)  (car stack))
                                   (cddr stack)))]))
  (eval-rpn-help expr null))

;;#######5#######

(define (if-cond e)
  (cadr e))

(define (if-a e)
  (caddr e))

(define (if-b e)
  (cadddr e))
 
(define (if-zero? e)
  (and (list? e)
       (= 4 (length e))
       (eq? (car e) 'if-zero)))

(define (if-zero cond a b env)
  (if (= 0 cond)
      (eval-env a env)
      (eval-env b env)))

;;######6######

(define (op-args e)
  (cdr e))

;;######7#######

(define (let-def? t)
  (list? t))

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
      (and (binop? t)
           (arith/let-expr? (binop-left  t))
           (arith/let-expr? (binop-right t)))
      (and (let? t)
           (arith/let-expr? (let-expr t))
           (arith/let-expr? (let-def (let-def-expr t))))
      (var? t)))

(define (env-let def env)
  (printf "~v ~%" env)
  (if (null? def)
       env
       (if (symbol? (car def))
           (env-for-let def env)
           (env-let
            (cdr def)
            (env-for-let (car def) env)))))

(define (env-for-let def env)
  (add-to-env
    (let-def-var def)
    (eval-env (let-def-expr def) env)
    env))
