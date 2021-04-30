#include <iostream>
#include "../util/visitor.h"
#include "tree_layout.h"
int main(int argc, char *argv[])
{
    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    slide_window(
        a, a + 10,
        [](int *b, int *e) {
            int s = 0;
            while (b != e)
                s += *b++;
            std::cout << "s:" << s << " ";
        },
        2);
    std::cout << std::endl;
    window2d_t wd(2, 1);
    using iterator2d_t = std::pair<int *, int *>;
    iterator2d_t lt(a, a);
    iterator2d_t rb(a + 10, a + 1);
    slide_window(
        lt, rb,
        [](iterator2d_t lt, iterator2d_t rb) {
            int s = 0;
            while (lt.first != rb.first)
                s += *lt.first++;
            std::cout << "s:" << s << " ";
        },
        wd);
    std::cout << std::endl;
    node_t root(rect_t(0, 0, 100, 100));
    tree_layout tl;
    tl.print(&root);
    node_t child1(&root, MarginDesc(MarginDesc::Inner, rect_t(20)));
    node_t child2(&root, MarginDesc(MarginDesc::Outer, rect_t(20)));
    node_t child_left(&root, MarginDesc(MarginDesc::Left, rect_t(20)));
    node_t child_right(&root, MarginDesc(MarginDesc::Right, rect_t(20)));
    node_t child_bottom(&root, MarginDesc(MarginDesc::Bottom, rect_t(20)));
    node_t child_top(&root, MarginDesc(MarginDesc::Top, rect_t(20)));
    node_t child_ilb(&root, MarginDesc(MarginDesc::ILeftBottom, rect_t(20)));
    node_t child_irb(&root, MarginDesc(MarginDesc::IRightBottom, rect_t(20)));
    node_t child_ilt(&root, MarginDesc(MarginDesc::ILeftTop, rect_t(20)));
    node_t child_irt(&root, MarginDesc(MarginDesc::IRightTop, rect_t(20)));
    node_t child_olb(&root, MarginDesc(MarginDesc::OLeftBottom, rect_t(20)));
    node_t child_orb(&root, MarginDesc(MarginDesc::ORightBottom, rect_t(20)));
    node_t child_olt(&root, MarginDesc(MarginDesc::OLeftTop, rect_t(20)));
    node_t child_ort(&root, MarginDesc(MarginDesc::ORightTop, rect_t(20)));
    node_t childc_o(&child_ort, MarginDesc(MarginDesc::Outer, rect_t(20)));
    std::cout << "before eval:\n";
    tl.print(&root);
    std::cout << "after eval:\n";
    tl.apply(&root);
    tl.print(&root);

    return 0;
}