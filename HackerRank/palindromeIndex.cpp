#include <iostream>
#include <string>
using namespace std;
typedef string::const_iterator iter;

bool ispalin_inc(iter f, iter r)
{
    while (f<r && *f==*r)
        ++f, --r;

    return f>=r;
}

int answer_inclusive(iter f, iter r)
{
    iter const base=f;

    while(f<r && *f==*r)
        ++f, --r;

    if (f>=r)
        return -1;//if already a palindrome return this also
    else if (f[1]==*r && ispalin_inc(f+1, r))
        return f-base;
    else if (*f==r[-1] && ispalin_inc(f, r-1))
        return r-base;
    else
        return -1;//can't be made a palindrome by removing at most 1 character
}

int main()
{
    int t;
    string s;

    cin>>t;
    s.reserve(512);

    while (t--)
    {
        cin>>s;

        if (s.empty())
            cout<<"-1\n";
        else
            cout<<answer_inclusive(s.cbegin(), s.cend()-1)<<'\n';
    }

    return 0;
}
