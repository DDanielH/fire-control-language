#ifndef LIST_HPP_INCLUDED
#define LIST_HPP_INCLUDED

#include <vector>
#include "object.hpp"

class List: public Object
{
private:
    std::vector<ObjectPointer> m_list;
public:

    void add(ObjectPointer item)
    {
        m_list.emplace_back(item);
    }
    std::string toString() const override
    {
        return "[FIRE:LIST]";
    }
};


#endif // LIST_HPP_INCLUDED
