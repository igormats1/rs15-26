#ifndef VISITORNODES_H
#define VISITORNODES_H
#include "TreeNodes.hpp"
#include "automata.h"

class Visitor_nodes
{
public:
    Visitor_nodes()
    {}
    virtual ~Visitor_nodes()
    {}
    virtual void visit_reg_node(const Reg_node &reg) = 0;
    virtual void visit_binary_op(const Binary_op_reg_node & reg) = 0;
    virtual void visit_unary_op(const Unary_op_reg_node &reg) = 0;
    virtual void visit_union(const Union_reg_node & reg) = 0;
    virtual void visit_concat(const Concat_reg_node & reg) = 0;
    virtual void visit_star(const Star_reg_node & reg) = 0;
    virtual void visit_plus(const Plus_reg_node & reg) = 0;
    virtual void visit_ques(const Ques_reg_node & reg) = 0;
    virtual void visit_symbol(const Symbol_reg_node & reg) = 0;
    virtual void visit_normal_symbol(const Normal_symbol_reg_node & reg) = 0;
    virtual void visit_backslash_symbol(const Backslash_symbol_reg_node & reg) = 0;
    virtual void visit_char_class(const Char_class_reg_node & reg) = 0;
    virtual void visit_repetition(const Repetition_reg_node & reg) = 0;
    virtual void visit_empty(const Empty_reg_node & reg) = 0;
};

class PrintNodes : public Visitor_nodes
{
public:
    PrintNodes(ostream & ostr)
     :Visitor_nodes(), _ostr(ostr)
    {
    }
    void visit_reg_node(const Reg_node &reg);
    void visit_binary_op(const Binary_op_reg_node & reg);
    void visit_unary_op(const Unary_op_reg_node &reg);
    void visit_union(const Union_reg_node & reg);
    void visit_concat(const Concat_reg_node & reg);
    void visit_star(const Star_reg_node & reg);
    void visit_plus(const Plus_reg_node & reg);
    void visit_ques(const Ques_reg_node & reg);
    void visit_symbol(const Symbol_reg_node & reg);
    void visit_normal_symbol(const Normal_symbol_reg_node & reg);
    void visit_backslash_symbol(const Backslash_symbol_reg_node & reg);
    void visit_char_class(const Char_class_reg_node & reg);
    void visit_repetition(const Repetition_reg_node & reg);
    void visit_empty(const Empty_reg_node & reg);

public:
    ostream & _ostr;
};


class ThompsonNodes : public Visitor_nodes
{
public:
    ThompsonNodes()
     :Visitor_nodes()
    {
    }
    void visit_reg_node(const Reg_node &reg);
    void visit_binary_op(const Binary_op_reg_node & reg);
    void visit_unary_op(const Unary_op_reg_node &reg);
    void visit_union(const Union_reg_node & reg);
    void visit_concat(const Concat_reg_node & reg);
    void visit_star(const Star_reg_node & reg);
    void visit_plus(const Plus_reg_node & reg);
    void visit_ques(const Ques_reg_node & reg);
    void visit_symbol(const Symbol_reg_node & reg);
    void visit_normal_symbol(const Normal_symbol_reg_node & reg);
    void visit_backslash_symbol(const Backslash_symbol_reg_node & reg);
    void visit_char_class(const Char_class_reg_node & reg);
    void visit_repetition(const Repetition_reg_node & reg);
    void visit_empty(const Empty_reg_node & reg);

    Thompson getTh() const;
    int getLast() const;
    int getStart() const;
    QVector<char> getAlphabet() const;
    QVector<Edge> getEdges() const;

private:
    Thompson t;
};

template <typename T>
Union_reg_node * makeCharRegUnion(vector<T *> & elements)
{
   if (elements.size()==2)
     return new Union_reg_node(elements[0],elements[1]);
   T * sym = elements.back();
   elements.pop_back();
   return new Union_reg_node(makeCharRegUnion(elements),sym);
}

Concat_reg_node * makeCharRegConcat(Reg_node & reg, int k);

#endif // VISITORNODES_H
