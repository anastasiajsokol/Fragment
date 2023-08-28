#ifndef DATATYPE_VALUE_H
#define DATATYPE_VALUE_H

#include "operatortype.h"
#include "valuetype.h"

#include <variant>
#include <vector>
#include <utility>

struct Value {
    public:
        typedef Value value_operator_function(const Value&, const Value&);
        typedef std::pair<OperatorType, std::vector<std::pair<std::pair<OperatorType, ValueType>, value_operator_function>>> OperatorPack;

        std::variant<double> value;
        ValueType type;

        static void add_operator_pack(OperatorPack);

    private:
        static Value bad_operator(const Value&, const Value&) noexcept(false) {

        }
        
        static inline value_operator_function* operator_table[NUMBER_OF_OPERATORS][NUMBER_OF_VALUE_TYPES][NUMBER_OF_VALUE_TYPES] = {bad_operator};
};

#endif