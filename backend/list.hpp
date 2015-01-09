#ifndef LIST_HPP_INCLUDED
#define LIST_HPP_INCLUDED

#include <vector>
#include "object.hpp"

class List
{
private:
    virtual std::vector<Object> m_list;
public:
    virtual void add(Object& item)
    {
        m_list.emplace_back(item);
    }

};


#endif // LIST_HPP_INCLUDED
