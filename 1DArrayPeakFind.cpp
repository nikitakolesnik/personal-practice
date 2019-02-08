// Finding any peak in an array, in a both efficient & inefficient way, where an element is greater than or equal to any elements surrounding it
// Based on this MIT lecture: https://youtu.be/HtSuA80QTyo

#include <iostream>
#include <sstream>

std::string listString(__int16 arr[10]) {
	std::stringstream ss;
	for (__int16 i = 0; i < 10; i++) ss << ((i==0) ? "" : ",") << arr[i];
	return ss.str();
}

// Linear time complexity
__int16 peakLinear(__int16 arr[10]) {
	// Edge case
	if (arr[0] >= arr[1]) return 0;
	if (arr[9] >= arr[8]) return 9;
	
	// Middle case
	for (__int16 i = 1; i < 9; i++)
		if (arr[i] >= arr[i - 1] && arr[i] >= arr[i + 1])
			return i;
	
	// Just in case
	return -1;
}

// Logarithmic time complexity
__int16 peakLog(__int16 arr[], __int16 start, __int16 end) {
	__int16 half = (start + end + 1) / 2;                                                                                                  // Look at the middle of the range
	
	// if it's on a boundary and bigger, return it
	if ((half == start && arr[start] >= arr[start+1]) || (half==end && arr[half] >= arr[half-1])) 
		return half;                        
	
	// if middle is bigger than L & R, return it
	else if ((arr[half] >= arr[half-1]) && (arr[half] >= arr[half+1]))
		return half;                        
	
	// if middle is smaller or equal to left, look left
	else if (arr[half] <= arr[half-1]) 
		return peakLog(arr, start, half-1); 
	
	// if middle is smaller or equal to right, look right
	else 
		return peakLog(arr, half+1, end);   
}

int main() {
	__int16 peakLeft[10]  = { 10,9,8,7,6,5,4,3,2,1 };
	__int16 peakRight[10] = { 1,2,3,4,5,6,7,8,9,10 };
	__int16 peakMid[10]   = { 1,3,5,7,9,10,8,6,4,2 };
	__int16 jagged[10]    = { 1,2,1,2,1,2,1,2,1,2 };
	__int16 even[10]      = { 1,1,1,1,1,1,1,1,1,1 };

	std::cout << "For peak-left   list {" << listString(peakLeft)  << "}, peak is at position: " << peakLinear(peakLeft)  << "|" << peakLog(peakLeft, 0, 9)  << "\r\n"
		  << "For peak-center list {" << listString(peakMid)   << "}, peak is at position: " << peakLinear(peakMid)   << "|" << peakLog(peakMid, 0, 9)   << "\r\n"
		  << "For peak-right  list {" << listString(peakRight) << "}, peak is at position: " << peakLinear(peakRight) << "|" << peakLog(peakRight, 0, 9) << "\r\n"
		  << "For jagged      list {" << listString(jagged)    << "}, peak is at position: " << peakLinear(jagged)    << "|" << peakLog(jagged, 0, 9)    << "\r\n"
		  << "For even        list {" << listString(even)      << "}, peak is at position: " << peakLinear(even)      << "|" << peakLog(even, 0, 9)      << "\r\n";

	std::cin.get();
}
