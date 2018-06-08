#lang racket

;; sygnatura: grafy
(define-signature graph^
  ((contracted
    [graph        (-> list? (listof edge?) graph?)]
    [graph?       (-> any/c boolean?)]
    [graph-nodes  (-> graph? list?)]
    [graph-edges  (-> graph? (listof edge?))]
    [edge         (-> any/c any/c edge?)]
    [edge?        (-> any/c boolean?)]
    [edge-start   (-> edge? any/c)]
    [edge-end     (-> edge? any/c)]
    [has-node?    (-> graph? any/c boolean?)]
    [outnodes     (-> graph? any/c list?)]
    [remove-node  (-> graph? any/c graph?)]
    )))

;; prosta implementacja grafów
(define-unit simple-graph@
  (import)
  (export graph^)

  (define (graph? g)
    (and (list? g)
         (eq? (length g) 3)
         (eq? (car g) 'graph)))

  (define (edge? e)
    (and (list? e)
         (eq? (length e) 3)
         (eq? (car e) 'edge)))

  (define (graph-nodes g) (cadr g))

  (define (graph-edges g) (caddr g))

  (define (graph n e) (list 'graph n e))

  (define (edge n1 n2) (list 'edge n1 n2))

  (define (edge-start e) (cadr e))

  (define (edge-end e) (caddr e))

  (define (has-node? g n) (not (not (member n (graph-nodes g)))))
  
  (define (outnodes g n)
    (filter-map
     (lambda (e)
       (and (eq? (edge-start e) n)
            (edge-end e)))
     (graph-edges g)))

  (define (remove-node g n)
    (graph
     (remove n (graph-nodes g))
     (filter
      (lambda (e)
        (not (eq? (edge-start e) n)))
      (graph-edges g)))))

;; sygnatura dla struktury danych
(define-signature bag^
  ((contracted
    [bag?       (-> any/c boolean?)]
    [empty-bag  (and/c bag? bag-empty?)]
    [bag-empty? (-> bag? boolean?)]
    [bag-insert (-> bag? any/c (and/c bag? (not/c bag-empty?)))]
    [bag-peek   (-> (and/c bag? (not/c bag-empty?)) any/c)]
    [bag-remove (-> (and/c bag? (not/c bag-empty?)) bag?)])))

;; struktura danych - stos
(define-unit bag-stack@
  (import)
  (export bag^)

  (define (bag? b)
    (list? b))

  (define (bag-empty? b)
    (null? b))
  
  (define empty-bag
    '())

  (define (bag-insert b x)
    (cons x b))

  (define (bag-peek b)
    (car b))

  (define (bag-remove b)
    (cdr b))
)

;; struktura danych - kolejka FIFO
;; do zaimplementowania przez studentów
(define-unit bag-fifo@
  (import)
  (export bag^)
  
  (define (bag? b)
    (and (pair? b)
         (list? (first b))
         (list? (second b))))

  (define (bag-empty? b)
    (and (null? (first b))
         (null? (second b))))
  
  (define empty-bag
    (list '() '()))

  (define (bag-insert b x)
    (list (cons x (first b)) (second b)))

  (define (bag-peek b)
    (if (null? (second b))
        (car (reverse (first b)))
        (car (second b))))

  (define (bag-remove b)
    (if (null? (second b))
        (list '() (cdr (reverse (first b))))
        (list (first b) (cdr (second b)))))
  
)

;; sygnatura dla przeszukiwania grafu
(define-signature graph-search^
  (search))

;; implementacja przeszukiwania grafu
;; uzależniona od implementacji grafu i struktury danych
(define-unit/contract graph-search@
  (import bag^ graph^)
  (export (graph-search^
           [search (-> graph? any/c (listof any/c))]))
  (define (search g n)
    (define (it g b l)
      (cond
        [(bag-empty? b) (reverse l)]
        [(has-node? g (bag-peek b))
         (it (remove-node g (bag-peek b))
             (foldl
              (lambda (n1 b1) (bag-insert b1 n1))
              (bag-remove b)
              (outnodes g (bag-peek b)))
             (cons (bag-peek b) l))]
        [else (it g (bag-remove b) l)]))
    (it g (bag-insert empty-bag n) '()))
  )

;; otwarcie komponentu grafu
(define-values/invoke-unit/infer simple-graph@)

;; graf testowy
(define test-graph
  (graph
   (list 1 2 3 4)
   (list (edge 1 3)
         (edge 1 2)
         (edge 2 4))))
;; TODO: napisz inne testowe grafy!

(define graph1
  (graph
   (list 1 2 3 4 5 6 7 8 9 10 11 12)
   (list (edge 1 2)
         (edge 1 3)
         (edge 3 4)
         (edge 3 5)
         (edge 2 6)
         (edge 2 7)
         (edge 4 8)
         (edge 4 9)
         (edge 5 10)
         (edge 5 11)
         (edge 6 12))))

(define graph2
  (graph
   (list 1 2 3 4 5 6 7 8 9 10)
   (list (edge 1 2)
         (edge 2 3)
         (edge 3 4)
         (edge 4 5)
         (edge 5 6)
         (edge 6 7)
         (edge 7 8)
         (edge 8 9)
         (edge 9 10))))

(define graph3
  (graph
   (list 1 2 3 4 5 6 7 8 9 10 11 12)
   (list (edge 1 2)
         (edge 1 3)
         (edge 1 4)
         (edge 1 5)
         (edge 1 6)
         (edge 1 7)
         (edge 1 8)
         (edge 1 9)
         (edge 1 10)
         (edge 10 11)
         (edge 10 12)
         )))


;; otwarcie komponentu stosu
(define-values/invoke-unit/infer bag-stack@)
;; opcja 2: otwarcie komponentu kolejki
;(define-values/invoke-unit/infer bag-fifo@)

;; testy w Quickchecku
(require quickcheck)

;; test przykładowy: jeśli do pustej struktury dodamy element
;; i od razu go usuniemy, wynikowa struktura jest pusta
(quickcheck
 (property ([s arbitrary-symbol])
           (bag-empty? (bag-remove (bag-insert empty-bag s)))))

(quickcheck
 (property ([s1 arbitrary-symbol]
            [s2 arbitrary-symbol])
           (not (bag-empty? (bag-insert (bag-insert empty-bag s1) s2)))))



;;stack
;(quickcheck
; (property ([s1 arbitrary-symbol]
;           [s2 arbitrary-symbol])
;          (eq? (bag-peek (bag-insert(bag-insert empty-bag s1) s2)) s2)))

;;fifo
;(quickcheck
; (property ([s1 arbitrary-symbol]
;            [s2 arbitrary-symbol])
;           (eq? (bag-peek (bag-insert (bag-insert empty-bag s1) s2)) s1)))

;; TODO: napisz inne własności do sprawdzenia!
;; jeśli jakaś własność dotyczy tylko stosu lub tylko kolejki,
;; wykomentuj ją i opisz to w komentarzu powyżej własności

;; otwarcie komponentu przeszukiwania
(define-values/invoke-unit/infer graph-search@)

;; uruchomienie przeszukiwania na przykładowym grafie
(search test-graph 1)
(search graph1 1)
(search graph2 1)
(search graph3 1)
