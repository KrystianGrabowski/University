#lang racket

;; pomocnicza funkcja dla list tagowanych o określonej długości
(define (tagged-tuple? tag len p)
  (and (list? p)
       (= (length p) len)
       (eq? (car p) tag)))

(define (tagged-list? tag p)
  (and (pair? p)
       (eq? (car p) tag)
       (list? (cdr p))))

;; reprezentacja danych wejściowych (z ćwiczeń)
(define (var? x)
  (symbol? x))

(define (var x)
  x)

(define (var-name x)
  x)

;; przydatne predykaty na zmiennych
(define (var<? x y)
  (symbol<? x y))

(define (var=? x y)
  (eq? x y))

(define (literal? x)
  (and (tagged-tuple? 'literal 3 x)
       (boolean? (cadr x))
       (var? (caddr x))))

(define (literal pol x)
  (list 'literal pol x))

(define (literal-pol x)
  (cadr x))

(define (literal-var x)
  (caddr x))

(define (clause? x)
  (and (tagged-list? 'clause x)
       (andmap literal? (cdr x))))

(define (clause . lits)
  (cons 'clause lits))

(define (clause-lits c)
  (cdr c))

(define (cnf? x)
  (and (tagged-list? 'cnf x)
       (andmap clause? (cdr x))))

(define (cnf . cs)
    (cons 'cnf cs))

(define (cnf-clauses x)
  (cdr x))

;; oblicza wartość formuły w CNF z częściowym wartościowaniem. jeśli zmienna nie jest
;; zwartościowana, literał jest uznawany za fałszywy.
(define (valuate-partial val form)
  (define (val-lit l)
    (let ((r (assoc (literal-var l) val)))
      (cond
       [(not r)  false]
       [(cadr r) (literal-pol l)]
       [else     (not (literal-pol l))])))
  (define (val-clause c)
    (ormap val-lit (clause-lits c)))
  (andmap val-clause (cnf-clauses form)))

;; reprezentacja dowodów sprzeczności

(define (axiom? p)
  (tagged-tuple? 'axiom 2 p))

(define (proof-axiom c)
  (list 'axiom c))

(define (axiom-clause p)
  (cadr p))

(define (res? p)
  (tagged-tuple? 'resolve 4 p))

(define (proof-res x pp pn)
  (list 'resolve x pp pn))

(define (res-var p)
  (cadr p))

(define (res-proof-pos p)
  (caddr p))

(define (res-proof-neg p)
  (cadddr p))

;; sprawdza strukturę, ale nie poprawność dowodu
(define (proof? p)
  (or (and (axiom? p)
           (clause? (axiom-clause p)))
      (and (res? p)
           (var? (res-var p))
           (proof? (res-proof-pos p))
           (proof? (res-proof-neg p)))))

;; procedura sprawdzająca poprawność dowodu
(define (check-proof pf form)
  (define (run-axiom c)
    (displayln (list 'checking 'axiom c))
    (and (member c (cnf-clauses form))
         (clause-lits c)))
  (define (run-res x cpos cneg)
    (displayln (list 'checking 'resolution 'of x 'for cpos 'and cneg))
    (and (findf (lambda (l) (and (literal-pol l)
                                 (eq? x (literal-var l))))
                cpos)
         (findf (lambda (l) (and (not (literal-pol l))
                                 (eq? x (literal-var l))))
                cneg)
         (append (remove* (list (literal true x))  cpos)
                 (remove* (list (literal false x)) cneg))))
  (define (run-proof pf)
    (cond
     [(axiom? pf) (run-axiom (axiom-clause pf))]
     [(res? pf)   (run-res (res-var pf)
                           (run-proof (res-proof-pos pf))
                           (run-proof (res-proof-neg pf)))]
     [else        false]))
  (null? (run-proof pf)))


;; reprezentacja wewnętrzna

;; sprawdza posortowanie w porządku ściśle rosnącym, bez duplikatów
(define (sorted? vs)
  (or (null? vs)
      (null? (cdr vs))
      (and (var<? (car vs) (cadr vs))
           (sorted? (cdr vs)))))

(define (sorted-varlist? x)
  (and (list? x)
       (andmap var? x)
       (sorted? x)))

;; klauzulę reprezentujemy jako parę list — osobno wystąpienia pozytywne i negatywne. Dodatkowo
;; pamiętamy wyprowadzenie tej klauzuli (dowód) i jej rozmiar.
(define (res-clause? x)
  (and (tagged-tuple? 'res-int 5 x)
       (sorted-varlist? (second x))
       (sorted-varlist? (third x))
       (= (fourth x) (+ (length (second x)) (length (third x))))
       (proof? (fifth x))))

(define (res-clause pos neg proof)
  (list 'res-int pos neg (+ (length pos) (length neg)) proof))

(define (res-clause-pos c)
  (second c))

(define (res-clause-neg c)
  (third c))

(define (res-clause-size c)
  (fourth c))

(define (res-clause-proof c)
  (fifth c))

;; przedstawia klauzulę jako parę list zmiennych występujących odpowiednio pozytywnie i negatywnie
(define (print-res-clause c)
  (list (res-clause-pos c) (res-clause-neg c)))

;; sprawdzanie klauzuli sprzecznej
(define (clause-false? c)
  (and (null? (res-clause-pos c))
       (null? (res-clause-neg c))))

;; pomocnicze procedury: scalanie i usuwanie duplikatów z list posortowanych
(define (merge-vars xs ys)
  (cond [(null? xs) ys]
        [(null? ys) xs]
        [(var<? (car xs) (car ys))
         (cons (car xs) (merge-vars (cdr xs) ys))]
        [(var<? (car ys) (car xs))
         (cons (car ys) (merge-vars xs (cdr ys)))]
        [else (cons (car xs) (merge-vars (cdr xs) (cdr ys)))]))

(define (remove-duplicates-vars xs)
  (cond [(null? xs) xs]
        [(null? (cdr xs)) xs]
        [(var=? (car xs) (cadr xs)) (remove-duplicates-vars (cdr xs))]
        [else (cons (car xs) (remove-duplicates-vars (cdr xs)))]))

(define (rev-append xs ys)
  (if (null? xs) ys
      (rev-append (cdr xs) (cons (car xs) ys))))

;; TODO: miejsce na uzupełnienie własnych funkcji pomocniczych
(define (exists x vset)
  (if (null? vset)
      #f
      (if (eq? x (car vset))
          #t
          (exists x (cdr vset)))))

(define (varremove x xs)
  (if (null? xs)
      null
      (if (eq? x (car xs))
          (varremove x (cdr xs))
          (cons (car xs) (varremove x (cdr xs))))))

(define (clause-trivial? c)
  (define (triv posvar negvar)
    (if (null? posvar)
        #f
        (if (exists (car posvar) negvar)
            #t
            (triv (cdr posvar) negvar))))
  (triv (res-clause-pos c) (res-clause-neg c)))

(define (find-var pos neg)
  (if (null? pos)
      null
      (if (exists (car pos) neg)
          (car pos)
          (find-var (cdr pos) neg))))

(define (resolve c1 c2)
  (let ([pos (remove-duplicates-vars(merge-vars (res-clause-pos c1) (res-clause-pos c2)))]
        [neg (remove-duplicates-vars(merge-vars (res-clause-neg c1) (res-clause-neg c2)))])
    (let ([p (find-var pos neg)])
      (if (null? p)
          #f
          (let ([final-pos (varremove p pos)]
                [final-neg (varremove p neg)])
            (if (exists p (res-clause-pos c1))
                 (res-clause final-pos
                             final-neg
                             (proof-res p
                                        (res-clause-proof c1)
                                        (res-clause-proof c2)))
                 (res-clause final-pos
                             final-neg
                             (proof-res p
                                        (res-clause-proof c2)
                                        (res-clause-proof c1)))))))))

(define (resolve-single-prove s-clause checked pending)
  ;; TODO: zaimplementuj!
  ;; Poniższa implementacja działa w ten sam sposób co dla większych klauzul — łatwo ją poprawić!
  (define (not-in-resolvents? el xs)
    (if (null? xs)
        #t
        (if (eq? el (car xs))
            #f
            (not-in-resolvents? el (cdr xs)))))
    
    
  (let* ((resolvents-checked   (filter-map (lambda (c) (resolve c s-clause))
                                     checked))
         (resolvents-pending   (filter-map (lambda (c) (resolve c s-clause))
                                     pending))
         (sorted-rsc    (sort resolvents-checked < #:key res-clause-size))
         (sorted-rsp    (sort resolvents-pending < #:key res-clause-size)))
    (cond [(null? resolvents-checked)
           (subsume-add-prove (cons s-clause checked) pending sorted-rsc)]
          [(null? resolvents-pending)
           (subsume-add-prove (cons s-clause checked) pending sorted-rsc)]
          [(= (res-clause-size (car sorted-rsc)) 0)
           (list 'unsat (res-clause-proof (car sorted-rsc)))]
          [(= (res-clause-size (car sorted-rsp)) 0)
            (list 'unsat (res-clause-proof (car sorted-rsp)))]
          [else (resolve-prove (cons s-clause sorted-rsc) pending)])))
            

;; wstawianie klauzuli w posortowaną względem rozmiaru listę klauzul
(define (insert nc ncs)
  (cond
   [(null? ncs)                     (list nc)]
   [(< (res-clause-size nc)
       (res-clause-size (car ncs))) (cons nc ncs)]
   [else                            (cons (car ncs) (insert nc (cdr ncs)))]))

;; sortowanie klauzul względem rozmiaru (funkcja biblioteczna sort)
(define (sort-clauses cs)
  (sort cs < #:key res-clause-size))

;; główna procedura szukająca dowodu sprzeczności
;; zakładamy że w checked i pending nigdy nie ma klauzuli sprzecznej
(define (resolve-prove checked pending)
  (cond
   ;; jeśli lista pending jest pusta, to checked jest zamknięta na rezolucję czyli spełnialna
   [(null? pending) (generate-valuation (sort-clauses checked))]
   ;; jeśli klauzula ma jeden literał, to możemy traktować łatwo i efektywnie ją przetworzyć
   [(= 1 (res-clause-size (car pending)))
    (resolve-single-prove (car pending) checked (cdr pending))]
   ;; w przeciwnym wypadku wykonujemy rezolucję z wszystkimi klauzulami już sprawdzonymi, a
   ;; następnie dodajemy otrzymane klauzule do zbioru i kontynuujemy obliczenia
   [else
    (let* ((next-clause  (car pending))
           (rest-pending (cdr pending))
           (resolvents   (filter-map (lambda (c) (resolve c next-clause))
                                     checked))
           (sorted-rs    (sort-clauses resolvents)))
      (subsume-add-prove (cons next-clause checked) rest-pending sorted-rs))]))

;; procedura upraszczająca stan obliczeń biorąc pod uwagę świeżo wygenerowane klauzule i
;; kontynuująca obliczenia. Do uzupełnienia.
(define (subsume-add-prove checked pending new)
  
  (define (subsum-iter? candidate cs)
    (if (null? cs)
        #f
        (if (subsum? (car cs) candidate)
            #t
            (subsum-iter? candidate (cdr cs)))))
  
  (define (subsum? candidate c)
    (define (subset? c1 c2)
      (if (null? c1)
          #t
          (if (exists (car c1) c2)
              (subset? (cdr c1) c2)
              #f)))
    (and (subset? (res-clause-pos candidate)
                       (res-clause-pos c))
         (subset? (res-clause-neg candidate)
                       (res-clause-neg c))))

  (define (remove-unnec candidate xs)
    (if (null? xs)
        null
        (if (subsum? (car xs) candidate )
            (remove-unnec candidate (cdr xs))
            (cons (car xs) (remove-unnec candidate (cdr xs))))))
                  
  
  (cond
   [(null? new)                 (resolve-prove checked pending)]
   ;; jeśli klauzula do przetworzenia jest sprzeczna to jej wyprowadzenie jest dowodem sprzeczności
   ;; początkowej formuły
   [(clause-false? (car new))   (list 'unsat (res-clause-proof (car new)))]
   ;; jeśli klauzula jest trywialna to nie ma potrzeby jej przetwarzać
   [(clause-trivial? (car new)) (subsume-add-prove checked pending (cdr new))]
   [else
    ;; TODO: zaimplementuj!
    ;; Poniższa implementacja nie sprawdza czy nowa klauzula nie jest lepsza (bądź gorsza) od już
    ;; rozpatrzonych; popraw to!
    
    (let ([checked-bool (subsum-iter? (car new) checked)]
          [pending-bool (subsum-iter? (car new) pending)])
      (if (or checked-bool pending-bool)
          (subsume-add-prove checked pending (cdr new))
          (let ([pendingv2 (remove-unnec (car new) pending)]
                [checkedv2 (remove-unnec (car new) checked)])
            (subsume-add-prove checkedv2 (insert (car new) pendingv2) (cdr new)))))]))
                           

  
  ;; TODO: zaimplementuj!
  ;; Ta implementacja mówi tylko że formuła może być spełniona, ale nie mówi jak. Uzupełnij ją!
(define (generate-valuation resolved)
  
  (define (slg x xs)
    (if (null? xs)
        null
        (let ([pos2 (remove x (res-clause-pos (car xs)))]
              [neg2 (remove x (res-clause-neg (car xs)))])
          (if (and (null? pos2)
                   (null? neg2))
              (slg x (cdr xs))
              (cons (res-clause pos2 neg2 (res-clause-proof (car xs)))
                                   (slg x (cdr xs)))))))
  
  (define (get-var c)
    (cond [(not (null? (res-clause-pos c))) (list (car (res-clause-pos c)) #t)]
          [(not (null? (res-clause-neg c))) (list (car (res-clause-neg c)) #f)]
          [else null]))
        
  
  (define (accumulate xs acc)
    (if (null? xs)
        acc
        (let ([v (get-var (car xs))])
          (if (null? v)
              (accumulate (cdr xs) acc)
              (accumulate (slg (first v) (cdr xs)) (cons v acc))))))
  
  (list 'sat (accumulate resolved null)))


;; procedura przetwarzające wejściowy CNF na wewnętrzną reprezentację klauzul
(define (form->clauses f)
  (define (conv-clause c)
    (define (aux ls pos neg)
      (cond
       [(null? ls)
        (res-clause (remove-duplicates-vars (sort pos var<?))
                    (remove-duplicates-vars (sort neg var<?))
                    (proof-axiom c))]
       [(literal-pol (car ls))
        (aux (cdr ls)
             (cons (literal-var (car ls)) pos)
             neg)]
       [else
        (aux (cdr ls)
             pos
             (cons (literal-var (car ls)) neg))]))
    (aux (clause-lits c) null null))
  (map conv-clause (cnf-clauses f)))

(define (prove form)
  (let* ((clauses (form->clauses form)))
    (subsume-add-prove '() '() clauses)))

;; procedura testująca: próbuje dowieść sprzeczność formuły i sprawdza czy wygenerowany
;; dowód/waluacja są poprawne. Uwaga: żeby działała dla formuł spełnialnych trzeba umieć wygenerować
;; poprawną waluację.
(define (prove-and-check form)
  (let* ((res (prove form))
         (sat (car res))
         (pf-val (cadr res)))
    (if (eq? sat 'sat)
        (valuate-partial pf-val form)
        (check-proof pf-val form))))

;;; TODO: poniżej wpisz swoje testy
(printf "{ v -> alt} ~%")


(printf "~%=====[(p), (-p)]=====~%")
(define c0 '(clause (literal #t p)))
(define c01 '(clause (literal #f p)))
(prove-and-check (cons 'cnf (list c0 c01)))

(printf "~%=====[(pvq), (rv-q), (qv-r), (-p), (-q) ]=====~%")
(define c02 '(clause (literal #t p) (literal #t q)))
(define c03 '(clause (literal #t r) (literal #f q)))
(define c04 '(clause (literal #t r) (literal #f r)))
(define c05 '(clause (literal #f p)))
(define c06 '(clause (literal #f r)))

(prove-and-check (cons 'cnf (list c02 c03)))
(prove-and-check (cons 'cnf (list c02 c03 c04)))
(prove-and-check (cons 'cnf (list c02 c03 c04 c05)))
(prove-and-check (cons 'cnf (list c02 c03 c04 c05 c06)))


;;zainspirowane whitebookiem
(printf "~%=====[(pvq), (-pvq), (pv-q) (-pv-q)]=====~%")
(define c1 '(clause (literal #t p) (literal #t q)))
(define c2 '(clause (literal #f p) (literal #t q)))
(define c3 '(clause (literal #t p) (literal #f q)))
(define c4 '(clause (literal #f p) (literal #f q)))
(prove-and-check (cons 'cnf (list c1 c2)))
(prove-and-check (cons 'cnf (list c1 c4)))
(prove-and-check (cons 'cnf (list c1 c2 c3 c4)))

(printf "~%=====[(pvqvr), (-rv-qv-p), (-qvr) (-rvp)]======~%")
(define c5 '(clause (literal #t p) (literal #t q) (literal #t r)))
(define c6 '(clause (literal #f p) (literal #f q) (literal #f r)))
(define c7 '(clause (literal #f q) (literal #t r)))
(define c8 '(clause (literal #t p) (literal #f r)))
(prove-and-check (cons 'cnf (list c5 c6)))
(prove-and-check (cons 'cnf (list c5 c6 c7)))
(prove-and-check (cons 'cnf (list c5 c6 c7 c8)))

(printf "~%======[(pvr), (qvs), (-pv-q) (-rv-s), (qvr), (svp)]======~%")
(define c9 '(clause (literal #t p) (literal #t r)))
(define c10 '(clause (literal #t q) (literal #t s)))
(define c11 '(clause (literal #f p) (literal #f q)))
(define c12 '(clause (literal #f r) (literal #f s)))
(define c13 '(clause (literal #t q) (literal #t r)))
(define c14 '(clause (literal #t s) (literal #t p)))
(prove-and-check (cons 'cnf (list c9 c10)))
(prove-and-check (cons 'cnf (list c9 c10 c11)))
(prove-and-check (cons 'cnf (list c9 c10 c11 c12 c13)))
(prove-and-check (cons 'cnf (list c9 c10 c11 c12 c13 c14 )))




