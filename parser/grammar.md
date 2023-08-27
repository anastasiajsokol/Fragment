# Grammar Definition for Fragment Lisp

Expression Types
    atomic := numeric | stringliteral | boolean | reference

    define_expression := (define reference expression)
    lambda_expression := (lambda (reference*) expression)
    conditional_expression := (if expression expression expression)

    operator_expression := (operator expression*)
    
    s_expression := (reference expression*)
