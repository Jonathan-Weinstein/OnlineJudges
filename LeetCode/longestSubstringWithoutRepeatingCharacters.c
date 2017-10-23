#include <limits.h>
#include <stddef.h>

static inline int maxint(int a, int b){return a>b ? a : b;}

int lengthOfLongestSubstring(const char *const s)
{
    int pastLastIdx[UCHAR_MAX]={0};
    int len=0, b=0, e=0;
    size_t ch;

    for (; (ch=s[e])!='\0'; ++e)
    {
        if (b < pastLastIdx[ch])
        {
            len=maxint(len, e-b);
            b=pastLastIdx[ch];
        }

        pastLastIdx[ch]=e+1;
    }

    return maxint(len, e-b);
}
