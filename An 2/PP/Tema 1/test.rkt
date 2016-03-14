#lang racket

(require test-engine/racket-tests)
(include "decision-tree-test.rkt")


;; pentru frunze:

;; primește un nod; întoarce #t dacă acesta este frunză, #f altfel
(define is-leaf?
  ; TODO
  (λ (node)
    (if (equal? (length node) 1) #t #f)))

;; primște un nod frunză; întoarce clasa exemplelor din frunză
(define get-leaf-class
  ; TODO
  (λ (node) (car (last node)))
  )


;; pentru frunze speciale (BONUS):

;; primște un nod; întoarce #t dacă nodul este frunză specială (frunză fără exemple sau cu exemple de clase diferite), #f altfel
;; dacă nu implementați bonus, trebuie ca funcția să întoarcă #f
(define is-special-leaf?
  ; TODO
  (λ (node) #f)
  )

;; primște un nod frunză specială; întoarce tipul frunzei speciale (trebuie să fie unul dintre membrii 2 și 3 ai strings
;; clasa exemplelor din frunza specială va fi verificată tot cu get-leaf-class
(define get-special-leaf-type
  ; TODO
  (λ (node) #f)
  )


;; pentru noduri care nu sunt frunze:

;; primște un nod; întoarce numele atributului verificat în nod
(define get-attribute-name
  ; TODO
  (λ (node) 
    (if (list? (car node)) (caar node) (car node))
  ))

;; primește un nod și o valoare a atributului verificat în nod
;; întoarce nodul copil (nod intern sau frunză) corespunzător valorii date
(define get-child
  ; TODO
  (λ (node value) 
    (cddr (car (filter (λ(x) (member value x)) node))))
  )


;; opțional: verificare nod
;; primește un argument; întoarce #t dacă argumentul este o reprezentare corectă a unui nod (frunză sau nu) din arbore; #f altfel
(define is-node?
  ; TODO
  (λ (node) 
    (if (> (length node) 0) #t #f))
  )


; asamblare funcții de acces arbore
(define functions (list is-leaf? get-leaf-class is-special-leaf? get-special-leaf-type get-attribute-name get-child is-node?))


;; TASK (pregătitor):
;; scrieți (manual) în formatul ales un arbore de decizie pentru exemple conținând 1 atribut - shape, care are două valori - round și square
;; un exemplu va fi în clasa "yes" dacă este rotund, și în "no" altfel
;; arborele trebuie să fie astfel:
;;    shape
;;     / \
;; round square
;;   /     \
;; yes     no
(define tree-1 
  ;'(((shape . round)(classname . yes)) ((shape . square)(classname . no)))
  '((shape round (yes)) (shape square (no)))
  ;((Food great (Chat yes (Speedy yes (yes)) (Speedy no (no))) (Chat no (yes))) (Food mediocre (no)))
  )

(check-expect (is-node? tree-1) #t)
(check-expect (is-leaf? tree-1) #f)
(check-expect (get-attribute-name tree-1) 'shape)
(check-expect (not (get-child tree-1 'round)) #f)
(check-expect (not (get-child tree-1 'square)) #f)
(check-expect (is-leaf? (get-child tree-1 'round)) #t)
(check-expect (is-leaf? (get-child tree-1 'square)) #t)
(check-expect (is-special-leaf? (get-child tree-1 'round)) #f)
(check-expect (get-leaf-class (get-child tree-1 'round)) 'yes)
(check-expect (get-leaf-class (get-child tree-1 'square)) 'no)


;; TASK
;; scrieți funcția de mai jos pentru a calcula entropia unui set de exemple, fiecare exemplu conținând informație despre clasa sa
;; funcția log2 este implementată în decision-tree-test

;; examples: o listă de exemple (setul S), nevidă, în care fiecare exemplu este o listă de perechi, una dintre ele fiind (<nume-atribut-clasă> <clasă>)
;; class-attribute: o listă de forma (<nume-atribut-clasă> <clasă-1> <clasă-2> <clasă-3>)
;; întoarce: entropia setului de exemple în raport cu clasa, H(S) = - sumă-peste-clase p(clasă)*log2 p(clasă)
;;   unde p(clasă) este numărul de exemple cu clasa <clasă> împărțit la numărul de exemple din setul S
(define compute-enthropy
  (λ (examples class-attribute)
    (- 0 (apply + 0 (map (λ(z) (* (/ z (length examples)) (log2 (/ z (length examples))))) (filter (λ(f) (not (equal? f 0))) (map (λ(d) (count (λ(y) (equal? d y)) (filter (λ(f) (not (equal? (car class-attribute) f))) (flatten (map (λ(x) (filter (λ(n) (and (equal? (cdr n) d) (equal? (car n) (car class-attribute)))) x)) examples))))) (cdr class-attribute))))))
    ))

(define tolerance 0.001)
;(check-within (compute-enthropy '() '(classname yes no)) 0 tolerance) ; expect error
(check-within (compute-enthropy '(((shape . round) (classname . yes)) ((shape . square) (classname . yes))) '(classname yes no)) 0 tolerance)
(check-within (compute-enthropy '(((shape . round) (classname . no)) ((shape . square) (classname . no))) '(classname yes no)) 0 tolerance)
(check-within (compute-enthropy '(((shape . round) (classname . yes)) ((shape . square) (classname . no))) '(classname yes no)) 1 tolerance)
(check-within (compute-enthropy '(((shape . round) (classname . yes)) ((shape . square) (classname . no)) ((shape . square) (classname . no))) '(classname yes no maybe)) 0.918 tolerance)
(check-within (compute-enthropy '(((shape . round) (classname . yes)) ((shape . square) (classname . no)) ((shape . square) (classname . maybe))) '(classname yes no maybe)) 1.584 tolerance)

;; TASK
;; scrieți funcția de mai jos pentru a calcula câștigul informațional al unui atribut în raport cu clasa, pentru un set de exemple

;; examples: o listă de exemple, nevidă, în care fiecare exemplu este o listă de perechi, una dintre ele fiind (<nume-atribut-clasă> <clasă>)
;; attribute: o listă de forma (<nume-atribut> <valore-1> <valoare-2> <valoare-3>)
;; class-attribute: o listă de forma (<nume-atribut-clasă> <clasă-1> <clasă-2> <clasă-3>)
;; întoarce: câștigul informațional al atributului, G(S, A) = H(S) - sumă-peste-valori-A p(v)*H(Sv)
;;   unde p(v) este numărul de exemple cu valoarea v pentru A împărțit la numărul de exemple din S
;;   iar Sv este mulțimea exemplelor din S care au valoarea v pentru A
(define compute-gain
  (λ (examples attribute class-attribute)
    ;(- (compute-enthropy examples class-attribute) (apply + 0 (map (λ(a b) (* a (/ b (length examples)))) (map (λ(k) (compute-enthropy (filter (λ(j) (equal? (cdr (car j)) k)) examples) class-attribute)) (cdr attribute)) (map (λ(d) (count (λ(y) (equal? d y)) (filter (λ(f) (not (equal? (car attribute) f))) (flatten (map (λ(x) (filter (λ(n) (and (equal? (cdr n) d) (equal? (car n) (car attribute)))) x)) examples))))) (cdr attribute)))))))
    (- (compute-enthropy examples class-attribute) (apply + 0 (map (λ(a b) (* a (/ b (length examples)))) (map (λ(k) (compute-enthropy (filter (λ(u) (not (equal? 
                           (member (cons (car attribute) k) u) #f))) examples) class-attribute)) (cdr attribute)) (map (λ(d) (count (λ(y) (equal? d y))
                          (filter (λ(f) (not (equal? (car attribute) f))) 
                      (flatten (map (λ(x) (filter (λ(n) (and (equal? (cdr n) d) (equal? (car n) (car attribute)))) x)) examples))))) (cdr attribute)))))))

(check-within (compute-gain 
               '(((shape . round) (classname . yes)) ((shape . square) (classname . yes)))
               '(shape round square)
               '(classname yes no)
               ) 0 tolerance)
(check-within (compute-gain 
               '(((shape . round) (classname . no)) ((shape . square) (classname . yes)))
               '(shape round square)
               '(classname yes no)
               ) 1 tolerance)
(check-within (compute-gain 
               '(((shape . round) (classname . no)) ((shape . round) (classname . yes)))
               '(shape round square)
               '(classname yes no)
               ) 0 tolerance)
(check-within (compute-gain 
               '(((shape . round) (size . 1) (classname . yes))
                 ((shape . round) (size . 2) (classname . no))
                 ((shape . square) (size . 1) (classname . yes))
                 ((shape . square) (size . 2) (classname . yes)))
               '(shape round square)
               '(classname yes no)
               ) 0.311 tolerance)
(check-within (compute-gain 
               '(((shape . round) (size . 1) (classname . yes))
                 ((shape . round) (size . 2) (classname . no))
                 ((shape . square) (size . 1) (classname . yes))
                 ((shape . square) (size . 2) (classname . no))
                 ((shape . square) (size . 2) (classname . yes)))
               '(size 1 2)
               '(classname yes no)
               ) 0.419 tolerance)



;; TASK
;; creați un arbore de decizie pentur mulțimea dată de exemple, pentru muțimea dată de atribute, și pentru clasa dată

;; examples: o listă de exemple, nevidă, în care fiecare exemplu este o listă de perechi, una dintre ele fiind (<nume-atribut-clasă> <clasă>)
;; attributes: o listă de liste de forma (<nume-atribut> <valore-1> <valoare-2> <valoare-3>)
;; class-attribute: o listă de forma (<nume-atribut-clasă> <clasă-1> <clasă-2> <clasă-3>)
;; întoarce: un arbore de decizie, în formatul ales, corespunzător cu argumentele date

(define ex '(
   ((Food . great) (Chat . yes) (Speedy . no) (Price . high) (Bar . no) (BigTip . no))
   ((Food . great) (Chat . no) (Speedy . no) (Price . high) (Bar . no) (BigTip . yes))
   ((Food . mediocre) (Chat . yes) (Speedy . no) (Price . high) (Bar . no) (BigTip . no))
   ((Food . great) (Chat . yes) (Speedy . yes) (Price . adequate) (Bar . yes) (BigTip . yes))))

(define cls '(BigTip yes no))

(define att-set '((Food great mediocre) (Chat yes no) (Speedy yes no) (Price adequate high) (Bar yes no)))

(define (check-last-class examples)
  (if (null? (filter (λ(clasa) (not (equal? (car (map (λ(exemplu) (cdr (last exemplu))) examples)) clasa))) (map (λ(exemplu) (cdr (last exemplu))) examples))) #t #f)
  )

(define (delete-max-atr examples attribute class-attribute)
  (remove (assoc (get-max-atr examples attribute class-attribute) attribute) attribute))

(define (get-max-atr examples attribute class-attribute)
  (car (car (sort attribute (λ(a b) (> (compute-gain examples a class-attribute) (compute-gain examples b class-attribute)))))))

(define (get-examples-with-attribute examples atribut value)
  (filter (λ(exemplu) (equal? (cdr (assoc atribut exemplu)) value)) examples))

(define (get-atr-values examples attribute class-attribute)
  (cdr (car (sort attribute (λ(a b) (> (compute-gain examples a class-attribute) (compute-gain examples b class-attribute)))))))

(define create-tree
  (λ (examples attributes class-attribute)
    ;(map (λ(atribut) (cons (car (car (sort attribute (λ(a b) (> (compute-gain examples a class-attribute) (compute-gain examples b class-attribute)))))) atribut)) (cdr (car (sort attribute (λ(a b) (> (compute-gain examples a class-attribute) (compute-gain examples b class-attribute)))))))
    (if (equal? (check-last-class examples) #t) 
        (list (list (cdr (last (car examples)))))
        (for/list ([v (get-atr-values examples attributes class-attribute)])
          ;(cons (cons (get-max-atr examples attributes class-attribute) (list v)) (list (create-tree (get-examples-with-attribute examples (get-max-atr examples attributes class-attribute) v) (delete-max-atr examples attributes class-attribute) class-attribute))))
          (cons (get-max-atr examples attributes class-attribute) (cons v (create-tree (get-examples-with-attribute examples (get-max-atr examples attributes class-attribute) v) (delete-max-atr examples attributes class-attribute) class-attribute))))
        )))

(define I-DID-THE-BONUS #f)

(check-expect (perform-test functions 'food-small create-tree) #t)
(check-expect (perform-test functions 'food-big create-tree) #t)
(check-expect (perform-test functions 'objects create-tree) #t)
(check-expect (perform-test functions 'weather create-tree) #t)

(check-expect (and (perform-test functions 'food-small create-tree) (get-tree-height functions (get-tree 'food-small create-tree) (get-test 'food-small))) 2)
(check-expect (and (perform-test functions 'food-big create-tree)   (get-tree-height functions (get-tree 'food-big create-tree) (get-test 'food-big)))   4)
(check-expect (and (perform-test functions 'weather create-tree)    (get-tree-height functions (get-tree 'weather create-tree) (get-test 'weather)))    3)
(check-expect (and (perform-test functions 'objects create-tree)    (get-tree-height functions (get-tree 'objects create-tree) (get-test 'objects)))    3)

(if I-DID-THE-BONUS (display "BONUS DONE\n") (display "bonus not done\n"))
(check-expect (if I-DID-THE-BONUS (perform-test functions 'bonus create-tree) #t) #t)
(when I-DID-THE-BONUS (display (get-tree 'bonus create-tree)) (newline))



(test)