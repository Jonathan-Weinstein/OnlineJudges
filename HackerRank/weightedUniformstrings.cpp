#include <stdint.h>
#include <stdio.h>

enum
{
    MaxLen=100000,//100k
    MaxVal=MaxLen*26//all z's, if sub 1 repeated a's all have zero val
};

void setbit(uint32_t* a, unsigned i)
{
    a[i>>5] |= uint32_t(1)<<(i&31u);
}

bool testbit(const uint32_t* a, unsigned i)
{
    return (a[i>>5] >> (i&31u)) & 1;
}

int main()
{
    static uint32_t bs[((MaxVal+1-1)/32)+1];//zero init'ed

    int ch, last=0, sum=0;
    while ((ch=getchar())>' ')
    {
        if ((ch-='a'-1)==last)
            setbit(bs, sum+=ch);
        else
            setbit(bs, sum=last=ch);
    }

    int queries=0;
    scanf("%d", &queries);
    while (queries-- > 0)
    {
        unsigned val;
        scanf("%u", &val);
        puts(val<=MaxVal && testbit(bs, val) ? "Yes" : "No");
    }

    return 0;
}
