#lang racket

(define ones (lambda () (cons 1 ones)))

(define nats 
  (letrec ([f (lambda (x) (cons x (lambda () (f (+ x 1)))))])
          (lambda () (f 1))))

(define evens 
  (letrec ([f (lambda (x) (cons x (lambda () (f (+ x 2)))))])
          (lambda () (f 0))))

(define (stream-map f s)
  (lambda () 
    (let ([pr (s)])
      (cons (f (car pr)) (stream-map f (cdr pr))))))


(define (stream-filter f s)
   (lambda ()
     (let ([pr (s)])
       (if (f (car pr ))
           (cons (car pr) (stream-filter f (cdr pr)))
           ((stream filter f (cdr pr)))))))

; actual macros for real

(define-syntax zmif 
  (syntax-rules (then else)
    [(zmif e1 then e2 else e3)
     (if e1 e2 e3)]))

(define-syntax zdelay
  (syntax-rules ()
          [(zdelay e) (mcons #f (lambda () e))]))

(define (my-force p)
  (if (mcar p)
      (mcdr p)
      (begin (set-mcar! p #t)
              (set-mcdr! p ((mcdr p)))
              (mcdr p))))

(define (dbl1 x) (+ x x))
(define (dbl2 x) (* x 2))

(define-syntax mdbl1
  (syntax-rules ()
    [(mdbl1 x) (* x 2)]))


