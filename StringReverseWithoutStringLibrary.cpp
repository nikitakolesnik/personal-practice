//A completely worthless, not applicable exercise

#include <iostream>

void mystrrev(char* s)
{
	int len = 0;
	char* trav = s;

	while (*trav++)
		len++;

	for (int i = 0; i < len/2; i++)
	{
		*(s+i) ^= *(s + len - i - 1);
		*(s + len - i - 1) ^= *(s + i);
		*(s + i) ^= *(s + len - i - 1);
	}
}

int main()
{
	char test[6];
	strcpy_s(test, "hello");
	
	mystrrev(test);

	std::cout << test << '\n';
}
