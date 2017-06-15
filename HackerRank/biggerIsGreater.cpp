#include <iostream>
#include <utility>
using namespace std;

/*  To get the next lexicographically greater sequence that is as small as possible,
    we need to keep the elements in the beginning the same for as long as possible, until we must increase an element.
    Then we need to increase the value of said element by swapping it with something just big enough to the right of it.
    Then the elements to the right of the promoted element must be sorted, which can be done by a reverse.

    If the array is already sorted in reverse, there is no greater sequence, and we return false.
*/
bool permute(char *inc)//inc=end-1, also sentinel placed at begin[-1]. only arrays of length>1 actual values are passed
{
    char *j=inc, *promoter=inc;

    do --j; while (*j >= j[1]);//walk until no longer increasing from right, {...3, 7, 5, 4} would stop at 3

    if (*j == '\0') return false;//planted sentinel value smaller than all possible values, array is sorted descending
    //can do binary search here
    while (*j >= *promoter) --promoter;//get first from right that is greater, this is also the least greater

    swap(*j, *promoter);//array to right of j will still be descending, before swap: promoter[1]<*j (second loop). Also: promoter[-1]>=*j, b/c if not, would have found j to be there (first loop)
    for (++j; j<inc; ++j, --inc) swap(*j, *inc);//can sort the right side by reversing
    return true;
}

enum{MaxLen=100};

int main()//standard IO options in C/C++ aren't the best
{
    char base[MaxLen+2], *const first=base+1;
    *base='\0';

    int t;
    cin>>t;
    cin.ignore(0xffff, '\n');

    while (t--)
    {
        streamsize len=cin.getline(first, MaxLen+1).gcount();
        if (!cin.eof()) --len;//don't count the '\n' if there is one...

        if (len>1 && permute(base+len))
            cout.write(first, len).put('\n');
        else
            cout<<"no answer\n";
    }

    return 0;
}
