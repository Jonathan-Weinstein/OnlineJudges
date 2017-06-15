/*
    HackerRank 'Candies' challenge
    https://www.hackerrank.com/challenges/candies

    Alice is a kindergarden teacher. She wants to give some candies to the children in her class.
    All the children sit in a line (their positions are fixed),
    and each of them has a rating score according to his or her performance in the class.
    Alice wants to give at least 1 candy to each child. If two children sit next to each other,
    then the one with the higher rating must get more candies. Alice wants to save money,
    so she needs to minimize the total number of candies given to the children.

    Input Format:
    The first line of the input is an integer N, the number of children in Alice's class.
    Each of the following N lines contains an integer that indicates the rating of each child.

    1 <= N <= 10e5
    1 <= rating[i] <= 10e5

    Output Format:
    Output a single line containing the minimum number of candies Alice must buy.

    Sample Input:
    3
    1
    2
    2

    Sample Output:
    4

    Explanation:
    Here 1, 2, 2 is the rating. Note that when two children have equal rating, they are allowed to have different number of candies.
    Hence optimal distribution will be 1, 2, 1.
*/

/*
    This is a nice solution I wrote. It traverses the input once, is online, and does not require extra space.

    Jonathan Weinstein, May 6, 2016.
*/

#include <stdio.h>

static inline
unsigned min(unsigned a, unsigned b)
{
    return a<b ? a : b;
}

static inline
unsigned long sum(unsigned long n)//sum of numbers [1,n]
{
    return (n*(n+1u))>>1u;
}

//((n+1u)>>1u)*(n|1u);

void candies()
{
    int n=0;
    scanf("%d", &n);

    if (n>1)
    {
        unsigned long total=1uL;
        unsigned fall=1u, rise=1u, prev, next;
        scanf("%u", &next);
        --n;

        /************************************************/
        for ( ; ; fall=1u)
        {
            for ( ; ; ++fall)//see if we are descending and for how long
            {
                prev=next;
                scanf("%u", &next);
                if ( (--n==0) | (next>=prev) )//may not get last increment checking both at same time like this, fixed outside
                    break;
            }

            if (n==0)
                break;

            if (fall!=1u)//if we went down at all
            {
                total += sum(fall) - min(fall, rise);
                rise=1u;
            }
            //tack on 1 or more candies due to kid on right
            if (next==prev)
            {
                ++total;
                rise=1u;
            }
            else//going up
                total += ++rise;
        }
        /************************************************/
        if (prev>next)
            total += sum(fall+1u) - min(fall+1u, rise);
        else
        {
            total += sum(fall) - min(fall, rise);
            if (next==prev) ++total;
            else if (fall!=1u) total+=2u;
            else total+=rise+1u;
        }

        printf("%lu\n", total);
    }
    else
        puts(n==1 ? "1" : "0");
}

int main(int argc, char* argv[])
{
    if (argc==2)
    {
        if (freopen(argv[1], "r", stdin))
        {
            candies();
            fclose(stdin);
            return 0;
        }
        else
        {
            perror("freopen");
            return 1;
        }
    }

    candies();
    return 0;
}
