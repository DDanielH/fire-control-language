#ifndef OBJECT_FUNCTIONS_HPP_INCLUDED
#define OBJECT_FUNCTIONS_HPP_INCLUDED

class GetType : public Function
{
public:
    GetType() : Function("getType")
    {
    }

    ObjectPointer execute(VM& vm, arg_list const& args) const override
    {
        if (args.size() != 1)
            throw std::runtime_error("Argument count not valid");

        auto typeName = getTypeName(args[0].get());
        return std::make_shared<String>(typeName);
    }

private:
    std::string getTypeName(Object* arg) const
    {
        if (dynamic_cast<Boolean*>(arg) != nullptr)
            return "Boolean";
        if (dynamic_cast<Integer*>(arg) != nullptr)
            return "Integer";
        if (dynamic_cast<String*>(arg) != nullptr)
            return "String";

        return "Object";
    }
};

class IsNull : public Function
{
public:
    IsNull() : Function("isNull")
    {
    }

    ObjectPointer execute(VM& vm, arg_list const& args) const override
    {
        if (args.size() != 1)
            throw std::runtime_error("Argument count not valid");

        bool isNull = args[0] == nullptr;
        return std::make_shared<Boolean>(isNull);
    }
};

#endif // OBJECT_FUNCTIONS_HPP_INCLUDED
