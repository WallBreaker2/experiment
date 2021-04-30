#ifndef __TREE_LAYOUT_H
#define __TREE_LAYOUT_H
#include <list>
#include <iostream>
#include <vector>
struct rect_t
{
    rect_t(int l, int b, int r, int t) : left(l), bottom(b), right(r), top(t)
    {
    }
    rect_t(int a = 0) : left(a), bottom(a), right(a), top(a) {}
    int left;
    int bottom;
    int right;
    int top;
};

struct MarginDesc
{
    enum MarginDescEnum
    {
        Inner = 0X1,
        Outer = 0X2,
        Left = 0X4,
        Right = 0X8,
        Bottom = 0X10,
        Top = 0X20,
        ILeftBottom = Inner | Left | Bottom,
        IRightBottom = Inner | Right | Bottom,
        ILeftTop = Inner | Left | Top,
        IRightTop = Inner | Right | Top,
        OLeftBottom = Outer | Left | Bottom,
        ORightBottom = Outer | Right | Bottom,
        OLeftTop = Outer | Left | Top,
        ORightTop = Outer | Right | Top
    };
    MarginDesc(int type_ = Inner, const rect_t &margin_ = rect_t(0)) : type(type_), margin(margin_) {}

    int type;

    rect_t margin;
};
struct node_t
{
    std::list<node_t *> childs;
    rect_t rect;
    node_t *m_parent;
    MarginDesc m_desc;
    node_t(const rect_t &r) : rect(r), m_parent(nullptr) {}
    node_t(node_t *parent = nullptr, const MarginDesc &desc = MarginDesc()) : m_parent(parent), m_desc(desc)
    {
        if (m_parent) //add child node to parent
        {
            m_parent->childs.push_back(this);
        }
    }
    ~node_t() {}
    //eval current node by margin and parent node
    void eval()
    {
        if (!m_parent)
            return;
        rect_t par = m_parent->rect;
        rect_t mg = m_desc.margin;
        int type = m_desc.type;
        if (type == MarginDesc::Inner)
        {
            rect.left = par.left + mg.left;
            rect.bottom = par.bottom + mg.bottom;
            rect.right = par.right - mg.right;
            rect.top = par.top - mg.top;
        }
        else if (type == MarginDesc::Outer)
        {
            rect.left = par.left - mg.left;
            rect.bottom = par.bottom - mg.bottom;
            rect.right = par.right + mg.right;
            rect.top = par.top + mg.top;
        }
        else if (type == MarginDesc::Left)
        {
            rect.left = par.left - mg.left;
            rect.bottom = par.bottom + mg.bottom;
            rect.right = par.left - mg.right;
            rect.top = par.top + mg.top;
        }
        else if (type == MarginDesc::Right)
        {
            rect.left = par.right + mg.left;
            rect.bottom = par.bottom + mg.bottom;
            rect.right = par.right + mg.right;
            rect.top = par.top + mg.top;
        }
        else if (type == MarginDesc::Bottom)
        {
            rect.left = par.left + mg.left;
            rect.bottom = par.bottom - mg.bottom;
            rect.right = par.left + mg.right;
            rect.top = par.top - mg.top;
        }
        else if (type == MarginDesc::Top)
        { //top
            rect.left = par.left + mg.left;
            rect.bottom = par.bottom + mg.bottom;
            rect.right = par.left + mg.right;
            rect.top = par.top + mg.top;
        }
        else if (type == MarginDesc::ILeftBottom)
        {
            rect.left = par.left + mg.left;
            rect.bottom = par.bottom + mg.bottom;
            rect.right = rect.left + mg.right;
            rect.top = rect.bottom + mg.top;
        }
        else if (type == MarginDesc::IRightBottom)
        {
            rect.left = par.right - mg.left - mg.right;
            rect.bottom = par.bottom + mg.bottom;
            rect.right = rect.left + mg.right;
            rect.top = rect.bottom + mg.top;
        }
        else if (type == MarginDesc::ILeftTop)
        {
            rect.left = par.left + mg.left;
            rect.bottom = par.top - mg.bottom - mg.top;
            rect.right = rect.left + mg.right;
            rect.top = rect.bottom + mg.top;
        }
        else if (type == MarginDesc::IRightTop)
        { //top
            rect.left = par.right - mg.left - mg.right;
            rect.bottom = par.top - mg.bottom - mg.top;
            rect.right = rect.left + mg.right;
            rect.top = rect.bottom + mg.top;
        }
        else if (type == MarginDesc::OLeftBottom)
        {
            rect.left = par.left - mg.left - mg.right;
            rect.bottom = par.bottom - mg.bottom - mg.top;
            rect.right = rect.left + mg.right;
            rect.top = rect.bottom + mg.top;
        }
        else if (type == MarginDesc::ORightBottom)
        {
            rect.left = par.right + mg.left;
            rect.bottom = par.bottom - mg.bottom - mg.top;
            rect.right = rect.left + mg.right;
            rect.top = rect.bottom + mg.top;
        }
        else if (type == MarginDesc::OLeftTop)
        {
            rect.left = par.left - mg.left - mg.right;
            rect.bottom = par.top + mg.bottom;
            rect.right = rect.left + mg.right;
            rect.top = rect.bottom + mg.top;
        }
        else if (type == MarginDesc::ORightTop)
        {
            rect.left = par.right + mg.left;
            rect.bottom = par.top + mg.bottom;
            rect.right = rect.left + mg.right;
            rect.top = rect.bottom + mg.top;
        }
        else
        {
            //do nothing
        }
    }
};

std::ostream &operator<<(std::ostream &os, const node_t &node);

struct node_iterator
{
    node_t *node;
    int branch;
    node_iterator(node_t *p, int b = 0) : node(p), branch(b) {}
};

class iteraotr_t
{
public:
    iteraotr_t(node_t *begin = nullptr) : node(begin)
    {
        if (node != nullptr)
        {
            sk.push_back(node_iterator(node));
        }
    }
    iteraotr_t &operator++()
    {
        next();
        return *this;
    }
    iteraotr_t operator++(int)
    {
        iteraotr_t tmp(*this);
        next();
        return tmp;
    }
    node_t *operator->()
    {
        return node;
    }

    node_t &operator*()
    {
        return *node;
    }

    bool operator==(const iteraotr_t &rhs)
    {
        return node == rhs.node;
    }

    bool operator!=(const iteraotr_t &rhs)
    {
        return !operator==(rhs);
    }

private:
    void next()
    {
        while (!sk.empty())
        {

            if (sk.back().branch < node->childs.size())
            {
                node = *std::next(node->childs.begin(), sk.back().branch);
                std::cout << " sk size:" << sk.size();
                sk.push_back(node_iterator(node));
                break;
            }
            else //leaf node
            {
                sk.pop_back();
                if (!sk.empty())
                {
                    node = sk.back().node;
                    sk.back().branch++;
                }
                else
                {
                    node = nullptr;
                    break;
                }
            }
        }
    }

    node_t *node;
    std::vector<node_iterator> sk;
};

class tree_layout
{
public:
    static void clear(node_t *node);

    static void apply(node_t *node);

    static void print(node_t *node);

    static iteraotr_t begin(node_t *node);

    static iteraotr_t end();

    static void restrict(node_t *node, void (*visit)(node_t *));
};

#endif