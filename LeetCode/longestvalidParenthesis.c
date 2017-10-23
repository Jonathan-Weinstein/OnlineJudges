static inline
void maxmov(unsigned *p, unsigned src)
{
    if (*p < src) *p = src;
}

typedef const char *iter;

static inline
unsigned solve(iter it)
{
    iter const start=it;
    int lvl=0;
    unsigned fwdMax=0u, run=0u;
    char ch;

    while ((ch=*it++) != '\0')
    {
        ++run;

        if (ch==')')
        {
            if (--lvl == 0)//case something like )()(
            {
                maxmov(&fwdMax, run);
            }
            else if (lvl < 0)
            {
                maxmov(&fwdMax, run-1u);
                run=0;
                lvl=0;
            }
        }
        else
            lvl += (ch=='(');

    }

    if (lvl==0)
        maxmov(&fwdMax, run);

    unsigned bkwdMax=0u;
    run=0u;
    lvl=0;
    --it;//now points to '\0'

    while (it!=start)
    {
        ch = *--it;
        //rest of loop body similar, but with '(', ')' fwd and bkwd maxes switched
        ++run;
        if (ch=='(')
        {
            if (--lvl == 0)
            {
                maxmov(&bkwdMax, run);
            }
            else if (lvl < 0)
            {
                maxmov(&bkwdMax, run-1u);
                run=0;
                lvl=0;
            }
        }
        else
            lvl += (ch==')');
    }

    if (lvl==0)
        maxmov(&bkwdMax, run);

    return fwdMax>bkwdMax ? fwdMax : bkwdMax;
}

int longestValidParentheses(char* s) {
    return solve(s);
}

#if 0
#include <stdio.h>
// )()(((())))(
// should be ten
int main(int argc, char **argv)
{
    (void)argc;
    const char *s;
    while ((s=*++argv)!=NULL)
        printf("%d\n", solve(s));

    return 0;
}
#endif
