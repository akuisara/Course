#lang plai-typed

(define-type Tree
  [node (n : number) (left : Tree) (right : Tree)]
  [leaf])

;Helper functions (if necessary)

(define (tree-to-list [t : Tree]) : (listof number)
  (cond 
   [(leaf? t) empty]
   [else (append (tree-to-list (node-left t)) (cons (node-n t) (tree-to-list (node-right t))))]
   ))

;Test cases:
(test (tree-to-list (node 5 (node 4 (node 3 (leaf) (leaf)) (leaf)) (node 7 (leaf) (node 9 (node 8 (leaf) (leaf)) (leaf))))) (list 3 4 5 7 8 9))
(test (tree-to-list (leaf)) empty)
(test (tree-to-list (node 9832 (leaf) (leaf))) (list 9832))
(test (tree-to-list (node 4 (node 2 (node 1 (leaf) (leaf)) (node 3 (leaf) (leaf))) (node 5 (leaf) (leaf)))) (list 1 2 3 4 5))

