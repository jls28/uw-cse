#lang racket

(require "hw4.rkt") 

; Stefan Dierauf sdierauf@cs.washington.edu 1232328

;; A simple library for displaying a 2x3 grid of pictures: used
;; for fun in the tests below (look for "Tests Start Here").

(require (lib "graphics.rkt" "graphics"))

(open-graphics)

(define window-name "Programming Languages, Homework 4")
(define window-width 700)
(define window-height 500)
(define border-size 100)

(define approx-pic-width 200)
(define approx-pic-height 200)
(define pic-grid-width 3)
(define pic-grid-height 2)

(define (open-window)
  (open-viewport window-name window-width window-height))

(define (grid-posn-to-posn grid-posn)
  (when (>= grid-posn (* pic-grid-height pic-grid-width))
    (error "picture grid does not have that many positions"))
  (let ([row (quotient grid-posn pic-grid-width)]
        [col (remainder grid-posn pic-grid-width)])
    (make-posn (+ border-size (* approx-pic-width col))
               (+ border-size (* approx-pic-height row)))))

(define (place-picture window filename grid-posn)
  (let ([posn (grid-posn-to-posn grid-posn)])
    ((clear-solid-rectangle window) posn approx-pic-width approx-pic-height)
    ((draw-pixmap window) filename posn)))

(define (place-repeatedly window pause stream n)
  (when (> n 0)
    (let* ([next (stream)]
           [filename (cdar next)]
           [grid-posn (caar next)]
           [stream (cdr next)])
      (place-picture window filename grid-posn)
      (sleep pause)
      (place-repeatedly window pause stream (- n 1)))))

;; Tests Start Here

; These definitions will work only after you do some of the problems
; so you need to comment them out until you are ready.
; Add more tests as appropriate, of course.

(define nums (sequence 0 5 1))

(define files (string-append-map 
               (list "ztatlock" "dog" "curry" "dog2") 
               ".jpg"))

(define funny-test (stream-for-n-steps funny-number-stream 16))

; a zero-argument function: call (one-visual-test) to open the graphics window, etc.
(define (one-visual-test)
  (place-repeatedly (open-window) 0.5 (cycle-lists nums files) 27))

; similar to previous but uses only two files and one position on the grid
(define (visual-zero-only)
  (place-repeatedly (open-window) 0.5 (stream-add-zero ztatlock-then-dog) 27))

; assert def
(define (assert b err)
  (if b
      null
      (begin (write (string-append err "\n")))))

; i am v lazy
(define eq (lambda (a b) (equal? a b)))

;sequence tests
(assert (eq (sequence 0 1 1) (list 0 1)) "sequence simple test")
(assert (eq (sequence 0 10 5) (list 0 5 10)) "sequence simple test2")

;string-append-map tests
(assert (eq (string-append-map (list "hi" "my") " KITTY!")
            (list "hi KITTY!" "my KITTY!")) "string-append-map simple test")

;list-nth-mod tests
(assert (eq (list-nth-mod (list 0 1 2 3) 3) 3) "l nth mod < length test")
(assert (eq (list-nth-mod (list 0 1 2 3) 5) 1) "l nth mod > length test")

;stream-n-steps will effectively be tested by the next couple functions
;funny-number-stream tests
(assert (eq (stream-for-n-steps funny-number-stream 5) (list 1 2 3 4 -5)) "funny number str first itr")
(assert (eq (stream-for-n-steps funny-number-stream 10) (list 1 2 3 4 -5 6 7 8 9 -10)) "funny number str second itr")

;lazy
(define n-st (lambda (s n) (stream-for-n-steps s n)))
;ztatlock-then-dog tests
(assert (eq (n-st ztatlock-then-dog 1) (list "ztatlock.jpg")) "zthend first step")
(assert (eq (n-st ztatlock-then-dog 2) (list "ztatlock.jpg" "dog.jpg")) "zthend second step")
(assert (eq (n-st ztatlock-then-dog 3) (list "ztatlock.jpg" "dog.jpg" "ztatlock.jpg")) "zthend wrap step")

;stream-add-zero tests
(assert (eq (n-st (stream-add-zero funny-number-stream) 1) (list (cons 0 1))) "add-zero simple test")
(assert (eq (n-st (stream-add-zero funny-number-stream) 2) (list (cons 0 1) (cons 0 2))) "add-zero simple test")

(define l1 (list 1 2 3 4))
(define l2 (list "a" "b"))
;cycle-lists tests
(assert (eq (n-st (cycle-lists l1 l2) 1) (list (cons 1 "a"))) "cycle lists first itr")
(assert (eq (n-st (cycle-lists l1 l2) 3) (list (cons 1 "a") (cons 2 "b") (cons 3 "a"))) "cycle lists wrap case")
(assert (eq (n-st (cycle-lists l1 l2) 5) 
            (list (cons 1 "a") (cons 2 "b") (cons 3 "a") (cons 4 "b") (cons 1 "a"))) 
        "cycle lists HELLA wrap case")

;vector-assoc tests
(define v (vector (cons 1 2) 3 (cons 4 5) #f (cons 6 7)))
(assert (eq (vector-assoc 1 v) (cons 1 2)) "vector-assoc simple case")
(assert (eq (vector-assoc 4 v) (cons 4 5)) "vector-assoc skip num case")
(assert (eq (vector-assoc 6 v) (cons 6 7)) "vector-assoc skip DAT BOOL")

;cached-assoc tests?
(define assl (list (cons 1 2) (cons 3 4) (cons 5 6)))
(define cached (cached-assoc assl 4))
(assert (eq (cached 1) (cons 1 2)) "cached-assoc simple test")
(assert (eq (cached 1)  (cons 1 2)) "cached-assoc simple test should log cached!")
(assert (eq (cached 5) (cons 5 6)) "cached-assoc simple test")
(assert (eq (cached 5) (cons 5 6)) "cached-assoc simple test should log cached!")


(define a 2)
(define b 7)
(assert (eq a 2) "base case")
(begin (while-less b do (begin (set! a (+ a 1)) a)))
(assert (eq a 7) "some mutatin")
(begin (while-less b do (begin (set! a (+ a 1)) a)))
(assert (eq a 8) "moar")
