/*
    Washing Plates
    https://www.hackerrank.com/contests/101hack41/challenges/washing-plates/problem

    solution by Jonathan Weinstein, last updated June 22, 2017

    Problem:
    There are N dirty dishes, but Bob only has time to wash K of them.
    Each dish has 2 values associated with them, P and D.
    P is how much money Bob will earn for washing the dish.
    D is how much money Bob will be deducted for not washing the dish.

    Question:
    >>> If Bob can only wash at most K dishes, whats the most he can earn?
        If this value is negative, print 0

    Input format:
    First line has N followed by K.
    The following N lines hold P and D for a dish.
*/
#include <cstdint>
#include <iostream>
#include <algorithm>//nth_element
#include <numeric>//accumulate
using namespace std;

//max value of any P or D is 10**9, twice this can fit in an i32,
//but accumlating many needs a wider type
typedef uint_least32_t ucost_t;
typedef int_fast64_t iaccum_t;

auto const above=[](ucost_t a, ucost_t b){return a>b;};

int main()
{
    unsigned n=0u, k=0u;
    cin>>n>>k;

    if (n>k)
    {
        ucost_t *const buf=new ucost_t[n];
        ucost_t *const past=buf+n;
        iaccum_t net=0;

        for (ucost_t *it=buf; it!=past; ++it)
        {
            ucost_t pay, deduct;
            cin>>pay>>deduct;
            *it = pay + deduct;
            net += deduct;//would lose all of this if wash none. minimize storage
        }

        ucost_t *const kth=buf+k;
        nth_element(buf, kth, past, above);
        net = accumulate(buf, kth, -net);//add on p values and undo d values
        delete[]buf;

        if (net>0)  cout<<net<<'\n';
        else        cout<<"0\n";
    }
    else//can wash everything
    {
        iaccum_t sum=0;
        ucost_t pay, deduct;//don't have to process deduct value, just ignore it. Something like scanf("*u");
        while (n--) cin>>pay>>deduct, sum+=pay;
        cout<<sum<<'\n';
    }

    return 0;
}
