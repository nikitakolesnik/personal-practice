// Rotates a one-dimensional array using three different algorithms of varying time complexity

#include <iostream>


const int size   = 10; // Size of the consecutive-ascending int array to generate
const int rotate = 1;  // How many positions to rotate it by, using each algorithm


void printArray(int arr[])
{
	for (int i = 0; i < size; i++)
		std::cout << arr[i] << " ";
	std::cout << "\n";
}

// Exponential time complexity iterative solution
void rotateBruteForce(int arr[], int rotate)
{
	int prev, temp;
	
	for (int i = 0; i < rotate; i++)
	{
		prev = arr[size - 1];
		for (int j = 0; j < size; j++)
		{
			temp   = arr[j];
			arr[j] = prev;
			prev   = temp;
		}
	}
}

// 2n time & space complexity iterative solution
void rotateCopy(int arr[], int rotate)
{
	int copy[size], index;

	for (int i = 0; i < size; i++)
	{
		index = (i + rotate) % size;
		copy[index] = arr[i];
	}

	for (int i = 0; i < size; i++)
		arr[i] = copy[i];
}

// Linear time complexity recursive solution
void rotateReverseHelper(int arr[], int start, int end)
{
	int temp;
	
	while (start++ < end--)
	{
		temp       = arr[start];
		arr[start] = arr[end];
		arr[end]   = temp;
	}
}

void rotateReverse(int arr[], int rotate)
{
	rotateReverseHelper(arr,      0, rotate - 1);
	rotateReverseHelper(arr, rotate,   size - 1);
	rotateReverseHelper(arr,      0,   size - 1);
}

int main()
{
	int arr[size];

	for (int i = 0; i < size; i++)
		arr[i] = i;

	// Rotate the array by the same amount each time, in different ways:

	printArray(arr); // Original
	
	rotateBruteForce(arr, rotate);
	printArray(arr); // Rotated r * 1
	
	rotateCopy(arr, rotate);
	printArray(arr); // Rotated r * 2
	
	rotateReverse(arr, rotate);
	printArray(arr); // Rotated r * 3

	std::cin.get();
}
