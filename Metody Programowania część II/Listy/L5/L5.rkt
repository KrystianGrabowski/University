#lang racket
;; treść

(define (var? t)
  (symbol? t))

(define (neg? t)
  (and (list? t)
       (= 2 (length t))
       (eq? 'neg (car t))))

(define (conj? t)
  (and (list? t)
       (= 3 (length t))
       (eq? 'conj (car t))))

(define (disj? t)
  (and (list? t)
       (= 3 (length t))
       (eq? 'disj (car t))))

(define (prop? f)
  (or (var? f)
      (and (neg? f)
           (prop? (neg-subf f)))
      (and (disj? f)
           (prop? (disj-left f))
           (prop? (disj-right f)))
      (and (conj? f)
           (prop? (conj-left f))
           (prop? (conj-right f)))))

;;zad1

(define (make-neg x)
  (list 'neg x))

(define (make-conj x y)
  (list 'conj x y))

(define (make-disj x y)
  (list 'disj x y))



(define (neg-subf f)
  (second f))

(define (disj-left f)
  (second f))

(define (disj-right f)
  (third f))

(define (conj-left f)
  (second f))

(define (conj-right f)
  (third f))

;;zad2

(define (free-vars f)
  (define (all-vars f)
    (if (var? f)
        (cons f null)
        (cond [(neg? f) (all-vars (neg-subf f))]
              [(disj? f) (append (all-vars (disj-left f))
                                 (all-vars (disj-right f)))]
              [(conj? f) (append (all-vars (conj-left f))
                                 (all-vars (conj-right f)) )])))
  (remove-duplicates (all-vars f)))

;;zad4

(define (literal? f)
  (or (var? f)
      (and (neg? f) (var? (cadr f)))))

(define (make-literal isNeg x)
  (if (eq? isNeg 'neg)
      (list isNeg x)
      (list 'null x)))

(define (nnf? f)
  (cond
    [(literal? f) #t]
    [(conj? f) (and (nnf? (conj-left f)) (nnf? (conj-right f)))]
    [(disj? f) (and (nnf? (disj-left f)) (nnf? (disj-right f)))]
    [else #f]))


;;zad5

(define (conv-to-nnf t)
  (define (conf-to-nnf-neg t)
    (cond [(var? t) (make-neg t)]
          [(neg? t) (conv-to-nnf (neg-subf t))]
          [(disj? t) (make-conj (conf-to-nnf-neg (disj-left t))
                                (conf-to-nnf-neg (disj-right t)))]
          [(conj? t) (make-disj (conf-to-nnf-neg (conj-left t))
                                (conf-to-nnf-neg (conj-right t)))]))
  (cond [(var? t) t]
        [(neg? t) (conf-to-nnf-neg t)]
        [(conj? t) (make-conj (conv-to-nnf (conj-left t))
                              (conv-to-nnf (conj-right t)))]))

;;;zad3
(define (eval-formula t vars)
  (cond [(var? t) (findvar t var)]
        [(neg? t) (not (eval-formula (neg-subf t) vars))]
        [(conj? t) (and (eval-formula (conj-left t) vars)
                        (eval-formula (conj-right t) vars))]
        [(disj? t) (or (eval-formula (disj-left t) vars)
                        (eval-formula (disj-right t) vars))]))

(define (falsifiable-eval? t)
  (define (falsifiable t vals)
    (if (null? vals)
        #f
        (if (eval-formula t (car vals))
            (falsifiable t (cdr vals))
            (car vals))))
  (falsifiable t (gen-vals (vals t))))