#include <iostream>
using namespace std;
#include <ctype.h>

enum{N=200, MaxLine=30*27};//Max text len, (max width)*(num chars)

int main()
{
    char line[MaxLine+1];
    char word[N+1];
    int w, h;//width, height

    cin>>w>>h;
    cin.ignore(0x7fff, '\n').getline(word, N+1);

    char *const questionMark=line+(w*26);

    while (h--)
    {
        cin.getline(line, MaxLine+1);

        for (const char *it=word; *it!='\0'; ++it)
        {
            const unsigned i = unsigned(toupper(*it)) - 'A';

            cout.write(i<26u ? line+(i*w) : questionMark, w);
        }

        cout.put('\n');
    }

    return 0;
}
