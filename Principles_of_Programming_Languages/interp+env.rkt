#lang plai-typed

; The internal semantic representation for the arithmetic
; expressions language
; (the C stands for "core" language)
(define-type ExprC
  [numC (num : number)]
  [plusC (left : ExprC) (right : ExprC)]
  [multC (left : ExprC) (right : ExprC)]
  [idC (name : symbol)]
  [appC (function : symbol) (arg : ExprC)]
  )

; the internal representation of a function definition
; for now, function definitions have a name, one argument, and a body
(define-type FunDefC
  [fdC (name : symbol) (arg : symbol) (body : ExprC)])

; example list of function definitions
(define myfds (list 
               (fdC 'inc5 'y (plusC (idC 'y) (numC 5)))
               (fdC 'inc10 'y (plusC (idC 'y) (numC 10)))
               (fdC 'double 'y (multC (idC 'y) (numC 2)))
               ))
; a recursive helper function to find the representation of a function 
; definition from the list, given its name
(define (get-fundef [name : symbol] [fundefs : (listof FunDefC)]) : FunDefC
  (cond 
    [(empty? fundefs) 
     (error 'get-fundef "function name not found")]
    [(eq? (fdC-name (first fundefs)) name)
    (first fundefs)]
    [else
     (get-fundef name (rest fundefs))]
    ))

; test expressions
(test (get-fundef 'double myfds) (fdC 'double 'y (multC (idC 'y) (numC 2))))
(test (get-fundef 'inc5 myfds) (fdC 'inc5 'y (plusC (idC 'y) (numC 5))))
(test/exn (get-fundef 'inc15 myfds) "function name not found")

; the parser takes in an s-expression 
; and returns the internal representation of the program
(define (parse [s : s-expression]) : ExprC
  (cond
    [(s-exp-number? s) (numC (s-exp->number s))]
    [(s-exp-symbol? s) (idC (s-exp->symbol s))]
    [(and (s-exp-list? s) (= 3 (length (s-exp->list s))))
     (let ([sl (s-exp->list s)])
       (case (s-exp->symbol (first sl))
         [(+) (plusC (parse (second sl)) (parse (third sl)))]
         [(*) (multC (parse (second sl)) (parse (third sl)))]
         [else (error 'parse "syntax error")]))]
    [(and (s-exp-list? s) (= 2 (length (s-exp->list s))))
     (let ([sl (s-exp->list s)])
      (appC (s-exp->symbol (first sl)) (parse (second sl))))]
     [else (error 'parse "syntax error")]
    ))


(define-type Binding
  [bind (name : symbol) (val : number)])

(define-type-alias Env (listof Binding))
(define mt-env empty)
(define extend-env cons)

;interpreter
(define (interp [expr : ExprC] [env : Env] [fds : (listof FunDefC)]) : number
  (type-case ExprC expr
    [numC (n) n]
    [plusC (l r) (+ (interp l env fds) (interp r env fds))]
    [multC (l r) (* (interp l env fds) (interp r env fds))]
    [idC (n) (lookup n env)]
    ;[appC (f a) (interp (get-fundef f fds) env fds)]
    [appC (f a) (local ([define fd (get-fundef f fds)])
                  (interp (fdC-body fd) 
                          (extend-env (bind (fdC-arg fd)
                                            (interp a env fds))
                                      mt-env)
                          fds)
                  )]
    ))

;lookup
(define (lookup [for : symbol] [env : Env]) : number
  (cond
    [(empty? env) (error 'lookup "name not found")]
    [else (cond
            [(symbol=? for (bind-name (first env)))(bind-val (first env))]
            [else (lookup for (rest env))])]))

; a few example test expressions
(test (parse '5) (numC 5))
(test (parse '(double 4)) 
      (appC 'double (numC 4)))
(test (parse '(* (inc5 5) 2)) 
       (multC (appC 'inc5 (numC 5)) (numC 2)))
(test (parse '(inc10 (+ 2 (+ 1 1)))) 
      (appC 'inc10 (plusC (numC 2) (plusC (numC 1) (numC 1)))))
(test/exn (parse '(inc5 1 2)) ; too many args
          "syntax error")
(test/exn (parse '(double)) ; not enough args
          "syntax error")

; Test Case Examples From Book
(test (interp (plusC (numC 10) (appC 'const5 (numC 10))) 
              mt-env 
              (list (fdC 'const5 '_ (numC 5)))) 
      15)
(test (interp (plusC (numC 10) (appC 'double (plusC (numC 1) (numC 2))))
              mt-env
              (list (fdC 'double 'x (plusC (idC 'x) (idC 'x))))) 
      16)
 
(test (interp (plusC (numC 10) (appC 'quadruple (plusC (numC 1) (numC 2))))
              mt-env
              (list (fdC 'quadruple 'x (appC 'double (appC 'double (idC 'x))))
                    (fdC 'double 'x (plusC (idC 'x) (idC 'x))))) 
      22)

(display "\n=============More Test Cases============\n\n")
; Interp Test Cases:
(test/exn (interp (appC 'f1 (numC 3))
                  mt-env
                  (list (fdC 'f1 'x (appC 'f2 (numC 4)))
                        (fdC 'f2 'y (plusC (idC 'x) (idC 'y))))) "name not found")
(test (interp (multC (appC 'sextuple (numC 3)) (numC 2))
              mt-env
              (list (fdC 'sextuple 'x (multC (idC 'x) (numC 6))))) 36)
(test (interp (plusC (appC 'quintuple (appC 'const10 (numC 1))) (plusC (numC 1) (multC (numC 2) (numC 3))))
              mt-env
              (list (fdC 'quintuple 'x (multC (numC 5) (idC 'x)))
                    (fdC 'const10 '_ (numC 10))))
      57)
(test/exn (interp (appC 'inc5 (appC 'inc10 (numC 5)))
              mt-env
              empty)
      "name not found")
(test (interp (appC 'inc5 (numC 5))
              mt-env
              myfds)
      10)

; Func-Def Test Cases:
(define mysecondfds (list 
               (fdC 'double 'y (multC (idC 'y) (numC 2)))
               (fdC 'triple 'y (multC (idC 'y) (numC 3)))
               (fdC 'quadruple 'y (multC (idC 'y) (numC 4)))
               (fdC 'quintuple 'y (multC (idC 'y) (numC 5)))
               ))
(test (get-fundef 'quintuple mysecondfds) (fdC 'quintuple 'y (multC (idC 'y) (numC 5))))
(test/exn (get-fundef 'sextuple mysecondfds) "function name not found")

; Env/Binding Test Cases:
(test (interp (multC (numC 5)(appC 'square (numC 5)))
              (extend-env (bind 'x 10) mt-env)
              (list (fdC 'square 'x (multC (idC 'x) (idC 'x)))))
      125)    
(test (interp (plusC (appC 'square (idC 'y))(appC 'square (idC 'x)))
              (extend-env (bind 'y 5) (extend-env (bind 'x 10) mt-env))
              (list (fdC 'square 'x (multC (idC 'x) (idC 'x)))))
      125)

; Lookup Test Cases;
(test/exn (lookup 'x mt-env) "name not found")
(test (lookup 'x (list (bind 'a 1) (bind 'x 2))) 2)
(test (lookup 'x (list (bind 'x 1) (bind 'x 2))) 1)
(test (lookup 'x (extend-env (bind 'y 5) (extend-env (bind 'x 10) mt-env))) 10)