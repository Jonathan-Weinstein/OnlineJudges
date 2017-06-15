#include <cstdint>
#include <iostream>
#include <algorithm>
using namespace std;

typedef std::uint_least64_t uprice_t;

struct entry
{
    uprice_t val;
    unsigned original_pos;//wastes some space

    bool operator<(const entry& r) const {return val<r.val;}
};

int main()
{
    int n=0;
    cin>>n;

    if (n>1)
    {
        entry *const buf = new entry[n];
        entry *const past= buf+n;

        for (int i=0; i!=n; ++i)
        {
            cin>>buf[i].val;
            buf[i].original_pos=i;
        }

        sort(buf, past);

        uprice_t minloss = ~0ull;
        for (const entry* it=buf+1; it!=past; ++it)//know at least 2 elements
        {
            if (it[-1].original_pos > it[0].original_pos)//if something with a lower value(did sort) came after
            {
                const uprice_t closs = it[0].val - it[-1].val;
                if (closs<minloss)
                    minloss=closs;
            }
            //else it cam before it, and since it has a lower value we can forget about the other
        }

        cout<<minloss<<'\n';
        delete[]buf;
        return 0;
    }
    else
        return 1;
}
