// Find the smallest integer that doesn't occur in a list
// Given [1, 3, 6, 4, 1, 2], the function should return 5.
// Given [1, 2, 3], the function should return 4.
// Given [-1, -3], the function should return 1.

using System;

class Solution
{
    public int solution(int[] A)
    {
        Array.Sort(A); // Allows this to be potentially solved without visiting every member or using extra space
        int last = A[A.Length - 1];

        // If the lowest number is greater than one
        if (A[0] > 1)
            return 1;

        // If the highest number is negative or zero
        if (last < 1)
            return 1;

        // If the list is consecutive, return highest + 1. We can know this without traversing the list at all.
        if (A[A.Length - 1] - A[0] == A.Length - 1)
            return A[A.Length - 1] + 1;

        // If the list is non-consecutive, and the result is within bounds of the lowest and highest members
        int min = int.MaxValue;
        for (int i = A.Length - 2; i >= 0; i--) // Going backwards, starting with the second-to-last number
        {
            if (last - A[i] > 1) // If these two elements have a gap larger than 1,
                min = A[i] + 1;  // Then the new minimum is the lowest number in this gap
            last = A[i];
        }
        return min; // this has to have been updated, since the consecutive case was handled above
    }
}
