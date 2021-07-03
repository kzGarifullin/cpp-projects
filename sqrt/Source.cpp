#include <iostream>
#include <vector>
#include<cmath>
#include<exception>
#include <algorithm>

template <typename T> 
void sqrt(std::vector<T>& v)
{
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i] < 0) 
        {
            throw(-1);
        }
        else 
        {
            v[i] = std::pow(v[i], 0.5);
        }
    }
}
int main() 
{
    std::vector<double>a{ 1,4,9,16 };

    try
    {
        sqrt(a);
        std::for_each(a.begin(), a.end(), [](auto x) {std::cout << x<<" "; });
      
    }
    catch (int a)
    {
        // Любые исключения типа int, сгенерированные в блоке try, приведенном выше, обрабатываются здесь
        std::cerr << "We caught an int exception with value: " << a << '\n';
    }

}