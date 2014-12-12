#ifndef NODES_HPP_INCLUDED
#define NODES_HPP_INCLUDED

#include <stdexcept>
#include <string>
#include <sstream>
#include <memory>
#include <cmath>

class ExprNode
{
public:
    virtual ~ExprNode() = default;

    virtual double calculate() = 0;

    virtual std::string toReversePolishNotation() = 0;
};

enum Operator
{
    OP_PLUS,
    OP_MINUS,
    OP_TIMES,
    OP_DIVIDE
};

class BinaryOpNode : public ExprNode
{
public:
    BinaryOpNode(ExprNode* left, ExprNode* right, Operator op)
        : m_left(left)
        , m_right(right)
        , m_op(op)
    {
    }

    double calculate() override
    {
        auto left = m_left->calculate();
        auto right = m_right->calculate();

        switch (m_op)
        {
        case OP_PLUS: return left + right;
        case OP_MINUS: return left - right;
        case OP_TIMES: return left * right;
        case OP_DIVIDE: return left / right;
        default:
            throw std::runtime_error("Operator not defined");
        }
    }

    std::string toReversePolishNotation() override
    {
        auto left = m_left->toReversePolishNotation();
        auto right = m_right->toReversePolishNotation();
        std::stringstream out;
        out << left << right;
        switch (m_op)
        {
            case OP_PLUS:
                out << "+";
                break;

            case OP_MINUS:
                out << "-";
                break;

            case OP_TIMES:
                out << "*";
                break;

            case OP_DIVIDE:
                out << "/";
                break;

            default:
                throw std::runtime_error("Operator not defined");
        }
        out << " ";
        return out.str();
    }

private:
    std::unique_ptr<ExprNode> m_left;
    std::unique_ptr<ExprNode> m_right;
    Operator m_op;
};

class ValueNode : public ExprNode
{
public:
    ValueNode(double value)
        : m_value(value)
    { }

    double calculate() override
    {
        return m_value;
    }

    std::string toReversePolishNotation() override
    {
        std::stringstream out;
        out << m_value << " ";
        return out.str();
    }

private:
    double m_value;
};

class SinNode : public ExprNode
{
public:
    SinNode(ExprNode* arg)
        : m_arg(arg)
    { }

    double calculate() override
    {
        auto arg = m_arg->calculate();
        return std::sin(arg);
    }

    std::string toReversePolishNotation() override
    {
        auto arg = m_arg->toReversePolishNotation();
        std::stringstream out;
        out << arg << "sin ";
        return out.str();
    }

private:
    std::unique_ptr<ExprNode> m_arg;
};

class CosNode : public ExprNode
{
public:
    CosNode(ExprNode* arg)
        : m_arg(arg)
    { }

    double calculate() override
    {
        auto arg = m_arg->calculate();
        return std::cos(arg);
    }

    std::string toReversePolishNotation() override
    {
        auto arg = m_arg->toReversePolishNotation();
        std::stringstream out;
        out << arg << "cos ";
        return out.str();
    }

private:
    std::unique_ptr<ExprNode> m_arg;
};

class MaxNode : public ExprNode
{
public:
    MaxNode(ExprNode* left, ExprNode* right)
        : m_left(left)
        , m_right(right)
    { }

    double calculate() override
    {
        auto left = m_left->calculate();
        auto right = m_right->calculate();
        return std::max(left, right);
    }

    std::string toReversePolishNotation() override
    {
        auto left = m_left->toReversePolishNotation();
        auto right = m_right->toReversePolishNotation();
        std::stringstream out;
        out << left << right << "max ";
        return out.str();
    }

private:
    std::unique_ptr<ExprNode> m_left;
    std::unique_ptr<ExprNode> m_right;
};

#endif // NODES_HPP_INCLUDED
