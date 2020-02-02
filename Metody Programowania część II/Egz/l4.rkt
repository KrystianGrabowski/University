#lang racket
(define (fold-right op nval xs)
  (if (null? xs)
      nval
      (op (car xs)
          (fold-right op nval (cdr xs)))))

;(define (fold-left op nval xs)
;  (fold-right op nval (reverse xs)))

(define (fold-left op nval xs)
  (if (null? xs)
      nval
      (fold-left op
                 (op (car xs) nval)
                 (cdr xs))))

;;######1#####

(define (concatMap f xs)
  (if (null? xs)
      null
      (append (f (car xs)) (concatMap f (cdr xs)))))

(define (from-to s e)
  (if (= s e)
      (list s)
      (cons s (from-to (+ s 1) e))))

(define (queens board-size)
  ;; Return the representation of a board with 0 queens inserted
  (define (empty-board)
    (define (iter-gen i xs)
      (if (= i board-size)
          xs
          (iter-gen (+ i 1) (cons 'empty xs))))
    ( iter-gen 0 null)
    )
  ;; Return the representation of a board with a new queen at
  ;; (row, col) added to the partial representation `rest'
  (define (adjoin-position row col rest)
    (define (move i xs)
      (if (= col i)
          (cons row (cdr xs))
          (cons (car xs) (move (+ i 1) (cdr xs)))))
    (move 1 rest)
    )

  ;; Return true if the queen in k-th column does not attack any of
  ;; the others
  (define (safe? k positions)
    
    (define (dist x s)
      (abs (- x s)))
    
    (define (getk-th it p)
      (if (= k it)
          (car p)
          (getk-th (+ it 1) (cdr p))))

    (define (iter val i xs)
      (cond [(= i k) #t]
            [(or (= (car xs) val)
                 (= (dist val (car xs)) (dist k i)))
                 #f]
            [else (iter val (+ i 1) (cdr xs))]))

    (iter (getk-th 1 positions) 1 positions)
    
    )
  ;; Return a list of all possible solutions for k first columns
  (define (queen-cols k)
    (if (= k 0)
        (list (empty-board))
        (filter
         (lambda (positions) (safe? k positions))
         (concatMap
          (lambda (rest-of-queens)
            (map (lambda (new-row)
                   (adjoin-position new-row k rest-of-queens))
                 (from-to 1 board-size)))
          (queen-cols (- k 1))))))
  (queen-cols board-size))


;;########3########

(define (leaf? x)
  (eq? x 'leaf))

(define leaf 'leaf)

(define (node? x)
  (and (list? x)
       (= (length x) 4)
       (eq? (car x) 'node)))

(define (node-val x)
  (cadr x))

(define (node-left x)
  (caddr x))

(define (node-right x)
  (cadddr x))

(define (make-node v l r)
  (list 'node v l r))

(define (tree? t)
  (or (leaf? t)
      (and (node? t)
           (tree? (node-left t))
           (tree? (node-right t)))))

(define (mirror xs)
  (if (leaf? xs)
      xs
      (let ([nodel (node-left xs)]
            [noder (node-right xs)])
        (make-node (node-val xs) (mirror noder) (mirror nodel)))))

;;#######4######


(define (bst-insert x t)
  (cond [(leaf? t)
         (make-node x leaf leaf)]
        [(< x (node-val t))
         (make-node (node-val t)
                    (bst-insert x (node-left t))
                    (node-right t))]
        [else
         (make-node (node-val t)
                    (node-left t)
                    (bst-insert x (node-right t)))]))



(define (flatten xs)
  (define (help lst acc)
    (cond [(leaf? lst) acc]
          [(and (leaf? (node-left lst))
                (leaf? (node-right lst)))
           (cons (node-val lst) acc)]
          [(leaf? (node-left lst))
           (cons (node-val lst) (help (node-right lst) acc))]
          [(leaf? (node-right lst))
           (help (node-left lst) (cons (node-val lst) acc))]
          [else
           (help (node-left lst)
                 (cons (node-val lst)
                       (help (node-right lst) acc)))]))
  (help xs null)
    )


;;######5########
(define (treesort xs)
  (define (treesort-insert ls tree)
    (if (null? ls)
        tree
        (treesort-insert (cdr ls) (bst-insert (car ls) tree))))
  (flatten (treesort-insert xs 'leaf)))


;;#######6########
(define (delete todel tree)

  (define (deleter del tree)
    (cond [(leaf? tree) 'leaf]
          [(and (leaf? (node-left tree))
                (leaf? (node-left tree)))
           'leaf]
          [(leaf? (node-left tree)) (node-right tree)]
          [(leaf? (node-right tree)) (node-left tree)]
          [(= (node-val tree) todel)
           (make-node (minimum (node-right tree))
                      (node-left tree)
                      (delete (minimum (node-right tree)) (node-right tree)))]
          [(< todel (node-val tree))
           (make-node (node-val tree)
                      (delete todel (node-left tree))
                      (node-right tree))]
          [(> todel (node-val tree))
           (make-node (node-val tree)
                      (delete todel (node-right tree))
                      (node-right tree))
           ]))
          
  (define (minimum tree)
    (if (leaf? tree)
        'leaf
        (if (leaf? (node-left tree))
            (node-val tree)
            (minimum (node-left tree)))))
  (deleter todel tree))
                
       
                     


