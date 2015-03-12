#lang plai-typed

; The internal semantic representation for the arithmetic
; expressions language
; (the C stands for "core" language)
(define-type ArithC
  [numC (n : number)]
  [plusC (left : ArithC) (right : ArithC)]
  [multC (l : ArithC) (r : ArithC)]
  [ifC (testC : ArithC) (thenC : ArithC) (elseC : ArithC)]
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
    [(and (s-exp-list? s) (= 3 (length (s-exp->list s))))
     (let ([sl (s-exp->list s)])
       (case (s-exp->symbol (first sl))
         [(+) (plusC (parse (second sl)) (parse (third sl)))]
         [(*) (multC (parse (second sl)) (parse (third sl)))]
         ;return (second sl) if (second sl) equals to 0, otherwise, return (third sl)
         [(if0) (ifC (parse (second sl)) (parse (second sl)) (parse (third sl))) ]))]
    [else (error 'parse "syntax error")]))
    

; the interpreter takes the internal representation
; of the program, executes it, and returns the result

(define (interp [a : ArithC]) : number
  (type-case ArithC a
    [numC (n) n]
    [plusC (l r) (+ (interp l) (interp r))]
    [multC (l r) (* (interp l) (interp r))]
    ;defines ifC operation, if the first element equals to 0, then return the second one, otherwise return the third one
    [ifC (x y z) 
         (cond 
           [(= (interp x) 0) (interp y)] 
           [else (interp z)])]
))

;-----------------------------------------------------
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

;test interp (takes ArithC and returns a number)
;input is s-exp-number
(test (interp (parse '2)) 2)
;input is s-exp-list with length of 3, and starts with a symbol
(test (interp (parse '(+ 1 2))) 3)
;input is s-exp-list with length of 3, and start with a symbol, but cannot execute plusC
(test/exn (interp (parse '(+ a 2))) "syntax error")
;input is s-exp-list with length other than 3, and start with a non-symbol
(test/exn (interp (parse '(1))) "syntax error")
;input is s-exp-list with length other than 3, and start with a symbol
(test/exn (interp (parse '(+ 1 2 3))) "syntax error")

;-----------------------------------------------------
;2. test parse (takes s-expression and returns ArithC)
;single operation
(test (parse '(* 1 2)) (multC (numC 1) (numC 2)))
;multiple operation
(test (parse '(* (+ 1 2) 3)) (multC (plusC (numC 1) (numC 2)) (numC 3)))

;test interp (takes ArithC and returns a number)
;single operation
(test (interp (parse '(* 1 2))) 2)
;multiple operation
(test (interp (parse '(* (+ 1 2) 3))) 9)

;-----------------------------------------------------
;3. define eval function
(define (eval [x : s-expression]) : number
  (interp (parse x))
)
;test when input is a s-exp-number
(test (eval '9) 9)
;test when input is a s-exp-list
(test (eval '(* (+ 1 2) 3)) 9)

;-----------------------------------------------------
;4. if0 statement 
;test case does not equal to 0
(test (parse '(if0 (+ 0 1) 5)) (ifC (plusC (numC 0) (numC 1)) (plusC (numC 0) (numC 1)) (numC 5)))
(test (interp (ifC (plusC (numC 0) (numC 1)) (plusC (numC 0) (numC 1)) (numC 5))) 5)
(test (eval '(if0 (+ 2 3) (* 3 4))) 12)

;test case equals to 0
(test (eval '(if0 0 1)) 0)
(test (eval '(if0 (* 1 0) (+ 3 4))) 0)

;-----------------------------------------------------
;test equality without if0 sugaring
(test (= (interp (numC 0)) (interp (numC 0))) #t)
(test (= (interp (numC 1)) (interp (numC 0))) #f)