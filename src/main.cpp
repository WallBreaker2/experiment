#include <iostream>
#include <vector>

#include <functional>
#include <windows.h>
#include <math.h>

#include "util.h"
using namespace std;

template<class T>
void tsort(T* begin,T* end){
    while(begin != end){
        cout<<*begin<<" ";
        begin++;
    }
}

template<class F>
std::function<void()> toVoidFunc(F&& f){
    return [f](){f();};
}

class CallList{
public:
    typedef std::function<void()> call_type;
    template<class F, class... Args>
    void append(F&& f, Args&&... args){
        call_type c = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
        m_calls.push_back(toVoidFunc(c));
    }
    void runAll(){
        for(call_type c : m_calls){
            c();
        }
    }
private:
    std::vector<call_type> m_calls;
};

int func1(int a,int b){
    std::cout<<"func1\n";
    return a+b;
}

void func2(int a){
    std::cout<<"func2\n";
}

struct A{
    long func3(int a,int b){
        std::cout<<"func3"<<a<<","<<b<<std::endl;
        return a + b;
    }
};

#define INCH 0.03937

float GetDPI()
{
    HDC hdcScreen;
    hdcScreen = CreateDCW(L"DISPLAY", NULL, NULL, NULL);

   int logx = GetDeviceCaps(hdcScreen,LOGPIXELSX);
   int logy = GetDeviceCaps(hdcScreen,LOGPIXELSY);
    std::cout<<"logx:"<<logx<<std::endl;
    std::cout<<"logy:"<<logy<<std::endl;
    if (NULL != hdcScreen)
    {
        DeleteDC(hdcScreen);
    }
    float dpi = 1.0;
    if(logx == 96){
        dpi = 1.0;
    }else if(logx == 120){
        dpi = 1.25;
    }else if(logx == 144){
        dpi = 1.50;
    }else if(logx == 192){
        dpi = 2.0;
    }
  
    return dpi;
}

int main()
{
    CallList cl;
    cl.append(func1,1,2);
    cl.append(func2,1);

    A aa;
    cl.append(&A::func3, &aa, 3, 4);
    cl.runAll();
 
    int a[]={1,2,3};
    tsort(a, a+3);

    std::cout<<GetDPI()<<std::endl;
    std::cout<<"add :"<<add(1,1)<<std::endl;
    return 0;
}

