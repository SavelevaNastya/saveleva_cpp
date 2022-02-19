int main()
{

	char* c = new char;
	*c = 'n';

	int* ar = new int[10];
	for (int i = 0; i < 10; i++)
		ar[i] = 1;

	int*& sar = ar;

	char const* arr_s[3] = { "s1", "s2", "s3" };

	char const* (*mrs)[3] = &arr_s;

	char** s = &c;

	int const cnst = 10;

	int const* rcint = &cnst;

	int* const crint = new int;
	*crint = 2;

	delete c;

	delete[] ar;

	delete crint;

}
