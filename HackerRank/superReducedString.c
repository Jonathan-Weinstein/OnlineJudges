/*
    Super Reduced String
    https://www.hackerrank.com/challenges/reduced-string

    Here's kind of a neat algorithm like std::remove or std::unique.

    The first is a version with a sentinel planted before the actual data,
    below it is a general-purpose one.
*/
#include <stdio.h>

enum{N=128};
#if 1
char *annihilate_sentinel(char *next)//*next[-1]=='\0', and there is another byte <=' ' at or beyond next[0]
{
    char *beforebegin=next-1, c;

    while ( (c=*next++)>' ' )
    {
        if (*beforebegin!=c)
            *++beforebegin=c;
        else
            --beforebegin;
    }

    return beforebegin+1;//return past
}

int main(void)
{
    char Storage_[N+1], *const begin=Storage_+1, *end;
    Storage_[0]='\0';

    fgets(begin, N, stdin);
    end=annihilate_sentinel(begin);

    if (end!=begin) fwrite(begin, 1, end-begin, stdout);
    else            fputs("Empty String", stdout);

    return 0;
}
#else
char *annihilate_copy(const char *in, char *out)
{
    char *const StackBegin=out, c;//here convention is out is past top, StackBegin-out == stack size

    while ( (c=*in++)>' ' )
    {
        if (out==StackBegin || out[-1]!=c)//stack empty or top != incoming
            *out++ = c;//push
        else
            --out;//pop
    }

    return out;
}

static inline
char *annihilate(char *data)
{
    return annihilate_copy(data, data);//works in-place
}

int main(void)
{
    char data[N], *end;

    fgets(data, N, stdin);
    end=annihilate(data);

    if (end!=data) fwrite(data, 1, end-data, stdout);
    else           fputs("Empty String", stdout);

    return 0;
}
#endif
