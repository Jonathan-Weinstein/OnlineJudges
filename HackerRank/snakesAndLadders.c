#include <stdio.h>
#include <string.h>//memset
#include <limits.h>
typedef unsigned char byte;
enum{start=1, step=6, finish=100, N=101};

int bfs(const byte* jump_from, byte* distance_to, byte* first)
{
    byte *last=first+1;
    byte currIdx=0, nextDist;

    *first=start;
    distance_to[start]=0;

    do
    {
        currIdx = *first++;//get front of queue and bump
        nextDist=distance_to[currIdx]+1;

        if (currIdx+step>=finish) break;//if in immediate reach

        for (int i=1; i<=step; ++i)
        {
            int x = currIdx+i;//next index
            if (jump_from[x]) x=jump_from[x];

            if (distance_to[x]==UCHAR_MAX)//if not visited
            {
                distance_to[x]=nextDist;
                *last++ = x;//append to queue
            }
        }
    }
    while (first!=last);//queue not empty

    if (currIdx+step>=finish) return currIdx==finish ? nextDist-1 : nextDist;
    else return -1;
}

void input(byte* jump_from)
{
    int reps=2;//snakes and ladders can be treated as the same

    do
    {
        int lines;
        scanf("%d", &lines);

        while (lines--)
        {
            unsigned src, dest;
            scanf("%u%u", &src, &dest);

            jump_from[src]=dest;
        }
    }
    while (--reps);
}

int main()
{
    byte jump_from[N];
    byte distance_to[N];
    byte q[N];
    int tests;
    scanf("%d", &tests);

    while (tests--)
    {
        memset(jump_from, 0, sizeof jump_from);
        memset(distance_to, ~0, sizeof distance_to);
        input(jump_from);
        printf("%d\n", bfs(jump_from, distance_to, q));
    }

    return 0;
}
