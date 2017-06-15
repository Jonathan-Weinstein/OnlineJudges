/* Divisible Sum Pairs https://www.hackerrank.com/challenges/divisible-sum-pairs

You are given an array of n integers, { a[0], a[1], ...a[n-1] } and a positive integer, k.
Find and print the number of (i,j) pairs where i<j and a[i]+a[j] is evenly divisible by k.

Input Format:
The first line contains 2 space-separated integers, n and k, respectively.
The second line contains n space-separated integers describing the respective values of the array.

Constraints:
2<=n<=100
1<=k<=100
1<=a[i]<=100

Output Format:
Print the number of (i,j) pairs where i<j and a[i]+a[j] is evenly divisible by k.

Sample Input:
6 3
1 3 2 6 1 2

Sample Output:
5

*/

/**
 * This is doable in O(n) time, instead of O(n*n) as done in the editorial.
 *
 * This is also very similar to the "Non-Divisible Subset" problem I posted as well.
 *
**/
#include <stdio.h>

unsigned nc2(unsigned n)//n choose 2
{
    return (n*(n-1u))>>1u;//multiply before dividing so always even number
}

int main()
{
    unsigned rcnt[100]={}, n, k;//1<=k<=100, values of any number a%k are in [0,99]
    scanf("%u%u", &n, &k);

    while (n--)//rcnt[i] will hold the count of numbers with remainder i when divided by k after this loop
    {
        unsigned a;
        scanf("%u", &a);
        ++rcnt[a%k];
    }

    unsigned total = nc2(rcnt[0]);

    for (int lo=1, hi=k-1; lo<hi; ++lo, --hi)
        total += rcnt[lo]*rcnt[hi];

    if (!(k&1u))//if k is even
        total+=nc2(rcnt[k>>1u]);

    printf("%u\n", total);
    return 0;
}
