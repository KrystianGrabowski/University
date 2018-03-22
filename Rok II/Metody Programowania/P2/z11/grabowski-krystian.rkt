#lang racket

;;pomocincze funkcje potrzebne również w testach więc są poza nth-root
(define (repeated p n)
  (cond [(= n 0) (lambda(x) x)]
        [else (compose p (repeated p (- n 1)))]))

(define (goodenough? a b)
  (< (abs(- a b)) 0.000000001))

(define (fix-point f x0)
  (let ((x1 (f x0)))
    (if (goodenough? x0 x1)
        x0
        (fix-point f x1))))

(define (average-damp f)
  (lambda (x) (/ (+ x (f x)) 2 )))


(define (nth-root x n)
    (fix-point
     ((repeated
       average-damp (floor (log n 2)))
       (lambda (i)
         (/ x (expt i (- n 1)))))
      1.0))

             

(define (nth-roottest x n z)
    (fix-point
     ((repeated
       average-damp z)
       (lambda (i)
         (/ x (expt i (- n 1)))))
      1.0))

;;ustalanie ilości złożeń
(nth-roottest 4 2 1)
(nth-roottest 8 3 1)
(nth-roottest 16 4 2)
(nth-roottest 32 5 2)
(nth-roottest 64 6 2)
(nth-roottest 128 7 2)
(nth-roottest 256 8 3)
(nth-roottest 512 9 3)
(nth-roottest 1024 10 3)
(nth-roottest 2048 11 3)
(nth-roottest 32768 15 3)
(nth-roottest 65536 16 4)
(nth-roottest 2147483648 31 4)
(nth-roottest 4294967296 32 5)
(nth-roottest 4294967296 32 5)

;;wzor na ilosc złożen określa logarytm przy podstawie 2 ze stopnia pierwiastka

(define (test name real x n)
  (define (compare y)
    (goodenough? real y))
  
  (let ([r (nth-root x n)])
    (printf "[~v] ~%  Value:     ~v~%  nth-root: ~v isGood?:~v ~%"
            name real r (compare r) )))

(printf "~%Nazwy określają [Liczba-stopien]~%")
(test "4 2"      2.0 4 2)
(test "32 5"     2.0 32 5)
(test "512 9"     2.0 512 9)
(test "2 4"      1.1892071150027210667174 2 4)
(test "5 11"     1.1575579117706545686427 5 11)
(test "3 5"      1.2457309396155173259666 3 5)
(test "2 4"      1.1892071150027210667174 2 4)
(test "6 7"      1.2917083420907466068275 6 7)
(test "15 6"     1.5704178024750197353105 15 6)
(test "20 9"     1.3949507939624209793659 20 9)
(test "32 10"    1.4142135623730950488016 32 10)
(test "96 14"    1.3854498257163285666909 96 14)
(test "3^66 66"  3.0 (expt 3 66) 66)
(test "6^66 66"  6.0 (expt 6 66) 66)
(test "21 4"     2.1406951429280723265467 21 4)
(test "12564321456 13" 5.98214380950417829504350264 12564321456 13)


