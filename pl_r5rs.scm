(define (double n)
  (+ n n))

(define twice (lambda (n) (+ n n)))

(define n 7)

; (double 1234)
(double n)

; (lambda (x y) (+ x y)
((lambda (x y) (+ x y)) n 10)
(twice 5)

(define f
  (lambda (x)
    (if (> x 0) x (- x))))

(f 123)
(f -1910)

;;;;

(define fact
  (lambda (n)
    (if (= n 0) (+ 1 n))
    (* n (fact (- n 1)))))
 
(fact 10)

