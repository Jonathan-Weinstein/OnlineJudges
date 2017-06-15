```C++
int main()
{
    unsigned rcnt[100]={};
    unsigned n, k;//1<=k<=100, values of any number a%k are in [0,99]
    scanf("%u%u", &n, &k);

    while (n--)//rcnt[i] will hold the count of numbers with remainder i when divided by k after this loop
    {
        unsigned a;
        scanf("%u", &a);
        ++rcnt[a%k];
    }
    
    unsigned pairs = nc2(rcnt[0]);//nc2 stands for n choose 2, defined as (n*(n-1))/2
    
    for (size_t lo=1, hi=k-1; lo<hi; ++lo, --hi)
        pairs += rcnt[lo]*rcnt[hi];

    if (even(k))
        pairs += nc2(rcnt[k/2]);

    printf("%u\n", pairs);
    return 0;
}
```