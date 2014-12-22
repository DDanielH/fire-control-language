#ifndef OBJECT_HPP_INCLUDED
#define OBJECT_HPP_INCLUDED

#include <memory>

class Object
{

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
};

class Integer : public Object
{
private:
    int m_value;

public:
    Integer(int const& value)
        :m_value(value)
    {
    }

    int getValue() { return m_value; }
};

#endif // OBJECT_HPP_INCLUDED
