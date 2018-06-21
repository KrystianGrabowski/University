#lang racket

;;; rozdział 3.1.1

(define balance 100)

(define (withdraw amount)
  (if (>= balance amount)
      (begin (set! balance (- balance amount))
             balance)
      "Insufficient funds"))

;: (withdraw 25)
;: (withdraw 25)
;: (withdraw 60)
;: (withdraw 15)

(define new-withdraw
  (let ((balance 100))
    (lambda (amount)
      (if (>= balance amount)
          (begin (set! balance (- balance amount))
                 balance)
          "Insufficient funds"))))


(define (make-withdraw balance)
  (lambda (amount)
    (if (>= balance amount)
        (begin (set! balance (- balance amount))
               balance)
        "Insufficient funds")))


;: (define W1 (make-withdraw 100))
;: (define W2 (make-withdraw 100))
;: (W1 50)
;: (W2 70)
;: (W2 40)
;: (W1 40)

;;(define (make-account balance)
;;  (define (withdraw amount)
;;    (if (>= balance amount)
;;        (begin (set! balance (- balance amount))
;;               balance)
;;        "Insufficient funds"))
;;  (define (deposit amount)
;;    (set! balance (+ balance amount))
;;    balance)
;;  (define (dispatch m)
;;    (cond ((eq? m 'withdraw) withdraw)
;;          ((eq? m 'deposit) deposit)
;;          (else (error "Unknown request -- MAKE-ACCOUNT"
;;                       m))))
;;  dispatch)

;: (define acc (make-account 100))

;: ((acc 'withdraw) 50)
;: ((acc 'withdraw) 60)
;: ((acc 'deposit) 40)
;: ((acc 'withdraw) 60)

;;; rozdział 3.1.3

(define (make-simplified-withdraw balance)
  (lambda (amount)
    (set! balance (- balance amount))
    balance))


;: (define W (make-simplified-withdraw 25))
;: (W 20)
;: (W 10)


(define (make-decrementer balance)
  (lambda (amount)
    (- balance amount)))

;: (define D (make-decrementer 25))
;: (D 20)
;: (D 10)

;: ((make-decrementer 25) 20)
;: ((lambda (amount) (- 25 amount)) 20)
;: (- 25 20)

;: ((make-simplified-withdraw 25) 20)

;: ((lambda (amount) (set! balance (- 25 amount)) 25) 20)
;: (set! balance (- 25 20)) 25

;;; Toższamość obiektów

;: (define D1 (make-decrementer 25))
;: (define D2 (make-decrementer 25))
;: 
;: (define W1 (make-simplified-withdraw 25))
;: (define W2 (make-simplified-withdraw 25))
;: 
;: (W1 20)
;: (W1 20)
;: (W2 20)

;: (define peter-acc (make-account 100))
;: (define paul-acc (make-account 100))
;: 
;: (define peter-acc (make-account 100))
;: (define paul-acc peter-acc)

;;; Kłopoty z programowaniem imperatywnym

(define (factorial n)
  (define (iter product counter)
    (if (> counter n)
        product
        (iter (* counter product)
              (+ counter 1))))
  (iter 1 1))

(define (factorial1 n)
  (let ((product 1)
        (counter 1))
    (define (iter)
      (if (> counter n)
          product
          (begin (set! product (* counter product))
                 (set! counter (+ counter 1))
                 (iter))))
    (iter)))


;;z1l14


(define (make-account p balance)
  (define (withdraw amount)
    (if (>= balance amount)
        (begin (set! balance (- balance amount))
               balance)
        "Insufficient funds"))
  (define (sprawdzenie h m)
    (if (eq? h p)
        (dispatch m)
        'incorrect-password))
  
  (define (deposit amount)
    (set! balance (+ balance amount))
    balance)
  (define (dispatch m)
    (cond ((eq? m 'withdraw) withdraw)
          ((eq? m 'deposit) deposit)
          (else (error "Unknown request -- MAKE-ACCOUNT"
                       m))))
  sprawdzenie)


;;;z2l14
(define (make-cycle-helper or-list list)
  (if (null? (mcdr list))
      (set-mcdr! list or-list)
      (make-cycle-helper or-list (mcdr list))))

(define (make-cycle list)
  (if (null? list)
      null
      (make-cycle-helper list list)))

;;z3l14
(define (has-cycle? list)
  (define (contains? list elem)
    (if (null? list)
        false
        (if (eq? (mcar list) elem)
            true
            (contains? (mcdr list) elem))))

  (define (has-cycle-helper visited list)
    (if (null? list)
        false
        (if (contains? visited list)
            true
            (has-cycle-helper (mcons list visited) (mcdr list)))))
  (has-cycle-helper '() list))


(define (has-cycle2? m) ;;mcdr
  (define (pom m1 m2)
    (cond [(or (null? m2) (null? (mcdr m2))) #t]
          [(eq? m1 m2) #t]
          [else (pom (mcdr m1) (mcdr (mcdr m2)))]))
  (if (null? m)
      #t
      (pom m (mcdr m))))