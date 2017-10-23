/* Largest Rectangle https://www.hackerrank.com/challenges/largest-rectangle
There are N buildings in a certain two-dimensional landscape. Each building has some height in meters.
Buildings can be joined to form rectangles. Buildings are all 1 meter in width.

>>> Given N buildings, find the greatest rectangular area that can be formed.

Input Format:
The first line contains N, the number of buildings altogether.
The second line contains N space-separated integers, each representing the height of a building.

Constraints:
1<=N<=1e5
1<= any height <=1e6

Output Format:
One integer representing the maximum area of rectangle formed.

Sample Input:
5
1 2 3 4 5

Sample Output:
9

Explanation:
let X=position, H=height.

X | H |
0   1   *
1   2   **
2   3   @@@
3   4   @@@*
4   5   @@@**

The largest rectangle is 3 meters by 3 meters = 9 square meters.
*/
#include <stdint.h>

#include <iostream>
using namespace std;

typedef uint64_t u64;

struct building
{
    unsigned h, x;
};

building* cut(building* top, unsigned h, unsigned i, u64* maxptr)//h is incoming building data
{
    u64 m=*maxptr;

    do{
        const u64 area = u64(top->h)*u64(i-top->x);
        if (area>m)
            m=area;
    }while( h < (--top)->h );//sentinel at beginning

    (++top)->h=h;//new top x takes on x value of what its replacing, due to buildings on the left being higher
    *maxptr=m;
    return top;
}

u64 finish(const building* sentinel, const building* top, unsigned n, u64 maxArea)
{
    for ( ; top!=sentinel; --top)
    {
        const u64 a = u64(top->h)*u64(n-top->x);
        if (a>maxArea)
            maxArea=a;
    }

    return maxArea;
}

int main()
{
    static building stack[100001];
    building* top=stack;//convention here is not one past the end
    u64 maxArea=0uL;
    unsigned n;

    stack->h=0u;//sentinel in cut loop, and triggers first push
    cin>>n;

    for (unsigned i=0u; i!=n; ++i)
    {
        unsigned h;
        cin>>h;

        if (h >= top->h)
            *++top={h, i};
        else
            top=cut(top, h, i, &maxArea);
    }

    cout<<finish(stack, top, n, maxArea)<<'\n';
    return 0;
}
