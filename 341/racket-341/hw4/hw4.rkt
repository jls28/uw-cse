
#lang racket

(provide (all-defined-out)) ;; so we can put tests in a second file

; Stefan Dierauf sdierauf@cs.washington.edu 1232328

;; put your code below


(define (sequence low high stride)
  (if (> low high)
      (list)
      (cons low (sequence (+ low stride) high stride))))


(define (string-append-map xs suffix)
  (map (lambda (x) (string-append x suffix)) xs))


(define (list-nth-mod xs n)
  (cond
    [(negative? n) (error "list-nth-mod: negative number")]
    [(null? xs) (error "list-nth-mod: empty list")]
    [else (car (list-tail xs (remainder n (length xs))))]))


(define (stream-for-n-steps s n)
  (letrec ([aux (lambda (x) (if (<= x 0)
                                (list)
                                (cons (car (s)) (stream-for-n-steps (cdr (s)) (- n 1)))))])
    (aux n)))


(define funny-number-stream
  (letrec ([fives (lambda (x) (if (= (modulo x 5) 0) (- x) x))]
           [f (lambda (x) (cons (fives x) (lambda () (f (+ x 1)))))])
    (lambda () (f 1))))


(define ztatlock-then-dog
  (letrec ([ztatlock (lambda () (cons "ztatlock.jpg" dog))]
           [dog (lambda () (cons "dog.jpg" ztatlock))])
    (lambda () (ztatlock))))


(define (stream-add-zero s)
  (lambda() (cons (cons 0 (car (s))) (lambda () ((stream-add-zero (cdr (s))))))))


(define (cycle-lists xs ys)
  (letrec ([aux (lambda (n) (cons 
                             (cons (list-nth-mod xs n) 
                                   (list-nth-mod ys n)) 
                             (lambda () (aux (+ n 1)))))])
  (lambda () (aux 0))))


(define (vector-assoc v vec)
  (letrec ([aux (lambda (n) (if (>= n (vector-length vec))
                                #f
                                (letrec ([cur (vector-ref vec n)]
                                         [next (lambda (x) (aux (+ x 1)))])
                                  (if (pair? cur)
                                      (if (equal? (car cur) v)
                                          cur
                                          (next n))
                                      (next n)))))])
    
    (aux 0)))


(define (cached-assoc xs n)
  (letrec ([memo (make-vector n #f)]
           [cur-index 0]
           [aux (lambda (lookup) ;going to return a function to be evaluated
                  (let ([ans (vector-assoc lookup memo)])
                    (if ans
                        ans
                        (let ([new-ans (assoc lookup xs)])
                          ;store new-ans
                          (begin
                            (vector-set! memo cur-index new-ans)
                            ; update cur-index
                            (set! cur-index (modulo (+ cur-index 1) (vector-length memo)))
                            ;return new-ans
                            new-ans)))))])
    aux))


(define-syntax while-less
  (syntax-rules (do)
    [(while-less e1 do e2)
     (letrec ([c e1]
              [aux (lambda (p) (if (< p c)
                                   (begin (aux e2) #t)
                                   #f))])
       (aux e2))]))

