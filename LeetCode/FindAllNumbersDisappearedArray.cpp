
enum:int32_t{SB = int32_t(1LL << 31) };

class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int32_t>& nums)
    {
        int *const a= nums.data();
        unsigned const n = nums.size();

        for (unsigned i=0; i!=n; ++i)
            a[(a[i]-1) &~ SB] |= SB;

        vector<int> r;

        for (unsigned i=0; i!=n; ++i)
        {
            if (a[i]>=0)
                r.push_back(i+1);
        }

        return r;
    }
};
