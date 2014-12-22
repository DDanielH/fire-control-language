#ifndef NODES_HPP_INCLUDED
#define NODES_HPP_INCLUDED

#include <stdexcept>
#include <string>
#include <sstream>
#include <memory>
#include <cmath>
#include <vector>
#include "../backend/context.hpp"

struct FireString
{
    const char* string;
    int length;
};

class Node
{
public:
    virtual ~Node() = default;
    virtual void execute(Context* context) const = 0;
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
    void execute(Context* context) const override{}
};



class ThreadNode : public Node
{
private:
    std::unique_ptr<CommandListNode> m_block;
    std::string m_name;
public:
    ThreadNode(CommandListNode* block,const char* name, int length)
    :m_block(block),m_name(name, length)
    {
    }
    std::string const& getName() const
    {
        return m_name;
    }
     void execute(Context* context) const override{}
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
    std::vector<std::unique_ptr<ThreadNode>> const& getThreads() const
    {
        return m_threads;
    }
    void execute(Context* context) const override{}

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
     void execute(Context* context) const override{}
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
    std::unique_ptr<FireNode> const& getFire() const
    {
        return m_fire;
    }
    std::unique_ptr<ThreadListNode> const& getThreads() const
    {
        return m_threads;
    }
    void execute(Context* context) const override{}
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
     void execute(Context* context) const override{}
};

class FuncCallNode : public CommandNode
{
private:
     std::unique_ptr<ParamListNode> m_params;
     std::string m_id;
public:
    FuncCallNode(const char* id, int length,  ParamListNode* params)
    :m_params(params),
     m_id(id, length)
    {
    }
     void execute(Context* context) const override{}
};


class StringNode : public ExpressionNode
{
private:
    std::string m_value;
public:
    StringNode(const char* value, int length)
    : m_value(value, length)
    {
    }
     void execute(Context* context) const override{}
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
     void execute(Context* context) const override{}
};

#endif // NODES_HPP_INCLUDED
