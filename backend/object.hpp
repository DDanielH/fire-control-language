#ifndef OBJECT_HPP_INCLUDED
#define OBJECT_HPP_INCLUDED

#include <memory>

class Object
{
public:
    virtual std::string toString() const = 0;
};

typedef std::shared_ptr<Object> ObjectPointer;

class String : public Object
{
private:
    std::string m_value;

public:
    String(std::string const& value)
        :m_value(value)
    {
    }

    std::string getValue() { return m_value; }

    std::string toString() const override { return m_value; }
};

class Integer : public Object
{
private:
    int m_value;

public:
    Integer(int value)
        :m_value(value)
    {
    }

    int getValue() { return m_value; }

    std::string toString() const override { return std::to_string(m_value); }
};

class Boolean : public Object {
private:
    bool m_value;

public:
    Boolean(bool value)
        :m_value(value)
    {
    }

    bool getValue() { return m_value; }

    std::string toString() const override
    {
        if (m_value)
            return "true";
        else
            return "false";
    }
};

inline std::string toString(ObjectPointer const& obj)
{
    if (obj == nullptr)
        return "null";
    return obj->toString();
}

#endif // OBJECT_HPP_INCLUDED
