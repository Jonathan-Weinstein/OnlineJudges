/*
    Solution by Jonathan Weinstein
*/
#include <stdio.h>

int main()
{
    int dx, dy;//delta x, y
    {
        int init;
        scanf("%d%d", &dx, &dy);//destination coordinates
        scanf("%d", &init), dx-=init;
        scanf("%d", &init), dy-=init;
    }

    const char  xc = dx>=0 ? 'E' : (dx=-dx, 'W'),//horizontal
                yc = dy>=0 ? 'S' : (dy=-dy, 'N');//vertical

    int nDiag, nStraight;
    const char diagDir[3]={yc, xc},
                strDir[2]={ dx>dy ? (nDiag=dy, nStraight=dx-dy, xc) : (nDiag=dx, nStraight=dy-dx, yc) };

    while (nDiag--) puts(diagDir);
    while (nStraight--) puts(strDir);

    return 0;
}
