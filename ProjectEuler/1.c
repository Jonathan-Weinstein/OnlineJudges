#include <stdio.h>

// (n-1u)/d == how many multiples of d are BELOW n and ABOVE zero
// ignoring zero wont affect our some though.

//inclusive arithemtic series sum [1, n]
unsigned asum_inclusive(unsigned n)
{
    return (n*(n+1u))/2u;
}
//sum of divisibles below
unsigned sdb(unsigned n, unsigned d)
{
    return d*asum_inclusive((n-1u)/d);
}

//we only want to sum multiple of both 3 and 5 (multiples of 15)
//once, each of the first TWO sdb's will consider these, so
//subtract sdb(1000, 15) ONCE

int main()
{
    printf("%u\n", sdb(1000, 3) + sdb(1000, 5)  - sdb(1000, 15));
}
