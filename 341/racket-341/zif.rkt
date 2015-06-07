#lang racket

(define (zif e1 e2 e3)
  (if e1 e2 e3))

(define (zif-thunk e1 e2 e3)
  (if e1 (e2) (e3)))

(define (zfact n)
  (zif (= n 0)
       1
       (* n (zfact (- n 1 )))))

(define (zfact-thunk n)
  (zif (= n 0)
       (lambda () 1)
       (lambda () (* n (zfact-thunk (- n 1))))))


(define (zdelay th)
  (mcons #f th))

(define (zforce p)
  (if (mcar p)
      (mcdr p)
      (begin (set-mcar! p #t)
             (set-mcdr! p ((mcdr p)))
             (mcdr p))))

(define zones (lambda () (cons 1 zones)))
