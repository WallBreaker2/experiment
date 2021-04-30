#ifndef __VISTOR_H_
#define __VISTOR_H_
#include <utility>
template <class IteratorType, class F>
void slide_window(IteratorType begin, IteratorType end, F f, size_t window)
{
    size_t diff = end - begin;
    if (diff < window)
    {
        return;
    }
    size_t slide_cnt = diff - window + 1;
    for (size_t i = 0; i < slide_cnt; ++i)
    {
        f(begin, begin + window);
        ++begin;
    }
}
using window2d_t = std::pair<size_t, size_t>;
template <class IteratorType, class F>
void slide_window(std::pair<IteratorType, IteratorType> lefttop,
                  std::pair<IteratorType, IteratorType> rightbottom,
                  F f, window2d_t window)
{
    using iterator_t = std::pair<IteratorType, IteratorType>;
    size_t diffx = rightbottom.first - lefttop.first;
    size_t diffy = rightbottom.second - lefttop.second;
    if (diffx < window.first || diffy < window.second)
    {
        return;
    }
    size_t slidex = diffx - window.first + 1;
    size_t slidey = diffy - window.second + 1;
    for (size_t y = 0; y < slidey; ++y)
    {
        for (size_t x = 0; x < slidex; ++x)
        {
            f(lefttop,
              iterator_t(lefttop.first + window.first, lefttop.second + window.second));
            ++lefttop.first;
        }
        ++lefttop.second;
    }
}

#endif