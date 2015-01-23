#ifndef FIRE_EXCEPTION_H
#define FIRE_EXCEPTION_H

#include <exception>
#include <string>

class FireException : public std::exception
{
public:
    FireException(std::string message);
    virtual ~FireException() throw() {}

    std::string getMessage() { return m_message; }
private:
    std::string m_message;
};

#endif // FIRE_EXCEPTION_H
