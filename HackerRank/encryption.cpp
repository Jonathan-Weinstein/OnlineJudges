#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int main()
{
    string s;
    getline(cin, s);

    const int len = s.size(), cols = ceil(sqrt(len));   //At least one of rows or cols must be the ceiling,
                                                        //and from prob description, rows<=cols.
    for (int j=0; j!=cols; ++j, cout.put(' '))
        for (int pos=j; pos<len; pos+=cols)// < over != important for when length not perfect square
            cout.put(s[pos]);

    return 0;
}
