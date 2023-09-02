# Fragment

A simple interpeted language

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
        Atomic expressions are the simplest, representing a single value and of the form
    
    self := (expression)
        Self expressions are similar to atomic expressions in that they represent only one thing, however here functions get evaluated with no arguments
        See the example 'self_vs_atomic.fr' to better understand the difference.
    
    operator := (operator expression expression*)
        Operator expressions apply some operation across one or more sub expressions
    
    define := ('define' reference expression)
        Sets the provided reference to the value of the expression, starts with 'define' keyword
    
    lambda := ('lambda' (reference reference*) expression)
        Defines a function that takes in arguments (a block of references) and passes them into the expression, starts with 'lambda' keyword
    
    conditional := ('if' expression expression expression)
        Depending on the truthyness of the first expression evaluates the first or second expression respectively, starts with 'if' keyword
    
    function := (expression expression expression*)
        Expects the first expression to evaluate to a function (lambda or reference to lambda), and passes the following expressions as arguments

    comment := ('%%' **)
        Comments must start with %%, then the rest of the block must be valid tokens however they do not need to be valid expressions
