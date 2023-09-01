# Grammar Definition for Fragment Lisp

Expression Types
    atomic := numeric | stringliteral | boolean | reference

    define_expression := (define reference expression)
    lambda_expression := (lambda (reference reference*) expression)
    conditional_expression := (if expression expression expression)

    operator_expression := (operator expression expression*)
    
    function_expression := (expression expression expression*)

    self_expression := (expression)
