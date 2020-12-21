#define ZERO 0

int sum(int *a, int n)
{
	int i, s = ZERO;
	
	for (i=0;i<n;i++)
		s += a[i];
	
	return s;
	
}

