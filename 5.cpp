#include <iostream>
using namespace std;

double f1(double a, double b)
{
    return a + b;
}

double f2(double a, double b)
{
    return a / b;
}

template <class Function1, class Function2>
struct type_traits;

template <class F1, class F2, class In1, class In2>
struct type_traits<F1(*)(In1, In2), F2(*)(In1, In2)> {
    using type1 = In1;
    using type2 = In2;
};

template<class F1, class F2>
auto multiply_function(F1 f1, F2 f2)
{
    using Type1 = typename type_traits<decltype(f1), decltype(f2)>::type1;
    using Type2 = typename type_traits<decltype(f1), decltype(f2)>::type2;

    return [=](Type1 a, Type2 b) { return f1(a, b) * f2(a, b); };
};

int main(){
    auto f = multiply_function(f1, f2);
}