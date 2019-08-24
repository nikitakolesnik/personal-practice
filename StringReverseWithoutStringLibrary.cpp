// A completely worthless, not applicable exercise

#include <iostream>

void mystrrev(char* s)
{
	// Find out how long it is
	char* trav = s;
	while (*trav)
		++trav;
	int len = trav - s;

	// Only need to iterate for half the length, odd-length-case is automatically handled (ex: length=9, truncated division result is 4, 5th spot correctly ignored)
	for (int i = 0; i < len / 2; i++)
	{
		// Swap str[i] & str[1+len-i] without using extra variable
		*(s + i) ^= *(s + len - i - 1);
		*(s + len - i - 1) ^= *(s + i);
		*(s + i) ^= *(s + len - i - 1);
	}
}

int main()
{
	char test[29];
	strcpy_s(test, "This is a great use of time.");
	mystrrev(test);
	std::cout << test << '\n';
}
