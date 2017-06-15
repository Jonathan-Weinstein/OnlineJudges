/*
    'Sherlock and Array'
    https://www.hackerrank.com/challenges/sherlock-and-array

    Problem:
    Given an array of integers, determine if there is an index where the sum of its elements to the right
    and left are same. The sums do not include the element at the index. The sum to the left of the first index
    and to the right of the last index is considered zero. (I assumed that an empty array has no such index, though
    in the problem it doesn't specify and a constraint is that its size is always>=1.)

    Example:
    An array of size n=5 holds 1, 3, 5, 2, 2.
    The sums to the left and right of index 2 (zero-based indexing) are both equal (1+3=2+2).

    The input format first consists of an integer t, the number of test cases.
    Each test case starts with an integer n, the elements in the array, followed by its n integers.
*/
#include <stdio.h>
//optimized this from my previous solution, see below
bool answer(const int* b, const int* e, int right)//right starts as the sum of all elements
{
    if (b==e) return true;

    int left=0;
    right-=*b;
    --e;

    while ( (left!=right)&(b!=e) )
    {
        left  += *b;
        right -= *++b;//made e inclusive
    }

    return left==right;
}

int main()
{
    static int buf[100000];//constraint: array size <= 1e5
    unsigned t;

    scanf("%u", &t);

    while (t--)
    {
        unsigned n;

        scanf("%u", &n);

        int sum=0;
        int* const end=buf+n;

        for (int* b=buf; b!=end; ++b)
        {
            scanf("%d", b);
            sum += *b;
        }

        puts(answer(buf, end, sum) ? "YES" : "NO");
    }

    return 0;
}

#if 0//here is my first submission
#include <stdio.h>

const char* answer(const int* b, const int* const end, int right)//right starts as the sum of all elements
{
    for (int left=0; b!=end; ++b)
    {
        right -= *b;//splitting index is not included in either sum.

        if (left==right)//at this point, b is the partition point, and left and right are their respective sums
            return "YES";

        left  += *b;
    }

    return "NO";
}

int main()
{
    static int buf[100000];//constraint: array size <= 1e5
    unsigned t;

    scanf("%u", &t);

    while (t--)
    {
        unsigned n;

        scanf("%u", &n);

        int sum=0;
        int* const end=buf+n;

        for (int* b=buf; b!=end; ++b)
        {
            scanf("%d", b);
            sum += *b;
        }

        puts(answer(buf, end, sum));
    }

    return 0;
}
#endif
