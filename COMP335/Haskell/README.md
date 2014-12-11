*** Background
* Who invented it?
- in the late 1980s, after the release of Miranda, there are dozens of pure functional languages invented, in order to make it better for future research, at the conference on Functional Programming Languages and Computer Architecture in 1987, a committee was formed to consolidate the existing function languages, as the result, the first version of Haskell was released in 1990
- There's a list of all the people designed Haskell on Wikipedia page online
- Haskell is named for Haskell Brooks Curry because his work in mathematical logic serves as the foundation for functional languages
- Since Haskell is based on the lambda calculus, so lambda is used as the logo for Haskell
- GHC (Glasgow Haskell Compiler) - the most widely used Haskell compiler


* What kind of tasks is this language used for?
- This language can be used for writing web frameworks
- developing and verifying cryptographic algorithms
- The fun fact is that the first formally verified microkernel was verified using Haskell.


* Why do programmers use this language?
- Supports Lazy evaluation, pure functional programming language (that has immutable objects), strong statically typed, (so while compiling, the compiler knows the type of data structures), the languages itself is concise and elegant. It supports templates, operator overloading, type classes, plenty of modules cannot be imported to use, and it is not an experimental language...


* What are some similar programming languages?
- There are several numbers of programming languages similar to Haskell, like Scotch is similar to both Python and Haskell; Curry is a language based on Haskell;  and Jaskell is a language running on Java Virtual Machine


*** Technical Aspects
* Does it have a REPL?
- When you type an expression at the prompt called "prelude", GHCi immediately read and expression, evaluates it and prints the result:


* Interpreted? Compiled?
- Both compiled and interpreted implementations available
- Left side: compiler
- Right side: interpreter


* Support for laziness
- immutable variables
- lazy evaluation: results are only computed if they're required 
(they only evaluate as much of the program as is required to get the answer)


* Typing
- Strongly Static typed
- Instances of a type cannot be cast into another type
- The type of every expression and every variable is known at compile time, eliminating a huge class of easy-to-make errors at compile time


* Error handling
- build your own error handling frameworks. 
- calling the error function that terminates the program in order to avoid programmer's error
- maybe a is a universal mechanism for reporting failure when there's only one possible error in the code
(maybe is a type constructor, a is a type parameter, Depending on what we want this data type to hold when it's not Nothing, this type constructor can end up producing a type of Maybe Int, Maybe Car, Maybe String, etc.)
for example, this code uses maybe a to handle the type error...
- Either A can handle two errors


* Functions as first class citizens
Pattern matching on data structures -- data structures are first class! (factorial)
- Because Haskell has first class functions, you can define a data structure that has functions as fields:
- Haskell has recurrence, so we can pass function as an argument and store in a data structure
- (This function takes two arguments: a function f which maps as to bs, and a list xs of as. It returns a list of bs which are the results of applying f to every member of xs. )


* The “parts” of a programming language (e.g. libraries, idioms, etc)
- In Haskell, abstract syntax can be expressed as algebraic datatypes.
 data Exp = Eplus Exp Exp
             | E2
             | E3
 Just like define-type in Racket, we can...
 data Shape = Circle Float Float Float | Rectangle Float Float Float Float
 the first two fields are the coordinates of its center, the third one its radius.
(- immutable objects
- Haskell has typeclasses, they look like classes in object oriented languages, but they aren't
- Data Car just like the constructor in C++)
- A non-strict programming language allows the user to define non-strict functions, and hence may allow lazy evaluation. (strict functions: parameters must be evaluated completely before they may be called)
- Idioms collections can be found online, and there are huge amount of packages that can be imported 


* Memory management
- Haskell produces a lot of memory garbage since data are immutable
every time we create new data structures, or iterate through the recursive functions (for example if we wanna write a function to calculate factorials of numbers, then new variables are created all the time, such function produces plenty of temporary data but just return one value in the end)
- The larger percent of your values are garbage, the faster it works.
(New data are allocated in 512kb memory. Once the memory is full, the Garbage Collection will copy useful values to the main memory area and free unused values. so the fewer values that survive, the less work to do. As the result, ...


* Concurrency
- GHC supports parallel and concurrent programming
- access to concurrency operations by importing the library Control.Concurrent.