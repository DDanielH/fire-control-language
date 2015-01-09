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
    void execute(Context* context) const override{
        for (auto& command : m_commands)
        {
            command->execute(context);
        }
    }
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
     void execute(Context* context) const override{
        m_block->execute(context);
     }
    std::string const& getName() const
    {
        return m_name;
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
     void execute(Context* context) const override{
        throw std::runtime_error("ThreadListNode: Do not call this Function.");
     }
    std::vector<std::unique_ptr<ThreadNode>> const& getThreads() const
    {
        return m_threads;
    }

};


class ClientNode : public Node
{
private:
    std::unique_ptr<CommandListNode> m_block;
    std::string m_name;
public:
    ClientNode(CommandListNode* block,const char* name, int length)
    :m_block(block),m_name(name, length)
    {
    }
     void execute(Context* context) const override{
        m_block->execute(context);
     }
    std::string const& getName() const
    {
        return m_name;
    }
};


class ClientListNode : public Node
{
private:
    std::vector<std::unique_ptr<ClientNode>> m_clients;
public:
    ClientListNode()
    {}
    void add(ClientNode* client)
    {
        //nur ein Pointer in die Liste hinzufügen
        m_clients.emplace_back(client);
    }
     void execute(Context* context) const override{
        throw std::runtime_error("ClientListNode: Do not call this Function.");
     }
    std::vector<std::unique_ptr<ClientNode>> const& getClients() const
    {
        return m_clients;
    }

};


class ForeachNode : public CommandNode
{
private:
    std::unique_ptr<CommandListNode> m_block;
    std::string m_collection;
    std::string m_var;

public:
    ForeachNode(CommandListNode* block, const char* collection, int collectionLength, const char* var, int varLength)
    :m_block(block), m_collection(collection, collectionLength), m_var(var, varLength)
    {
    }
    //TODO
     void execute(Context* context) const override{
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
     void execute(Context* context) const override{
        m_block->execute(context);
     }
};

class ProgramNode : public Node
{
private:
    std::unique_ptr<FireNode> m_fire;
    std::unique_ptr<ThreadListNode> m_threads;
    std::unique_ptr<ClientListNode> m_clients;
public:
    ProgramNode(FireNode* fire, ThreadListNode* threads, ClientListNode* clients)
    :m_fire(fire), m_threads(threads), m_clients(clients)
    {
    }
     void execute(Context* context) const override{
        m_fire->execute(context);
     }
    std::unique_ptr<FireNode> const& getFire() const
    {
        return m_fire;
    }
    std::unique_ptr<ThreadListNode> const& getThreads() const
    {
        return m_threads;
    }
    std::unique_ptr<ClientListNode> const& getClients() const
    {
        return m_clients;
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
     void execute(Context* context) const override {
        for (auto& param : m_params)
        {
            param->execute(context);
        }
     }

     int getLength() {
        return m_params.size();
     }
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
     void execute(Context* context) const override{
        m_params->execute(context);
        context->call(m_id,m_params->getLength());
     }
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
     void execute(Context* context) const override{
        context->pushString( m_value);
     }
};

class IdentifierNode : public ExpressionNode
{
private:
    std::string m_value;
public:
    IdentifierNode(const char* value, int length)
    : m_value(value, length)
    {
    }
    //TODO
     void execute(Context* context) const override{

     }
};

class VarDeclarationNode : public CommandNode
{
private:
    std::string m_name;
    std::unique_ptr<ExpressionNode> m_expression;
public:
    VarDeclarationNode(const char* name, int length, ExpressionNode* expressionNode)
    : m_name(name, length), m_expression(expressionNode)
    {
    }
    //TODO
    void execute(Context* context) const override{

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
     void execute(Context* context) const override{
        context->pushInteger( m_value);
     }
};

#endif // NODES_HPP_INCLUDED
