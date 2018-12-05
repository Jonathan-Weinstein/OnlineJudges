#include <stdio.h>
#include <vector>

template<typename T>
union manual
{
    T obj;
    char char_array[sizeof(T)];
    constexpr manual() {}
    ~manual() {}
};


int main()
{
    manual< std::vector<int> > m;


    printf("%d\n", __is_pod(manual< std::vector<int> >));

    return 0;
}
