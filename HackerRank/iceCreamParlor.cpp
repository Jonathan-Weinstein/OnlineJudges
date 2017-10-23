#include <iostream>
#include <limits>
using namespace std;
#include <string.h>

void answer(int k, int n, int* pos)//want the 1 based indexes of two prices that sum to k
{
    int i=1, a;

    for (; i<=n; ++i)
    {
        cin>>a;

        if (a>=k)
            continue;
        if (pos[k-a])
            break;

        pos[a]=i;//overwriting a previously seen elements index with a later one doesn't matter, any index will do
    }

    cout<<pos[k-a]<<' '<<i<<'\n';
}

int main()
{
    static int buf[10001]={};
    int t=0;
    cin>>t;

    if (t>0)
        for(;; memset(buf, 0, sizeof buf), cin.ignore(numeric_limits<streamsize>::max(), '\n'))
        {
            int k, n;
            cin>>k>>n;
            answer(k, n, buf);
            if (--t==0)
                break;
        }

    return 0;
}
