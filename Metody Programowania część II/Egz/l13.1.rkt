#lang racket

(require racklog)

;;predykat male zbior mezczyzn

(define %male
  (%rel ()
        [('adam)]
        [('john)]
        [('joshua)]
        [('mark)]
        [('david)]))


;;predykat female zbior kobiet

(define %female
  (%rel ()
        [('eve)]
        [('helen)]
        [('ivonne)]
        [('anna)]))

;relacja bycia rodzicem
(define %parent
  (%rel ()
        [('adam 'helen)]
        [('adam 'ivonne)]
        [('adam 'anna)]
        [('eve 'helen)]
        [('eve 'ivonne)]
        [('eve 'anna)]
        [('john 'joshua)]
        [('helen 'joshua)]
        [('ivonne 'david)]
        [('mark 'david)]))

;;predykat %sibling relacja bycia rodzensttwem
(define %sibling
  (%rel (a b c)
        [(a b)
         (%parent c a)
         (%parent c b)])) ;; a b są w relacji jesli <-

(define %sister
  (%rel (a b)
        [(a b)
         (%sibling a b)
         (%female a)]))

(define %ancestor
  (%rel (a b c)
        [(a b)
         (%parent a b)]
        [(a b)
         (%parent a c)
         (%parent c b)]))

;;#####1#####
(define %grandson
  (%rel (a b c)
        [(%parent b c)
         (%parent c a)]))
;;unarny -> 1 | binarny -> 2 parametry
(define %cousin
  (%rel (a b c d)
        [ (a b)
         (%parent c a)
         (%sibling c d)
         (%parent d b)]))

;;######2#####
;(%find-all () (%ancestor 'john 'jark))
;(%find-all (x) (%ancestor 'adam x))
;(%find-all (x) (%sister x 'ivonne))
(%find-all (x y) (%cousin x y))