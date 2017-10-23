/*
    'Greedy Florist' https://www.hackerrank.com/challenges/greedy-florist

    A group of k people want to buy flowers. Each flower has some cost.
    The florist is greedy and wants to maximize his number of new customers,
    so he increases the sale price of flowers for repeat customers;
    more precisely, the price to purchase another is (m+1)*p,
    where m is the number of flowers a particular customer has bought, and p is the regular price of the flower.

    Goal:
    Find and print the minimum cost for your group of k to purchase n flowers.
    You can purchase the flowers in any order.

    Input Format:
    The first line contains two integers, n (number of flowers to purchase) and k (the size of your group of friends,
    including you).
    The second line contains n space-separated positive integers describing the cost for each flower.

    Output Format:
    Print the minimum cost for buying flowers.

    Sample Input 0:
    3 3
    2 5 6

    Sample Output 0:
    13

    Sample Input 1:
    3 2
    2 5 6

    Sample Output 1:
    15

    Explanation

    Sample Case 0:
    There are 3 flowers and 3 people in your group. Each person buys one flower and the sum of prices paid is 13.

    Sample Case 1:
    There are 3 flowers and 2 people in your group. You want to buy the most expensive ones first, so one group member buys
    the one of price 6 and the other of price 5. Then one of them will have to purchase the last flower, at a price (1+1)*2,
    for a grand total of 15.
*/

#include <iostream>
#include <algorithm>//sort
#include <numeric>//accumulate
using namespace std;

//array is already sorted in descending format, n number of flowers, k people in group
int answer(const int* b, const int* e, size_t n, size_t k)//e-b == n, but already calc'd it
{
    int total=0, multiplier=1;

    for (size_t trips=n/k; trips--; b+=k, ++multiplier)
        total += multiplier*accumulate(b, b+k, 0);//could store b+k

    return total + multiplier*accumulate(b, e, 0);//clean up any remaining if n not evenly divisible by k
}

int main()
{
    size_t n, k;//n number of flowers, k people in group
    cin>>n>>k;
    //get space for the input, read it all, and sort it descending
    int *const buf=new int[n], *const e=buf+n;
    for (int *b=buf; b!=e; ++b) cin>>*b;
    sort(buf, e, [](int a, int b){return a>b;});

    cout<<answer(buf, e, n, k)<<'\n';

    delete[]buf;//could have used unique_ptr
    return 0;
}
