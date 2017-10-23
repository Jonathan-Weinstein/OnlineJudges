/*
    HackerRank Lisa's Workbook
    https://www.hackerrank.com/challenges/lisa-workbook
    Solution by Jonathan Weinstein(HackerRank: @splice)
    last updated June 18, 2017
    see below main for an explanation
*/
#include <stdio.h>

inline
unsigned groups(unsigned n, unsigned d)//n!=0
{
    return (n-1u)/d + 1u;
}

//k is chapter problem capacity
//a page is filled to this before starting a new page,
//unless the chapter does not have enough to fill its last
unsigned LisasWorkbook(unsigned chapters, unsigned const k)
{
    unsigned probs;

    if (k>1u)//in this case, can only be the number of problems in first chapter
    {
        unsigned specs=0u, pg=1u, needed=1u;

        while (chapters--)
        {
            scanf("%u", &probs);//current chapter problem count

            if (probs>=needed)
            {
                ++specs;//rhs below is needed%k == 0
                if (probs>needed && needed%k == 0u) //if the min needed is just before a new page,
                    ++specs;                    //and we have at least one problem to wrap there.
            }

            pg += groups(probs, k);//start page of next chapter
            needed = pg<=k ? pg : pg + (pg-(k+1u))/(k-1u) + 1u;
            //could pull the above out and have 2 sequential loops,
            //but for brevity
        }

        return specs;
    }
    else
    {
        scanf("%u", &probs);//get the first and return,
        return probs;       //if there were multiple test cases would have to do some input ignoring.
    }
}

int main(void)
{
    unsigned n, k;
    scanf("%u%u", &n, &k);//all values >= 1
    printf("%u\n", LisasWorkbook(n, k));
    return 0;
}

/*
    Here is solution a came up with myself that doesn't loop a lot.
    There are divisions, but they are by run-time invariants and could be optimized
    in a method described in:

        T. Granlund and P. L. Montgomery: Division by Invariant Integers Using Multiplication,
        Proceedings of the SIGPLAN 1994 Conference on Programming Language Design and Implementation.
        http://citeseerx.ist.psu.edu/viewdoc/summary?doi=10.1.1.1.2556

    Also, all numbers in the original problem are constricted in [1, 100].

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
        else:
        pg + (zero-based group index) + 1; for pg>K
    Once the current page passes K, the groups are in sizes of K-1.
    Getting the zero-based group index can be done by dividing, but first
    the "header" offset needs to be subtracted so the numbers inside them start from zero.
    Since the first group will start at page K+1, subtract this first.
    If K=1(each chapter has exactly one problem), then the special count is the number in the first
    chapter. After the first chapter, where the problem numbers reset,
    its impossible for a problem number to catch up to a page number, since they grow at the same rate.
*/
