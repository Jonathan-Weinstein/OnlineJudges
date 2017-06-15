/* Richie Rich https://www.hackerrank.com/challenges/richie-rich

*/
#include <stdio.h>

bool foo(char *left, int n, int k)
{
    if (!n) return true;
    const int odd=n&1;
    char *right=left+n-1;
    //first see if its possible
    for (const char *i=left, *j=right; i<j; ++i, --j)
        if (*i!=*j)//have to make at least one change
            --k;

    if (k<0) return false;

    for ( ; left<right; ++left, --right)
    {
        if (*left!='9' && *right!='9')//if exactly 1 is nine, already decremented k in first loop
        {
            if (*left==*right)//not counted at all in first loop
            {
                if (k>=2) k-=2;
                else break;
            }
            else//noted at least one change in first loop, need one more to maximize
            {
                if (k >= 1) --k;
                else break;
            }
        }

        *left=*right='9';
    }

    for ( ; left<right; ++left, --right)
        if (*left>*right)   *right = *left;
        else                *left  = *right;

    if (odd==1 && k!=0) *left='9';

    return true;
}

enum{N=100000};//woops

int main()
{
    static char buf[N];
    int n, k;

    scanf("%d%d ", &n, &k);
    fread(buf, 1, n, stdin);

    if (foo(buf, n, k))
        fwrite(buf, 1, n, stdout);
    else
        fwrite("-1", 1, 2, stdout);

    return 0;
}
