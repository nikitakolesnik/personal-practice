#include <iostream>


const int size = 10;


void printArray(int arr[])
{
	for (int i = 0; i < size; i++)
		std::cout << arr[i] << " ";
	std::cout << "\n";
}

//void rotateBruteForce(int * arr)
//void rotateBruteForce(int arr[5])
void rotateBruteForce(int arr[], int rotate)
{
	int prev, temp;
	for (int i = 0; i < rotate; i++)
	{
		prev = arr[size - 1];
		for (int j = 0; j < size; j++)
		{
			temp = arr[j];
			arr[j] = prev;
			prev = temp;

			//printArray(arr);
		}
	}
}

void rotateCopy(int arr[], int rotate)
{
	int copy[size];
	int index;

	for (int i = 0; i < size; i++)
	{
		index = (i + rotate) % size;
		//std::cout << "Writing " << arr[i] << " to index " << index << "\r\n";
		copy[index] = arr[i];
	}

	for (int i = 0; i < size; i++)
		arr[i] = copy[i];
}

void rotateReverseHelper(int arr[], int start, int end)
{
	int temp;
	while (start++ < end--)
	{
		temp = arr[start];
		arr[start] = arr[end];
		arr[end] = temp;
	}
}

void rotateReverse(int arr[], int rotate)
{
	rotateReverseHelper(arr, 0, rotate - 1);
	rotateReverseHelper(arr, rotate, size - 1);
	rotateReverseHelper(arr, 0, size - 1);
}

int main()
{
	int rotate = 1;
	int arr[size];

	for (int i = 0; i < size; i++)
		arr[i] = i;

	// Rotate the array by the same amount each time, in different ways:

	printArray(arr);
	rotateBruteForce(arr, rotate);
	printArray(arr);
	rotateCopy(arr, rotate);
	printArray(arr);
	rotateReverse(arr, rotate);
	printArray(arr);

	std::cin.get();
}
