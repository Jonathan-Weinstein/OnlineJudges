/*
    'Stock Maximize' https://www.hackerrank.com/challenges/stockmax

    Your algorithms have become so good at predicting the market that you now know what the
    share price of Wooden Orange Toothpicks Inc. (WOT) will be for the next N days.

    Each day, you can either buy one share of WOT, sell any number of shares of WOT that you own,
    or not make any transaction at all. What is the maximum profit you can obtain with an optimum trading strategy?

    Input:
    The first line contains the number of test cases T. T test cases follow:
    The first line of each test case contains a number N. The next line contains N integers,
    denoting the predicted price of WOT shares for the next N days.

    Output:
    Output T lines, containing the maximum profit which can be obtained for the corresponding test case.

    Constraints:
    1 <= T <= 10
    1 <= N <= 50000
    All share prices are between 1 and 100000

    Sample Input:
    3
    3
    5 3 2
    3
    1 2 100
    4
    1 3 1 2

    Sample Output:
    0
    197
    3

    Explanation:
    For the first case, you cannot obtain any profit because the share price never rises.
    For the second case, you can buy one share on the first two days, and sell both of them on the third day.
    For the third case, you can buy one share on day 1, sell one on day 2, buy one share on day 3, and sell one share on day 4.
*/
#include <stdio.h>
#include <limits.h>

unsigned answer(unsigned* sentinel, const unsigned* r)//r iterates in reverse and is inclusive, sentinel is 1 index before the actual data
{
    for (unsigned profit=0u, peak=*r; ; )
    {
        for (*sentinel=0u; *r>=peak; peak = *r--);//another constraint is that none of the data is zero

        if (*r==0u) return profit;

        *sentinel = UINT_MAX;
        unsigned sum=*r;
        const unsigned* const save=r;//to compute the count without doing extra work in the next loop

        for (--r; *r<peak; sum += *r--);

        profit += (save-r)*peak - sum;
    }
}

int main()
{
    static unsigned buf[50001];//within size constraint
    unsigned* const begin=buf+1;//for a sentinel value before the beginning of the actual data
    int t;
    scanf("%d", &t);

    while (t--)
    {
        int n;
        scanf("%d", &n);
        unsigned* const end=begin+n;

        for (unsigned* f=begin; f!=end; ++f) scanf("%u", f);

        printf("%u\n", answer(begin-1, end-1));
    }

    return 0;
}

/**
 * After I solved this challenge with the above solution, I looked in the discussion section
 * and saw the following solution posted by user DaleSeo, which looks very clean.
 * I was sort of bummed that I hadn't realized it on my first try, but both our
 * solutions are very similar, and my solution has merit: it is potentially very fast
 * on what could be considered real world data for this type of thing.
 *
 * For example, if the maximum stock value occurs at 30% of the way into the input from the end,
 * then the following loop with few operations will dash through the remaining 70% of the input:
 *
 * for (--r; *r<peak; sum += *r--);
*/
#if 0
public class Solution {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int size = scanner.nextInt();

        for (int i = 0; i < size; i++) {
            int numOfDays = scanner.nextInt();
            int[] prices = new int[numOfDays];
            for (int j = 0; j < numOfDays; j++) {
                prices[j] = scanner.nextInt();
            }
            System.out.println(getMaxProfit(prices));
        }
    }

    public static long getMaxProfit(int[] prices) {
        long profit = 0L;
        int maxSoFar = 0;
        for (int i = prices.length - 1; i > -1 ; i--) {
            if (prices[i] >= maxSoFar) {
                maxSoFar = prices[i];
            }
            profit += maxSoFar - prices[i];
        }
        return profit;
    }

}
#endif // 0
