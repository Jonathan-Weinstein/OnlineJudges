#include <string>
using std::string;

//look into std::rotate gcd algo

inline
char* CopyJumpSrcIncDest(const char* src, const char* send, int step, char *dest)
{
	while (src < send) // yeah yeah only allowed 1 past the last
	{
		*dest++ = *src;
		src += step;
	}
	return dest;
}

class Solution
{
public:
	string convert(string s, int numRows)
	{
		if (numRows < 2)
			return s;

		int slen = int(s.size());
		char *const src = const_cast<char *>(s.data());

		string res;
		res.resize(slen);
		char *dest = const_cast<char *>(res.data());

		//dist from going from top of col to last inclusive elem
		int const D = numRows - 1;

		dest = CopyJumpSrcIncDest(src, src + slen, D * 2, dest);

		for (int iRow = 1; iRow != D; ++iRow)//ignore first and last row with 0 stepB and 0 stepA respectively
		{
			int const stepA = (D - iRow) * 2;
			int const stepB = iRow * 2;

			int iRead = iRow;

			for (;;)//could be optimized to check if both steps fit in loop, then check after loop if just stepA fits
			{
				*dest++ = src[iRead];
				iRead += stepA;
				if (iRead >= slen)
					break;

				*dest++ = src[iRead];
				iRead += stepB;
				if (iRead >= slen)
					break;
			}
		}

		CopyJumpSrcIncDest(src + D, src + slen, D * 2, dest);
		return res;
	}
};
