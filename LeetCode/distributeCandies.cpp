#include <unordered_set>

//count the distinct numbers, and return it or n/2 if it exceeds n/2
//can use less memory if sort numbers in-place, than walk counting kinds
//range of possible values a consideration
int solve(const int *a, unsigned n)
{
    std::unordered_set<int> kinds;

    for (unsigned i=0u; i!=n; ++i)
        kinds.insert(a[i]);//does nothing if already in set

    unsigned res = kinds.size(), half = n/2u;
    if (res>half) res = half;
    return res;
}

class Solution {
public:
    int distributeCandies(vector<int>& candies) {
        return solve(candies.data(), candies.size());
    }
};
