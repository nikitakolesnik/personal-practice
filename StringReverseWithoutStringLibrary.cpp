#include <iostream>

void my_str_rev(char* str)
{
	char* walk = str; // Find out how long it is
	while (*walk)
		++walk;
	int len = walk - str;

	for (int i = 0; i < len / 2; i++) // Only need to iterate for half the length, odd-length-case is automatically handled (ex: length=9, truncated division result is 4, 5th spot correctly ignored)
	{
		*(str + i) ^= *(str + len - i - 1); // XOR swap to not use extra var
		*(str + len - i - 1) ^= *(str + i);
		*(str + i) ^= *(str + len - i - 1);
	}
}

int main()
{
	char str[64];
	strcpy_s(str, "I get reversed without a library!");
	my_str_rev(str);
	std::cout << str << '\n';
}
