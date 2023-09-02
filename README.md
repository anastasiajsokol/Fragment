# Fragment

A simple interpeted language.

## Values

While Fragment is weakly typed, it has four built-in value types

    Numeric Values: These store whatever the c++ implementation of a double is for a given platform.

    Boolean Values: These store either a true or false state.

    String Values: These store text.

    Function Values: These represent function expressions.

While the details of how each operation interacts between different types (and not every operation is defined between every type) they generally follow some base rules

    Numeric values generally decay into whatever the are being operated on by

    Boolean values generally convert other forms into booleans first

    String values prefer to convert other forms into strings first

    Function values are always lazily operated on, returning a new function that is the old function with some new operator and value applied to it (see lazy.fr example)

## Expressions

All languages are made up of expressions, and Fragment is no different

    atomic := numeric | stringliteral | boolean | reference
        Atomic expressions are the simplest, representing a single value
    
    self := (expression)
        Self expressions are similar to atomic expressions in that they represent only one thing, however here functions get evaluated with no arguments
        See the example 'self_vs_atomic.fr' to better understand the difference.
    
    operator := (operator expression expression*)
        Operator expressions apply some operation across one or more sub expressions
    
    define := ('define' reference expression)
        Sets the provided reference to the value of the expression, starts with 'define' keyword
    
    lambda := ('lambda' (reference*) expression)
        Defines a function that takes in arguments (a block of references) and passes them into the expression, starts with 'lambda' keyword
    
    conditional := ('if' expression expression expression)
        Depending on the truthyness of the first expression evaluates the first or second expression respectively, starts with 'if' keyword
    
    function := (expression expression expression*)
        Expects the first expression to evaluate to a function (lambda or reference to lambda), and passes the following expressions as arguments

    comment := ('%%' **)
        Comments must start with %%, then the rest of the block must be valid tokens however they do not need to be valid expressions

## Standard Library

The standard library defines a couple functions you can use.

    print: prints out all arguments passed in, returns a string representing what was printed (flushes stream)
    
    println: similar to print but adds a newline character afterwards (flushes stream)
    
    readline: reads a line of user input, takes no arguments

    readnumeric: reads a number from the user (blocks until a valid number is entered)

More functions may be added in the future.

## Examples

If you want to see the language in action or want a base for creating your own programs, check out the example directory.

    helloworld.fr: prints out "Hello World" to the console, always a good place to start
        expected output: Hello World

    addition.fr: uses many of the core language features, expands a bit upon "helloworld", but still pretty simple
        expected output: 2 + 39 = 41
    
    factorial.fr: recursion is always cool (challenge: instead of hardcoding a value, modify the program to accept user input)
        expected output: 8! = 40320
    
    input.fr: demonstrates some basic input, uses more of the standard library
        expected output:
            Enter a number: ${n}
            ${n} squared is ${n * n}
    
    lazy.fr: demonstrates lazy function operators
        expected output: 66
    
    self_vs_atomic.fr: demonstrates the difference between self and atomic expressions, and why it matters
        expected output:
            Enter a number: ${n}
            ${n} squared is ${n * n}
            Enter a number: λ(...) squared is λ(...)

## Issues

Some possible exceptions that you might run into if you write an invalid program (...or if my interpeter has bugs I did not catch)

    File Error: this almost always means the input file either does not exist or you do not have permission to open it

    Invalid Lexeme Exception: one of the fundamental tokens of your programs is not a valid token

    Invalid Block Exception: this means your tokens fail to form blocks, check that every expression starts and ends with delimeters '(' and ')' respectively

    Invalid Expression: you have an expression that does not match a valid pattern (see grammar above)

    Invalid Program State: undefined reference (no position information!)

    Operation Not Implemented: an attempt was made to perform an operation with types where that operation is not defined between (no position information!)

You may also have issues compiling the interpeter, if this is the case make sure you are using c++17 or greater.

## Command Line Interface

#### -v, --version

    Outputs version information (currently "Fragment Interpeter v. 1.0")

#### -h, --help

    Gives some limited information about using the command line

#### input file path

    This can be any path, the program will attempt to interpet it
