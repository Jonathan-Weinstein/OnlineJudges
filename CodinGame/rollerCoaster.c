#include <stdio.h>
#include <stddef.h>

enum{MaxParties=1000};

//a party size is always <= seat capacity. important?

int main(void)
{
    int members_in_party[MaxParties];

    int total_seats, runs, parties;
    scanf("%d%d%d", &total_seats, &runs, &parties);

    if (parties<=0 || parties>MaxParties)
        return 1;

    int sum_of_all=0;

    for (int i=0; i!=parties; ++i)
    {
        scanf("%d", members_in_party+i);
        sum_of_all += members_in_party[i];
    }

    if (sum_of_all <= total_seats)
    {
        printf("%lu\n", (unsigned long)sum_of_all * (unsigned long)runs);
        return 0;
    }

    int sum_at[MaxParties];
    short jump_to[MaxParties];

    int csum=0;
    int i=0;
    int e=0;
    int val=members_in_party[e];

    for (;;)
    {
        //val alwasy <= total seats
        if (csum+val <= total_seats)
        {
            csum += val;

            if (++e==parties)//can only happen once
                e = 0;

            val = members_in_party[e];
        }
        else
        {
            sum_at[i] = csum;
            jump_to[i] = e;
            csum -= members_in_party[i];

            if (++i==parties)
                break;
        }
    }

    unsigned long answer=0ul;
    unsigned pos=0u;

    while (runs--)
    {
        answer += sum_at[pos];
        pos=jump_to[pos];
    }

    printf("%lu\n", answer);
    return 0;
}

