/*
    The following functions for dividing by a run-time invariant divisor
    were adapted from the methods described by:
        T. Granlund and P. L. Montgomery: Division by Invariant Integers Using Multiplication,
        Proceedings of the SIGPLAN 1994 Conference on Programming Language Design and Implementation.
        http://citeseerx.ist.psu.edu/viewdoc/summary?doi=10.1.1.1.2556
    Agner Fogs file divfixedi32.asm in his asmlib subroutine library was referenced as well
    http://www.agner.org/optimize/#asmlib
*/
#include <stdint.h>

inline
int bsr(uint32_t u)
{
    return __builtin_clz(u)^31;//same as 31-clz but gcc will produce bad code.
}                              //doesn't optimize 31-(bsr^31) to just bsr

struct udivisor32_t
{
    uint32_t m;
    uint32_t l;//need 6 bits, always <= 32
};

inline
udivisor32_t udivisor32(uint32_t d)
{
    udivisor32_t ret;

    if (d>1u)//can skip this if know all will be above 1 before hand
    {
        ret.l = bsr(d-1u);//one less than ciel(lg2(d)), no rush to add one now, 1<<32 is undefined, so do 2<<(L-1)
        ret.m = uint32_t((uint64_t(2u<<ret.l)<<32u)/d) + 1u;
        ++ret.l;
    }
    else
        ret={};//quot = n = (n+0)>>0

    return ret;
}

inline
uint32_t divide(uint32_t n, udivisor32_t d)
{
    const uint32_t t = (uint64_t(n)*d.m) >> 32u;//take upper 32-bits of 64-bit product
    return uint32_t((uint64_t(n)+t)>>d.l);
}

/*
    HackerRank Lisa's Workbook
    https://www.hackerrank.com/challenges/lisa-workbook
    Solution by Jonathan Weinstein(HackerRank: @splice)
    last updated January 3, 2017
    see below main for an explanation
*/
#include <stdio.h>

unsigned lisas_wrokbook(unsigned chapters, const unsigned K)//K is chapter problem capacity
{                                                   //a page is filled to this before starting a new page,
    unsigned page=1u, needed=1u, specs=0u, x;       //unless the chapter does not have enough to fill its last

    if (K==1u)//in this case, can only be the number of problems in first chapter
    {
        scanf("%u", &x); //get the first and return,
        return x;        //if there were multiple test cases would have to do some ignoring.
    }

    const udivisor32_t divK=udivisor32(K), divKm1=udivisor32(K-1u);

    while (chapters--)
    {
        scanf("%u", &x);//current chapter problem count

        if (x>=needed)
        {
            ++specs;//rhs below is needed%K == 0
            if (x!=needed && needed == K*divide(needed, divK))  //if the min needed is just before a new page,
                ++specs;                    //and we have at least one problem to wrap there.
        }

        page += divide(x-1u, divK) + 1u;//start page of next chapter
        needed = page<=K ? page : page + divide(page-K-1u, divKm1) + 1u;
    }

    return specs;
}

int main()
{
    unsigned n, k;
    scanf("%u%u", &n, &k);//all values >= 1
    printf("%u\n", lisas_wrokbook(n, k));
    return 0;
}

/*
    Here is an efficient solution without any nested looping(though it trades them for two divisions).
    The strategy is to calculate the minimum problem count a chapter starting at a page must have for it to
    contain a special problem.
    I managed to figure this out myself with a pen and paper, and I haven't seen a solution like this
    online, so I'm happy about it. I'm afraid I'm not able to give a proper proof as of now, however.
    Here is an example where K(page capacity)=4:
adjust  page    needed
        1       1//the "header"
        2       2
        3       3
        4       4
0       5       6//group 0
1       6       7
2       7       8
3       8      10//group 1
4       9      11
5       10     12
6       11     14//group 2
7       12     15
8       13     16
9       14     18//group 3
10      15     19
11      16     20
    So, the min needed problems a chapter needs to have, starting at page "pg",
    to get at least one special is:
        pg; for pg<=K
        or:
        pg + (zero-based group index) + 1; for pg>K
    Once the current page passes K, the groups are in sizes of K-1.
    Getting the zero-based group index can be done by dividing, but first
    the "header" offset needs to be subtracted so the numbers inside them start from zero.
    Since the first group will start at page K+1, subtract this first.
    If K=1(each chapter has exactly one problem), then the special count is the number in the first
    chapter. After the first chapter, where the problem numbers reset,
    its impossible for a problem number to catch up to a page number, since they grow at the same rate.
*/
