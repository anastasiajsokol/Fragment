#include <iostream>
#include <variant>
#include <memory>

struct Value;
typedef std::shared_ptr<Value> value_t;

struct Value {
    enum class ValueType {
        numeric,
        string
    };
    
    std::variant<int, std::string> value;
    ValueType type;

    Value(int value) : value(value) {}
    Value(std::string value) : value(value) {}
    
    virtual value_t operator +(const value_t&) const {
        throw "AHHHH";
    }

    virtual std::string to_string() const {
        throw "AHHHH";
    }
};

value_t operator +(const value_t &a, const value_t &b){
    return *a + b;
}

struct IntValue : public Value {
    IntValue(int value) : Value(value) {
        type = Value::ValueType::numeric;
    }
    
    value_t operator +(const value_t&) const override;

    std::string to_string() const override;
};

struct StringValue : public Value {
    StringValue(std::string value) : Value(value) {
        type = Value::ValueType::string;
    }
    
    value_t operator +(const value_t&) const override;

    std::string to_string() const override;
};

value_t IntValue::operator +(const value_t& other) const {
    switch(other.get()->type){
        case Value::ValueType::numeric:
            return value_t(new IntValue(std::get<int>(value) + std::get<int>(other.get()->value)));
        
        case Value::ValueType::string:
            return value_t(new StringValue(this->to_string() + std::get<std::string>(other.get()->value)));

        default:
            throw "Unreachable";
    }
}

std::string IntValue::to_string() const {
    return std::to_string(std::get<int>(value));
}

value_t StringValue::operator +(const value_t& other) const {
    switch(other.get()->type){
        case Value::ValueType::numeric:
            return value_t(new StringValue(std::get<std::string>(value) + other.get()->to_string()));
        
        case Value::ValueType::string:
            return value_t(new StringValue(std::get<std::string>(value) + std::get<std::string>(other.get()->value)));

        default:
            throw "Unreachable";
    }
}

std::string StringValue::to_string() const {
    return std::get<std::string>(value);
};

int main() {
    value_t a = value_t(new StringValue("Hello World <"));
    value_t b = value_t(new IntValue(3));

    value_t c = a + b;
    
    std::cout << c.get()->to_string() << std::endl;

    return 0;
}