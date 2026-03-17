#pragma once
#include <iostream>
#include <string>
#include <vector>

class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual void print(int indent = 0) const = 0;

protected:
    static void pad(int indent) {
        for (int i = 0; i < indent; ++i) std::cout << ' ';
    }

    static void label(int indent, const std::string& text) {
        pad(indent);
        std::cout << text << "\n";
    }
};

class ExprNode : public ASTNode {
};

class StmtNode : public ASTNode {
};

class ParamNode : public ASTNode {
public:
    std::string name;
    std::string type;

    ParamNode(const std::string& n, const std::string& t) : name(n), type(t) {}

    void print(int indent = 0) const override {
        label(indent, "Param: " + name + " : " + type);
    }
};

class ParamListNode : public ASTNode {
public:
    std::vector<ParamNode*> params;

    ~ParamListNode() override {
        for (auto* p : params) delete p;
    }

    void add(ParamNode* p) {
        params.push_back(p);
    }

    void print(int indent = 0) const override {
        label(indent, "Params:");
        for (const auto* p : params) p->print(indent + 2);
    }
};

class ArgListNode : public ASTNode {
public:
    std::vector<ExprNode*> args;

    ~ArgListNode() override {
        for (auto* a : args) delete a;
    }

    void add(ExprNode* a) {
        args.push_back(a);
    }

    void print(int indent = 0) const override {
        label(indent, "Args:");
        for (const auto* a : args) a->print(indent + 2);
    }
};

class IdentifierNode : public ExprNode {
public:
    std::string name;

    IdentifierNode(const std::string& n) : name(n) {}

    void print(int indent = 0) const override {
        label(indent, "Identifier: " + name);
    }
};

class LiteralNode : public ExprNode {
public:
    std::string kind;
    std::string value;

    LiteralNode(const std::string& k, const std::string& v) : kind(k), value(v) {}

    void print(int indent = 0) const override {
        label(indent, "Literal(" + kind + "): " + value);
    }
};

class UnaryOpNode : public ExprNode {
public:
    std::string op;
    ExprNode* expr;

    UnaryOpNode(const std::string& o, ExprNode* e) : op(o), expr(e) {}

    ~UnaryOpNode() override {
        delete expr;
    }

    void print(int indent = 0) const override {
        label(indent, "UnaryOp: " + op);
        if (expr) {
            label(indent + 2, "Operand:");
            expr->print(indent + 4);
        }
    }
};

class BinaryOpNode : public ExprNode {
public:
    std::string op;
    ExprNode* left;
    ExprNode* right;

    BinaryOpNode(const std::string& o, ExprNode* l, ExprNode* r) : op(o), left(l), right(r) {}

    ~BinaryOpNode() override {
        delete left;
        delete right;
    }

    void print(int indent = 0) const override {
        label(indent, "BinaryOp: " + op);
        if (left) {
            label(indent + 2, "Left:");
            left->print(indent + 4);
        }
        if (right) {
            label(indent + 2, "Right:");
            right->print(indent + 4);
        }
    }
};

class CallNode : public ExprNode {
public:
    std::string callee;
    ArgListNode* args;

    CallNode(const std::string& c, ArgListNode* a) : callee(c), args(a) {}

    ~CallNode() override {
        delete args;
    }

    void print(int indent = 0) const override {
        label(indent, "Call: " + callee);
        if (args) args->print(indent + 2);
    }
};

class StatementListNode : public ASTNode {
public:
    std::vector<StmtNode*> statements;

    ~StatementListNode() override {
        for (auto* s : statements) delete s;
    }

    void add(StmtNode* s) {
        statements.push_back(s);
    }

    void print(int indent = 0) const override {
        label(indent, "Statements:");
        for (const auto* s : statements) s->print(indent + 2);
    }
};

class BlockNode : public StmtNode {
public:
    StatementListNode* statements;

    BlockNode(StatementListNode* s) : statements(s) {}

    ~BlockNode() override {
        delete statements;
    }

    void print(int indent = 0) const override {
        label(indent, "Block:");
        if (statements) statements->print(indent + 2);
    }
};

class LetNode : public StmtNode {
public:
    std::string name;
    std::string type;
    ExprNode* expr;

    LetNode(const std::string& n, const std::string& t, ExprNode* e) : name(n), type(t), expr(e) {}

    ~LetNode() override {
        delete expr;
    }

