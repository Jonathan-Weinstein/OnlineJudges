#include <iostream>
using namespace std;

void answer(int* data, int* pos, int n, int k)
{
    for (int i=0; n!=0 && k!=0; ++i, --n)
    {
        if (pos[n]!=i)
        {
            pos[data[i]]=pos[n];
            const int temp=data[i];
            data[i]=n;
            data[pos[n]]=temp;
            --k;
        }
    }
}

int main()
{
    static int data[100001], pos[100001];
    int n, k;
    cin>>n>>k;

    for (int i=0; i!=n; ++i)
    {
        cin>>data[i];
        pos[data[i]]=i;
    }

    answer(data, pos, n, k);
    for (int i=0; i!=n; ++i) cout<<data[i]<<' ';
    return 0;
}
