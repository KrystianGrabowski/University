#lang racket
;;uzywam distance również w testach więc jest zdefiniowany osobno
(define (distance x y)
  (abs (- x y)))

(define (cont-frac num den)
  (define (betteraprox prev-prev-a prev-a prev-prev-b prev-b w acc)
    (let ([n (num acc)]
          [d (den acc)])
      (let ([an (+ (* d prev-a) (* n prev-prev-a))]
            [bn (+ (* d prev-b) (* n prev-prev-b))])
        (let ([fn (/ an bn)])
          (cond [(isgood? w fn) fn]
                [else (betteraprox prev-a an prev-b bn fn (+ acc 1))])))))
    
  (define (isgood? a b)
    (< (distance a b) 0.0000001))

  (betteraprox 1.0 0.0 0.0 1.0 0.0 1))
  


(define (test name real f1 f2)
  (define (compare x)
    (<= (distance real x) 0.0000001))
  
  (let ([x (cont-frac f1 f2)])
    (printf "~v ~%Value:     ~v~%Cont-frac: ~v isGood?:~v ~%"
            name real x (compare x) )))


;;funkcje pomocnicze do testów             
(define (arctg x)
  (cond [(= x 1) 1]
        [else 2]))
(define (arctg2 x)
  (cond [(= x 1) 1]
        [else (- x 1)]))


(test "->1/złota-liczba" 0.61803398875 (lambda (i) 1.0) (lambda (i) 1.0))
(test "->sqrt 13 - 3 (Część ułamkowa)" 0.60555127546 (lambda (x) 4.0) (lambda (x) 6.0))
(test "->sqrt 18 - 4 (Część ułamkowa)" 0.24264068711 (lambda (x) 2.0) (lambda (x) 8.0))
(test "arctg 1" 0.785398163397448309615660 (lambda(x) (expt (* 1 (arctg2 x)) (arctg x)))
      (lambda(x) (- (* 2 x) 1)))
(test "arctg 12" 1.48765509490645538932065337 (lambda(x) (expt (* 12 (arctg2 x)) (arctg x)))
      (lambda(x) (- (* 2 x) 1)))
(test "arctg -6" -1.40564764938026978095219340 (lambda(x) (expt (* -6 (arctg2 x)) (arctg x)))
      (lambda(x) (- (* 2 x) 1)))
(test "arctg 1/2" 0.463647609000806116214256231 (lambda(x) (expt (* (/ 1 2) (arctg2 x)) (arctg x)))
      (lambda(x) (- (* 2 x) 1)))
(test "arctg 1/8" 0.124354994546761435031354849 (lambda(x) (expt (* (/ 1 8) (arctg2 x)) (arctg x)))
      (lambda(x) (- (* 2 x) 1)))
(test "arctg 2" 1.107148717794090503017065460 (lambda(x) (expt (* 2 (arctg2 x)) (arctg x)))
      (lambda(x) (- (* 2 x) 1)))
(test "arctg 1/100" 0.00999966668666523820634011 (lambda(x) (expt (* (/ 1 100) (arctg2 x)) (arctg x)))
      (lambda(x) (- (* 2 x) 1)))
(test "arctg 1/55" 0.018179815072978280527929851 (lambda(x) (expt (* (/ 1 55) (arctg2 x)) (arctg x)))
      (lambda(x) (- (* 2 x) 1)))