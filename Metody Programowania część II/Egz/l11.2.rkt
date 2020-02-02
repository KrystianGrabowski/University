#lang racket
(define/contract (dist x y)
  (-> number? number? number?)
  (abs (- x y)))

(define/contract (square x)
  (-> number? number?)
  (* x x))

(define/contract (inc i)
  (-> integer? integer?)
  (+ i 1))

(define/contract (foo x)
  (-> number? any)  ;; any nie zwraca uwagi na liczbe zwracanych arg 
  (values 'x 3 4))  ;;any/c liczy do 1 nie zwrócisz wiecej 

(define/contract (fun a b)
  (-> integer? integer? any)
  (values 2 3))


;; definicje złożonych kontraktów
(define natural/c (and/c integer? (not/c negative?)))
(define exact-natural/c (and/c natural/c exact?))
(define positive-natural/c (and/c integer? positive?))

(define/contract (fact x)
  (-> exact-natural/c positive-natural/c)
  (if (= 0 x)
      1
      (* x (fact (- x 1)))))

(define/contract (close-enough? x y)
  (-> number? number? boolean?)
  (< (dist x y) 0.0001))

(define/contract (fix-point f x0)
  (-> (-> number? number?) number? number?)
  (let ([x1 (f x0)])
    (if (close-enough? x0 x1)
        x1
        (fix-point f x1))))

(define/contract (average-damp f)
  (-> (-> number? number?) (-> number? number?))
  (lambda (x) (/ (+ (f x) x) 2)))

(define (sqrt-ad x)
  (-> positive? number?)
  (fix-point (average-damp (lambda (y) (/ x y))) 1.0))

(define/contract (deriv f)
  (-> (-> number? number?) (-> number? number?))
  (let ([dx 0.0001])
    (lambda (x) (/ (- (f (+ x dx)) (f x)) dx))))

(define/contract (newton-transform f)
  (-> (-> number? number?) (-> number? number?))
  (lambda (x) (- x (/ (f x) ((deriv f) x))))) 

(define/contract (newtons-method f x)
  (-> (-> number? number?) number? number?)
  (fix-point (newton-transform f) x))

(define/contract (sqrt-nm x)
  (-> positive? number?)
  (newtons-method (lambda (y) (- x (square y))) 1.0))

(define/contract pi positive? (newtons-method sin 3))