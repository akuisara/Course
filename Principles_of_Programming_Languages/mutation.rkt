#lang plai-typed

; The internal semantic representation for the arithmetic
; expressions language
; (the C stands for "core" language)

(define-type ArithC
  [numC (n : number)]
  [idC (id : symbol)]
  [plusC (left : ArithC) (right : ArithC)]
  [beginC (l : (listof ArithC))]
  [declareC (id : symbol) (val : ArithC)]
  [setC (id : symbol) (val : ArithC)]
  )

; remember the REPL
; eval has two parts, the parser and the interpreter
; (print (eval (read))) --> 
;     (print (interpret (parse (read))))

; the parser takes in an s-expression 
; and returns the internal representation of the program
(define (parse [s : s-expression]) : ArithC
  (cond
    [(s-exp-number? s) (numC (s-exp->number s))]
    [(and (s-exp-list? s) 
          (= 1 (length (s-exp->list s)))) 
     (error 'parse "syntax error")]
    [(and (s-exp-list? s)
          (eq? (s-exp->symbol (first (s-exp->list s))) 'begin))
     (beginC (map parse (rest (s-exp->list s))))]  
    [(and (s-exp-list? s) 
          (= 3 (length (s-exp->list s))))
     (let ([sl (s-exp->list s)])
       (case (s-exp->symbol (first sl))
         [(+) (plusC (parse (second sl)) (parse (third sl)))]
         [(declare) (declareC (s-exp->symbol (second sl)) (parse (third sl)))]
         [(set) (setC (s-exp->symbol (second sl)) (parse (third sl)))]
       ))]
    [else (error 'parse "syntax error")]))

(define-type Binding
  [bind (name : symbol) (val : number)])
(define-type-alias Env (boxof (listof Binding)))
(define mt-env (box empty))
(define (add-env [b : Binding] [e : Env]) : Env
  (begin 
    (set-box! e (cons b (unbox e)))
    e))

; the interpreter takes the internal representation
; of the program, executes it, and returns the result
(define (interp [a : ArithC] [e : Env]) : (boxof number)
  (type-case ArithC a
    [numC (n) (box n)]
    [plusC (l r) (box (+ (unbox (interp l e)) (unbox (interp r e))))]
    [idC (n) (box (lookup n e))]
    [beginC (l) 
            (cond
              [(empty? l) (error 'interp "empty list of ArithC")]
              [(= (length l) 1) (interp (first l) e)]
              [else 
               (interp (beginC (rest l)) e)])]
    [declareC (i v) (box (lookup i (add-env (bind i (unbox (interp v e))) e)))]
    [setC (i v) 
          (cond
            [(= (unbox (interp v e)) (lookup i e)) (box (lookup i e))]
            [else 
             (box (lookup i (add-env (bind i (unbox (interp v e))) e)))])]
))

;lookup
(define (lookup [for : symbol] [env : Env]) : number
  (cond
    [(empty? (unbox env)) (error 'lookup "name not found")]
    [else (cond
            [(symbol=? for (bind-name (first (unbox env))))(bind-val (first (unbox env)))]
            [else (lookup for (box (rest (unbox env))))])]))

(display "---------------------------Parse--------------------------\n")
;1. test parse (takes s-expression and returns ArithC)
;input is s-exp-number
(test (parse '2) (numC 2))
;input is s-exp-list with length of 3, and starts with a symbol
(test (parse '(+ 1 2)) (plusC (numC 1) (numC 2)))
;input is s-exp-list with length of 3, start with a non-symbol, but cannot execute plusC
(test/exn (parse '(+ a 2)) "syntax error")
;input is s-exp-list with length other than 3, and start with a non-symbol
(test/exn (parse '(1)) "syntax error")
;input is s-exp-list with length other than 3, and start with a symbol
(test/exn (parse '(+ 1 2 3)) "syntax error")
(test/exn (parse '(begin)) "syntax error")
;input is s-exp-list starts with 'declare
(test (parse '(declare four 4)) (declareC 'four (numC 4)))
;input is s-exp-list starts with 'begin
(test (parse '(begin 1)) (beginC (list (numC 1))))
;input is s-exp-list starts with 'begin
(test (parse '(begin (+ 1 2) (+ 3 4))) (beginC (list (plusC (numC 1) (numC 2)) (plusC (numC 3) (numC 4)))))
;input is s-exp-list starts with 'declare
(test (parse '(declare four 4)) (declareC 'four (numC 4)))
;input is s-exp-list starts with 'set
(test (parse '(set three 3)) (setC 'three (numC 3)))

(display "-----------------------Interp------------------------------\n")
;2. test interp (takes ArithC and Env and returns a boxof number)
;test interp with numC
(test (interp (numC 5) mt-env) (box 5))
(test (interp (parse '2) mt-env) (box 2))
;test interp with plusC
(test (interp (plusC (numC 10) (numC 5)) 
              mt-env) 
      (box 15))
(test (interp (parse '(+ 1 2)) mt-env) (box 3))
;test interp with idC
(test (interp (idC 'five)
              (add-env (bind 'five (unbox (interp (numC 5) mt-env))) mt-env))
      (box 5))

;test interp with beginC that contains an empty list)
(test/exn (interp (beginC empty)
                  mt-env)
      "empty list of ArithC")
;test interp with beginC that contains a list of ArithC)
(test (interp (beginC (list (plusC (numC 1) (numC 2)) (plusC (numC 3) (numC 4))))
                  mt-env)
      (box 7))
(test (interp (parse '(begin (+ 2 3) (+ 4 5) (+ 0 9))) mt-env) (box 9))
;test interp with declareC in an empty environment
(test (interp (declareC 'four (numC 4))
              mt-env)
      (box 4))
;test interp with declareC
(test (interp (declareC 'one (plusC (numC -9) (numC 10)))
              (add-env (bind 'z (unbox (interp (numC 11) mt-env))) mt-env))
      (box 1))
;test interp with declareC
(test (interp (declareC 'y (numC 999))
              (add-env (bind 'y (unbox (interp (numC 11) mt-env))) mt-env))
      (box 999))
(test (interp (parse '(declare mystery (+ 4 (+ 2 9)))) mt-env) (box 15))
;test interp with setC in an empty environment
(test/exn (interp (setC 'ten (plusC (numC 4) (numC 6)))
              mt-env)
      "name not found")
;test interp with setC
(test (interp (setC 'ten (plusC (numC 4) (numC 6)))
              (add-env (bind 'ten (unbox (interp (numC 11) mt-env))) mt-env))
      (box 10))
(test (interp (parse '(set blackbox 9)) (add-env (bind 'blackbox (unbox (interp (numC 11) mt-env))) mt-env)) (box 9))


(test/exn (interp (parse '(+ a 2)) mt-env) "syntax error")
(test/exn (interp (parse '(1)) mt-env) "syntax error")
(test/exn (interp (parse '(+ 1 2 3)) mt-env) "syntax error")

(define (eval [x : s-expression]) : number
  (unbox (interp (parse x) mt-env))
)
(test (eval '9) 9)

(display "-----------------------Lookup------------------------------\n")
;3. Test Lookup
(test/exn (lookup 'x mt-env) "name not found")
(test (lookup 'x (add-env (bind 'x (unbox (interp (numC 5) mt-env))) mt-env)) 5)