#lang racket

(define (sum xs)
  (if (null? xs)
      0
      (+ (car xs) (sum (cdr xs)))))


(define (my-map f xs)
  (if (null? xs)
      null
      (cons (f (car xs)) (my-map f (cdr xs)))))
          (+ (car xs) (sumnums (cdr xs)))

(define (sumnums xs)
  (if (null? xs)
      0
      (if (number? (car xs))
          (+ (car xs) (sumnums (cdr xs)))
          (+ (sumnums (car xs)) (sumnums (cdr xs))))))

