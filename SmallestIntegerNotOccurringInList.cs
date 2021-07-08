// Find the smallest integer that doesn't occur in a list
// Given [1, 3, 6, 4, 1, 2], the function should return 5.
// Given [1, 2, 3], the function should return 4.
// Given [-1, -3], the function should return 1.

using System;

class Solution
{
    public int solution(int[] A)
    {
        // Since we index into [length-1] and [length-2] later, make sure they're valid
        
        if (A.Length == 0)
            return 1;
        if (A.Length == 1)
            return (A[0] != 1) ? 1 : 2;
        
        // Ok, can continue. Sorting allows this to be solved without visiting every member or using extra space
        
        Array.Sort(A);

        // Check the two cases in which we can immediately just return 1. Examples being {2,3,4} and {-4,-3,-2} respectively
        
        if (A[0] > 1 || A[A.Length - 1] < 1)
            return 1;

        // If the list is consecutive, return highest + 1. We can know this without traversing the list at all.
        
        if (A[A.Length - 1] - A[0] == A.Length - 1)
            return A[A.Length - 1] + 1;

        // If the list is non-consecutive, and the result is within bounds of the lowest and highest members, find the lowest numbers with a gap of >1
        
        for (int i = 0; i < A.Length-2; i++)
            if (A[i+1] - A[i] > 1)
                return A[i] + 1;
        
        return -1; // unreachable
    }
}
