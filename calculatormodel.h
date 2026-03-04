#ifndef CALCULATORMODEL_H
#define CALCULATORMODEL_H

#include <QDebug>
#include <optional>

class CalculatorModel
{
public:
    CalculatorModel();

    struct Display{
        QString expression;
        QString result;
    };

    Display PreprocessInput(const QString& input) {
        Display result;
        std::optional<BOperator> b_op = StringToBOperator(input);
        if(b_op) {
            if(IsSignInMiddle()) {
                //calculate
                double left = prev_num_.toDouble();
                double right = active_num_.toDouble();
                double res = ApplyOperator(left, right, operator_);
                result.expression = QString::number(res) + input;
                result.result = QString::number(res);
                Clear();
                operator_ = *b_op;
                prev_num_ = QString::number(res);
            } else {
                if(operator_ == BOperator::None) {
                    ActiveNumberToPrev(*b_op);
                } else {
                    operator_ = *b_op;
                }
                result.expression = prev_num_ + input;
                result.result = prev_num_;
            }
            return result;
        }
        std::optional<UOperator> u_op = StringToUOperator(input);
        if(u_op) {
            if(IsActiveNumberEmpty()) {
                active_num_ = prev_num_;
            }
            double right = active_num_.toDouble();
            double res = ApplyOperator(right, *u_op);
            active_num_ = QString::number(res);
            if(IsSignInMiddle()) {
                result.expression = prev_num_ + BOperatorToString() + active_num_;
                result.result = QString::number(res);
            } else {
                result.expression = active_num_;
                result.result = QString::number(res);
            }
            return result;
        }
        if(input == "=") {
            //calculate
            double left = prev_num_.toDouble();
            double right = active_num_.toDouble();
            double res = ApplyOperator(left, right, operator_);
            result.expression = prev_num_ + BOperatorToString() + active_num_ + input;
            result.result = QString::number(res);
            Clear();
            //prev_num_ = QString::number(res);
            active_num_ = QString::number(res);
            return result;
        }
        if(input == ".") {
            if(!is_dot) {
                is_dot = true;
                active_num_ += input;
            }
        } else {
            active_num_ += input;
        }

        if(IsSignInMiddle()) {
            result.expression = prev_num_ + BOperatorToString();
            result.result = active_num_;
        } else {
            result.expression = active_num_;
            result.result = active_num_;
        }
        return result;
    }

private:
    enum class BOperator { Add, Subtract, Multiply, Divide, None};
    enum class UOperator { ChangeSign, Percent};


    void ActiveNumberToPrev(BOperator b_op = BOperator::None) {
        prev_num_=active_num_;
        active_num_.clear();
        operator_ = b_op;
        is_dot = false;
    }
    void Clear() {
        prev_num_.clear();
        active_num_.clear();
        operator_ = BOperator::None;
        is_dot = false;
    }
    void SetPrevNum(const QString& str) {
        prev_num_ = str;
    }
    bool IsSignInMiddle() const {
        return !prev_num_.isEmpty() && !active_num_.isEmpty();
    }
    bool IsActiveNumberEmpty() const {
        return active_num_.isEmpty();
    }
    QString BOperatorToString() {
        switch(operator_) {
        case BOperator::Add: return "+";
        case BOperator::Divide: return "/";
        case BOperator::Multiply: return "*";
        case BOperator::Subtract: return "-";
        default: return "Unknown";
        }
    }

    QString prev_num_;
    QString active_num_;
    BOperator operator_ = BOperator::None;
    bool is_dot = false;

    static double ApplyOperator(double left, double right, BOperator op) {
        switch(op) {
        case BOperator::Add:
            return left + right;
        case BOperator::Subtract:
            return left - right;
        case BOperator::Multiply:
            return left * right;
        case BOperator::Divide:
            if (right == 0) throw std::runtime_error("Division by zero");
            return left / right;
        default: throw std::runtime_error("Unknown operator");
        }
    }

    static double ApplyOperator(double number, UOperator op) {
        switch(op) {
        case UOperator::ChangeSign:
            return -number;
        case UOperator::Percent:
            return 123; ///////////////
        default: throw std::runtime_error("Unknown operator");
        }
    }

    std::optional<BOperator> StringToBOperator(const QString& input) {
        if(input == "+") return BOperator::Add;
        if(input == "-") return BOperator::Subtract;
        if(input == "*") return BOperator::Multiply;
        if(input == "/") return BOperator::Divide;
        return std::nullopt;
    }
    std::optional<UOperator> StringToUOperator(const QString& input) {
        if(input == "+/-")  return UOperator::ChangeSign;
        if(input == "%")    return UOperator::Percent;
        return std::nullopt;
    }



};

#endif // CALCULATORMODEL_H