    void print(int indent = 0) const override {
        std::string text = "Let: " + name;
        if (!type.empty()) text += " : " + type;
        label(indent, text);
        if (expr) {
            label(indent + 2, "Value:");
            expr->print(indent + 4);
        }
    }
};

class AssignNode : public StmtNode {
public:
    std::string name;
    ExprNode* expr;

    AssignNode(const std::string& n, ExprNode* e) : name(n), expr(e) {}

    ~AssignNode() override {
        delete expr;
    }

    void print(int indent = 0) const override {
        label(indent, "Assign: " + name);
        if (expr) {
            label(indent + 2, "Value:");
            expr->print(indent + 4);
        }
    }
};

class ReturnNode : public StmtNode {
public:
    ExprNode* expr;

    ReturnNode(ExprNode* e) : expr(e) {}

    ~ReturnNode() override {
        delete expr;
    }

    void print(int indent = 0) const override {
        label(indent, "Return");
        if (expr) {
            label(indent + 2, "Value:");
            expr->print(indent + 4);
        }
    }
};

class ExprStmtNode : public StmtNode {
public:
    ExprNode* expr;

    ExprStmtNode(ExprNode* e) : expr(e) {}

    ~ExprStmtNode() override {
        delete expr;
    }

    void print(int indent = 0) const override {
        label(indent, "ExprStmt:");
        if (expr) expr->print(indent + 2);
    }
};

class IfNode : public StmtNode {
public:
    ExprNode* condition;
    BlockNode* thenBlock;
    BlockNode* elseBlock;

    IfNode(ExprNode* c, BlockNode* t, BlockNode* e) : condition(c), thenBlock(t), elseBlock(e) {}

    ~IfNode() override {
        delete condition;
        delete thenBlock;
        delete elseBlock;
    }

    void print(int indent = 0) const override {
        label(indent, "If");
        label(indent + 2, "Condition:");
        if (condition) condition->print(indent + 4);
        label(indent + 2, "Then:");
        if (thenBlock) thenBlock->print(indent + 4);
        if (elseBlock) {
            label(indent + 2, "Else:");
            elseBlock->print(indent + 4);
        }
    }
};

class WhileNode : public StmtNode {
public:
    ExprNode* condition;
    BlockNode* body;

    WhileNode(ExprNode* c, BlockNode* b) : condition(c), body(b) {}

    ~WhileNode() override {
        delete condition;
        delete body;
    }

    void print(int indent = 0) const override {
        label(indent, "While");
        label(indent + 2, "Condition:");
        if (condition) condition->print(indent + 4);
        label(indent + 2, "Body:");
        if (body) body->print(indent + 4);
    }
};

class ForNode : public StmtNode {
public:
    std::string var;
    ExprNode* start;
    ExprNode* end;
    BlockNode* body;

    ForNode(const std::string& v, ExprNode* s, ExprNode* e, BlockNode* b)
        : var(v), start(s), end(e), body(b) {}

    ~ForNode() override {
        delete start;
        delete end;
        delete body;
    }

    void print(int indent = 0) const override {
        label(indent, "For: " + var);
        label(indent + 2, "Start:");
        if (start) start->print(indent + 4);
        label(indent + 2, "End:");
        if (end) end->print(indent + 4);
        label(indent + 2, "Body:");
        if (body) body->print(indent + 4);
    }
};

class FunctionNode : public ASTNode {
public:
    std::string name;
    ParamListNode* params;
    std::string returnType;
    BlockNode* body;

    FunctionNode(const std::string& n, ParamListNode* p, const std::string& r, BlockNode* b)
        : name(n), params(p), returnType(r), body(b) {}

    ~FunctionNode() override {
        delete params;
        delete body;
    }

    void print(int indent = 0) const override {
        std::string text = "Function: " + name;
        if (!returnType.empty()) text += " -> " + returnType;
        label(indent, text);
        if (params) params->print(indent + 2);
        if (body) body->print(indent + 2);
    }
};

class ProgramNode : public ASTNode {
public:
    std::vector<FunctionNode*> functions;

    ~ProgramNode() override {
        for (auto* f : functions) delete f;
    }

    void add(FunctionNode* f) {
        functions.push_back(f);
    }

    void print(int indent = 0) const override {
        label(indent, "Program:");
        for (const auto* f : functions) f->print(indent + 2);
    }
};