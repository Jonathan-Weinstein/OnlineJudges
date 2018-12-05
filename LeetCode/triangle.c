//hooray the runtime of this is faster than 100% of C submission, whatever that means.

static inline int Min(int a, int b) { return b<a ? b : a; }

typedef int const *const ptr;

//at least 2 rows, aux must span nrows-1 ints
int f(ptr *pprows, int nrows, int *aux)
{
	int toprowlen = nrows - 1;//itop is toprowlen - 1
	const int *ptop = pprows[toprowlen - 1];
	//initialize aux
	{
		const int *pbot = pprows[toprowlen];
		for (int j = 0; j != toprowlen; ++j)
			aux[j] = ptop[j] + Min(pbot[j], pbot[j + 1]);
	}

	while (--toprowlen != 0)//while itop != -1
	{
		ptop = pprows[toprowlen - 1];
		int a = aux[0];
		for (int j = 0; j != toprowlen; ++j)
		{
			int const b = aux[j+1];
			aux[j] = ptop[j] + Min(a, b);
			a = b;
		}
	}

	return aux[0];
}


int minimumTotal(int** triangle, int triangleRowSize, int *triangleColSizes)
{
	if (triangleRowSize < 2)
		return triangleRowSize>=0 ? triangle[0][0] : 0;
	return f(triangle, triangleRowSize, triangleColSizes);//triangleColSizes is pointless
}



int main()
{
	return 0;
}