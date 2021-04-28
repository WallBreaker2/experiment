#include <iostream>
#include "../util/visitor.h"

int main(int argc, char* argv[]){
    int a[10]={1,2,3,4,5,6,7,8,9,10};
    slide_window(a,a+10,
                [](int* b,int* e){
                        int s=0; 
                        while(b!=e)s+=*b++;std::cout<<"s:"<<s<<" ";
                    },
                2);
    std::cout<<std::endl;
    window2d_t wd(2,1);
    using iterator2d_t = std::pair<int*,int*>;
    iterator2d_t lt(a,a);
    iterator2d_t rb(a+10,a);
    slide_window(lt, rb,
                [](iterator2d_t lt, iterator2d_t rb){
                        int s=0; 
                        while(lt.first!=rb.first)s+=*lt.first++;std::cout<<"s:"<<s<<" ";
                    },
                wd);
    return 0;
}