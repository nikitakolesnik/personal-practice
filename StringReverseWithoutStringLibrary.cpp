//A completely worthless, not applicable exercise

#include <iostream>

void str_rev(char* str)
{
	char* walk = str; // Find out how long it is
	while (*walk)
		++walk;
	int len = walk - str;

	for (int i = 0; i < len / 2; i++) // Only need to iterate for half the length, odd-length-case is automatically handled (ex: length=9, truncated division result is 4, 5th spot correctly ignored)
	{
		*(str+i) ^= *(str+len-i-1); // Swap str[i] & str[1+len-i] without using extra variable
		*(str+len-i-1) ^= *(str+i);
		*(str+i) ^= *(str+len-i-1);
	}
}

int main()
{
	char str[29];
	strcpy_s(str, "This is a great use of time.");
	str_rev(str);
	std::cout << str << '\n';
}
