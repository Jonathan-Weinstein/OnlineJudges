#include <stdio.h>
#include <stdlib.h>
//Some conversions back and forth between ascii and integer could be removed
//or done more efficiently, as well as tring lengths.
int main(void)
{
    char buf[11]="13.09.0000";//buf[10] is '\0'
    fgets(buf+6, 5, stdin);//reads no more than 5-1
    const unsigned year=atoi(buf+6);

    if (year<1918u)
    {
        if (year%4u == 0u)
            buf[1]='2';
    }
    else if (year!=1918)
    {
        if (year%400u == 0u || (year%100u != 0u && year%4u == 0u))
            buf[1]='2';
    }
    else
    {
        buf[0]='2';
        buf[1]='6';
    }

    puts(buf);
    return 0;
}
