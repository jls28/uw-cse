;; Programming Languages, Homework 5
;; Stefan Dierauf sdierauf@cs 1232328

#lang racket

(require "hw5.rkt")

; some functions because I am lazy
(define (assert b err)
  (if b
      null
      (begin (write (string-append err "\n")))))

; i am v lazy
(define eq (lambda (a b) (equal? a b)))
(define e2i (lambda (e) (int-num (eval-exp e))))

; a test case that uses problems 1, 2, and 4
; should produce (list (int 10) (int 11) (int 16))
(define test1
  (mupllist->racketlist
   (eval-exp (call (call mupl-mapAddN (int 7))
                   (racketlist->mupllist 
                    (list (int 3) (int 4) (int 9)))))))

; some eval tests

; add
(assert (eq (int-num (eval-exp (add (int 1) (int 2)))) 3) "add simple test")
(assert (eq (e2i (add (int 1) (int 2))) 3) "add simple test")
(assert (eq (e2i (add (int 1) (add (int 1) (int 2)))) 4) "add 1 layer test")

; apair/fst
(assert (eq (e2i (fst (apair (int 1) (int 2)))) 1) "get first el of pair")
(assert (eq (e2i (fst (apair (add (int 1) (int 10)) (int 2)))) 11) "get first el of pair 1 layer")

; apair/snd
(assert (eq (e2i (snd (apair (int 1) (int 2)))) 2) "get second el of pair")
(assert (eq (e2i (snd (apair (int 1) (add (int 2) (int 3))))) 5) "get second el of pair 1 layer")

; ifgreater
(assert (eq (e2i (ifgreater (int 10) (int 1) (int 2) (int 3))) 2) "if greater simple test left")
(assert (eq (e2i (ifgreater (int 1) (int 10) (int 2) (int 3))) 3) "if greater simple test right")

; ifeq
(assert (eq (e2i (ifeq (int 1) (int 1) (int 400) (int 200))) 400) "if equal test true")
(assert (eq (e2i (ifeq (int 1) (int 5) (int 400) (int 200))) 200) "if equal test right side greater")
(assert (eq (e2i (ifeq (int 8) (int 1) (int 400) (int 200))) 200) "if equal test left side greater")

; isauinit
(assert (eq (e2i (isaunit (aunit))) 1) "isaunit true")
(assert (eq (e2i (isaunit (int 0))) 0) "isaunit false")
(assert (eq (e2i (isaunit (apair (aunit) (aunit)))) 0) "isaunit false 1 layer")

; ...function tests 
; incr function
(assert (eq (e2i (call (fun "incr" "x" (add (var "x") (int 1)))(int 10))) 11) "simple increment function")
; simple recursion
(assert (eq (e2i (call 
                  (fun "recurse10" "x" (ifgreater (int 0) (var "x")
                                             (int 100)
                                             (call (var "recurse10") (add (var "x") (int -1)))))
                  (int 10))) 100) "function should recurse 10 times then return 100")
; list sum
(assert (eq (e2i
             (call (fun "listsum" "xs"
                        (ifgreater (isaunit (var "xs")) (int 0)
                                   (int 0)
                                   (add (fst (var "xs")) (call (var "listsum") (snd (var "xs"))))))
                   (apair (int 5) (apair (int 6) (apair (int 7) (apair (int 20) (aunit))))))) 
              38) "simple list sum function")
; mlet* stuff
(assert (eq (e2i
             (mlet* (list (cons "x" (int 10)) (cons "y" (int 20)) (cons "z" (int 30)))
                    (add (var "x") (add (var "y") (var "z"))))) 60)
        "mlet some vars yee")

(assert (eq (e2i
             (mlet* (list (cons "x" (int 10))
                          (cons "incr" (fun #f "y" (add (int 1) (var "y")))))
                    (call (var "incr") (var "x"))))
            11)
        "mlet a function and a var")
; mlet* two functions, one of which calls the other
(assert (eq (e2i
             (mlet* (list (cons "incr1" (fun #f "b" (add (int 1) (var "b"))))
                          (cons "incr2"
                                (fun #f "a" (add (int 1) (call (var "incr1") (var "a"))))))
                    (call (var "incr2") (int 10)))) 12) "mlet two functions correct order")

; call function from pair
(assert (eq (e2i
             (mlet* (list (cons "incr" (fun #f "x" (add (int 1) (var "x"))))
                          (cons "intandfun" (apair (int 5) (var "incr"))))
                    (call (snd (var "intandfun")) (fst (var "intandfun")))))
            6) 
        "calling function from apair")

; mapppps
(assert (eq (e2i
             (mlet* (list (cons "list" (apair (int 1) (apair (int 2) (apair (int 3) (aunit)))))
                          (cons "double" (fun #f "x" (call mupl-map (fun #f "element" (add (var "element") (var "element"))))))
                          (cons "fold" 
                                (fun "loop" "xs"
                                     (ifgreater (isaunit (var "xs")) (int 0)
                                                (int 0)
                                                (add (fst (var "xs")) (call (var "loop") (snd (var "xs"))))))))
                    (call (var "fold") (call (call (var "double") (int 0)) (var "list")))))
            12) 
        "fold on a function that doubles a list hot damn")

