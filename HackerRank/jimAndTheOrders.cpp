#include <iostream>
#include <algorithm>
using namespace std;

struct order
{
    int done, id;
};

inline bool operator<(order a, order b)
{
    return a.done<b.done || (a.done==b.done && a.id<b.id);
}

int main()
{
    static order v[1000];
    int n;
    cin>>n;

    for (int i=0; i!=n; ++i)
    {
        int start, duration;
        cin>>start>>duration;
        v[i] = {start+duration, i+1};
    }

    sort(v, v+n);
    for (int i=0; i!=n; ++i) cout<<v[i].id<<' ';
    return 0;
}
