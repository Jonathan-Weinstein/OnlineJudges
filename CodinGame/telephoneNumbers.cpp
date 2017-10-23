#include <vector>

#include <stdio.h>

//simple but big waste of memory,
//though reduce some by not treating zero-terminator as digit

struct node
{
    unsigned eow_bf;//less memory waste for storing last digit
    unsigned index[10];
};

struct trie
{
    std::vector<node> pool;

    trie() : pool(1) {}

    int add(const char *str)
    {
        unsigned accum=0u;
        unsigned curch, nextch;
        unsigned i=0u;

        curch = *str++ - '0';

        if (curch>=10u)
            return 0u;
        //process all but last digit
        for (; (nextch=*str++ - '0') < 10u; curch=nextch)
        {
            if (pool[i].index[curch]==0u)
            {
                unsigned inext=pool.size();
                pool[i].index[curch]=inext;
                accum += ((pool[i].eow_bf >> curch) & 1u) ^ 1u;
                pool.emplace_back();
                i = inext;
                //rest of digits will go to this path,
                //pull out?
            }
            else
                i = pool[i].index[curch];
        }
        //handle last digit
        if (!(pool[i].eow_bf & 1u<<curch))//else will add one more for equal keys
        {
            pool[i].eow_bf |= 1u<<curch;
            accum += (pool[i].index[curch]==0u);
        }

        return accum;
    }
};

int main()
{
    int entries=0;
    char buffer[64];
    scanf("%d ", &entries);

    trie t;
    unsigned answer=0u;

    while (entries-- > 0)
    {
        fgets(buffer, 64, stdin);
        answer += t.add(buffer);
    }

    printf("%u\n", answer);
    return 0;
}
/*

Game Input
Input

Line 1: The number N of telephone numbers.

N following lines: Each line contains a phone number, with a maximum length L.
Telephone numbers consist of only the digits 0 to 9 included, without any spaces.
Output
The number of elements (referencing a number) stored in the structure.
Constraints
0 <= N <= 10000
2 <= L <= 20
Examples
Input

1
0467123456

Output

10

Input

2
0123456789
1123456789

Output

20

Input

2
0123456789
0123

Output

10

Input

5
0412578440
0412199803
0468892011
112
15

Output

28


*/
