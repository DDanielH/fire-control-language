#ifndef LIST_HPP_INCLUDED
#define LIST_HPP_INCLUDED

#include <vector>
#include "object.hpp"

class List
{
private:
    std::vector<ObjectPointer> m_list;
public:
    void add(ObjectPointer item)
    {
        m_list.emplace_back(item);
    }

};


#endif // LIST_HPP_INCLUDED
