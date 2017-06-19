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
    Heres a solution which traverse the input once, is online, and does not require extra space,
    which differs from the solutions I searched online afterwards to compare.


    Jonathan Weinstein last updated June 18, 2016.
*/

#include <stdint.h>
#include <iostream>
using namespace std;

typedef uint_least64_t total_t;

inline
total_t asum(unsigned n)//sum of numbers in [1,n] inclusive
{
    return (n*total_t(n+1))>>1;
}

inline
unsigned umin(unsigned a, unsigned b)
{
    return a<b ? a : b;
}

total_t solve(int n)
{
    total_t total=1;
    unsigned fall=1u, rise=1u, prev=~0u, next;

    if (n-- <= 1)
        return 1;

    cin>>next;//get first kid so have something to compare

    do
    {
        for(fall=1;;)
        {
            prev=next, cin>>next, --n;
            if (prev<=next)
                break;
            ++fall;
            if (n==0)
                goto LEndOnFall;
        }

        if (fall>1)//if we went down at all
        {
            //here rise refers to the previous run
            total += asum(fall) - umin(fall, rise);//dont include overlap twice. 1,2,9,8,5,1: sub 3
            rise=1;                                //rise of 3 overlaps fall of 4
        }
        //tack on 1 or more candies due to kid on right
        if (next==prev)
        {
            ++total;
            rise=1;
        }
        else//going up
            total += ++rise;//the current run
    }while(n);

    return total;
LEndOnFall:
    return total + asum(fall) - umin(fall, rise);//depending on how coded may have to inc fall
}

int main()
{
    int n=0;
    cin>>n;
    if (n>1)
    {
        cout<<solve(n)<<'\n';
        return 0;
    }
    else
        return 1;
}
