#include "tree_layout.h"
#include <iostream>
#include <vector>
#include <iterator>

std::ostream &operator<<(std::ostream &os, const node_t &node)
{
    os << "type:" << node.m_desc.type
       << " {" << node.rect.left << "," << node.rect.bottom << "," << node.rect.right << "," << node.rect.top << "}";
    return os;
}
void tree_layout::clear(node_t *node)
{
    if (node)
    {
        for (node_t *pn : node->childs)
        {
            clear(pn);
        }
        delete node;
    }
}
void tree_layout::apply(node_t *node)
{
    if (node)
    {
        if (node->m_parent)
        {
            node->eval();
        }
        for (node_t *pn : node->childs)
        {
            apply(pn);
        }
    }
}

void tree_layout::print(node_t *node)
{
    if (node)
    {
        rect_t &rect = node->rect;
        std::cout << (*node) << std::endl;
        for (node_t *pn : node->childs)
        {
            print(pn);
        }
    }
}

void tree_layout::restrict(node_t *node, void (*visit)(node_t *))
{
    std::vector<node_iterator> sk;
    if (node == nullptr)
    {
        return;
    }
    std::cout << " root:";
    visit(node);
    sk.push_back(node_iterator(node));
    while (true)
    {

        if (!node->childs.empty() && sk.back().branch < node->childs.size())
        {
            node = *std::next(node->childs.begin(), sk.back().branch);
            visit(node);
            sk.push_back(node_iterator(node));
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
                break;
            }
        }
    }
}

iteraotr_t tree_layout::begin(node_t *node)
{
    return iteraotr_t(node);
}

iteraotr_t tree_layout::end()
{
    return iteraotr_t(nullptr);
}
