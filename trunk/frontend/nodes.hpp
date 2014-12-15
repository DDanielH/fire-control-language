#ifndef NODES_HPP_INCLUDED
#define NODES_HPP_INCLUDED

#include <stdexcept>
#include <string>
#include <sstream>
#include <memory>
#include <cmath>
#include <vector>

class Node
{
public:
    virtual ~Node() = default;

};

class ExpressionNode : public Node
{
};
class CommandNode : public Node
{
};



class CommandListNode : public Node
{
private:
    std::vector<std::unique_ptr<CommandNode>> m_commands;
public:
    CommandListNode()
    {}
    void add(CommandNode* node)
    {
        //nur ein Pointer in die Liste hinzufügen
        m_commands.emplace_back(node);
    }

};



class ThreadNode : public Node
{
private:
    std::unique_ptr<CommandListNode> m_block;
    std::string m_name;
public:
    ThreadNode(CommandListNode* block,std::string const& name)
    :m_block(block),m_name(name)
    {
    }


};


class ThreadListNode : public Node
{
private:
    std::vector<std::unique_ptr<ThreadNode>> m_threads;
public:
    ThreadListNode()
    {}
    void add(ThreadNode* thread)
    {
        //nur ein Pointer in die Liste hinzufügen
        m_threads.emplace_back(thread);
    }
};




class FireNode : public Node
{
private:
    std::unique_ptr<CommandListNode> m_block;
public:
    FireNode(CommandListNode* block)
    :m_block(block)
    {
    }
};

class ProgramNode : public Node
{
private:
    std::unique_ptr<FireNode> m_fire;
    std::unique_ptr<ThreadListNode> m_threads;
public:
    ProgramNode(FireNode* fire, ThreadListNode* threads)
    :m_fire(fire), m_threads(threads)
    {
    }

};






class ParamListNode : public Node
{
private:
    std::vector<std::unique_ptr<ExpressionNode>> m_params;
public:
    ParamListNode()
    {}
    void add(ExpressionNode* expNode)
    {
        //nur ein Pointer in die Liste hinzufügen
        m_params.emplace_back(expNode);
    }

};

class FuncCallNode : public CommandNode
{
private:
     std::unique_ptr<ParamListNode> m_params;
     std::string m_id;
public:
    FuncCallNode(std::string id, ParamListNode* params)
    :m_params(params),
     m_id(id)
    {
    }
};


class StringNode : public ExpressionNode
{
private:
    std::string m_value;
public:
    StringNode(std::string const& value)
    : m_value(value)
    {
    }


};


class IntegerNode : public ExpressionNode
{
private:
    int m_value;
public:
    IntegerNode(int value)
    : m_value(value)
    {

    }

};

#endif // NODES_HPP_INCLUDED
