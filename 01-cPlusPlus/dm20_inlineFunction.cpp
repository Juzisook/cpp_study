//
// Created by YANHAI on 2019/4/30.
//

/*
 * C++中的const常量可以替代宏常数定义，如
 *      const int A = 3;
 *      #define A 3
 * C++中是否有解决方案替代代码片段呢？ （替代宏代码片段就可以避免宏的副作用）
 *
 * C++中推荐使用内联函数替代代码片段
 * C++中使用inline关键字声明内联函数
 *
 * 内联函数声明时inline关键字必须和函数定义结合在一起，否则编译器会直接忽略内联请求。
 */

#include <iostream>
using namespace std;

inline void printA()
{
    int a = 10;
    cout << "a: " << a << endl;
}

int main1()
{
    printA();
    return 0;
}

#define MYFUNC(a, b) ((a) < (b) ? (a) : (b))

inline int myfunc(int a, int b)
{
    return a < b ? a : b;
}

int main2()
{
    int a = 1;
    int b = 3;
//    int c = myfunc(++a, b);   // a=2 b=3 c=2
    int c = MYFUNC(++a, b);     // a=3 b=3 c=3

    printf("a: %d\n", a);
    printf("b: %d\n", b);
    printf("c: %d\n", c);
    return 0;
}

int main()
{
    main1();
    main2();
    return 0;
}

/*
 * 说明：
 *    1. 内联函数inline int func(int a, int b)必须和函数体的实现，写在一块
 *    2. C++编译器可以将一个函数进行内联编译
 *       被C++编译器内联编译的函数叫做内联函数
 *       内联函数在最终生成的代码中是没有定义的
 *       C++编译器直接将函数体插入函数调用的地方
 *       内联函数没有普通函数调用时的额外开销（压栈，跳转，返回）
 *    3. C++编译器不一定准许函数的内联请求！
 *    4. 内联函数是一种特殊的函数，具有普通函数的特征（参数检查，返回类型等）
 *       内联函数是对编译器的一种请求，因此编译器可以拒绝这种请求
 *       内联函数由编译器处理，直接将变异后的函数体插入调用的地方
 *       宏代码片段由预处理器处理，进行简单的文本替换，没有任何编译过程
 *    5. 现代C++编译器能够进行编译优化，因此一些内涵即使没有使用inline声明，也可以被编译器内联编译
 *       另外，一些现代C++编译器提供了扩展语法，能够对函数进行强制内联
 *       如g++中的__attribute((always_inline))属性
 *    6. C++中内联编译的限制：
 *        不能存在任何形式的循环语句
 *        不能存在过多的条件判断语句
 *        函数体不能过于庞大
 *        不能对函数进行取址操作
 *        函数内联声明必须在调用语句之前
 */

/*
 * 编译器对于内联函数的限制并不是绝对的，内联函数相对于普通函数的优势是省去了函数调用时压栈，跳转和返回的开销
 * 因此，当函数体的执行开销远大于压栈，跳转和返回所用的开销时，那么内联函数将无意义。
 */

/*
 * 结论：
 *  1. 内联函数在编译时直接将函数体插入函数调用的地方
 *  2. inline只是一种请求，编译器不一定允许这种请求
 *  3. 内联函数省去了普通函数调用时压栈，跳转和返回的开销
 */

