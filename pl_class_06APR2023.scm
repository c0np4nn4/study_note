(define nil '())

(define mylist
  (cons 1 (cons 2 (cons 3 nil))))

(define atom?
  (lambda (x)
    (and (not (pair? x))
         (not (null? x)))))

(define atom?
  (lambda (x)
    (cond
      ((null? x) #f)
      ((pair? x) #f)
      (else #t))))

(null? nil)
(null? mylist)

(car mylist)
(cdr mylist)
(cons mylist nil)

(pair? mylist)
(pair? nil)

(atom? 1)
(atom? #t)
(atom? "string")

(atom? nil)
(atom? mylist)

'atom
(quote atom)

(quote (1 2 3))
(atom? '(1 2 3))
(atom? (quote (1 2 3)))
(atom? (quote ()))
(atom? 'scheme)
(atom? mylist)

(display "____________\n")
(atom? (quote (1 2 3)))
(atom? (quote ()))
(atom? '(1 2 3))
(atom? 'scheme)
(atom? nil)

(+ 1 2)
'(+ 1 2)
'a
(quote a)
(quote 'a)
''a

(number? 12)
(number? 'scheme)

(eq? 12 nil)
(eq? 12 (+ 10 2))

(integer? 12)

(complex? 3+4i)

(number? 3+4i)

(real? 3.14)

(rational? 2/1)
(rational? 1/2)

(integer? 2/1)
(integer? 1/2)

(integer? 2.0)

(zero? 0.0)

(exact? 2.0)
(inexact? 2.0)

(exact? 3+4i)
(exact? 3.0+4i)
(complex? 3.0+4i)

(odd? 3.0)
(max 1 2 3 4 5)
(min 1 2 3 4 5)

(display "============================================\n")

(define fact
  (lambda (n)
    (cond
      ((= n 0) 1)
      (else (* n (fact (- n 1)))))))

(fact 10)

(define ifact
  (lambda (n p)
    (if (= n 0) p
        (ifact (- n 1) (* n p)))))

(ifact 10 1)

