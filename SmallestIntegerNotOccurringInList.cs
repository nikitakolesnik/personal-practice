// Find the smallest integer that doesn't occur in a list
// Given [1, 3, 6, 4, 1, 2], the function should return 5.
// Given [1, 2, 3], the function should return 4.
// Given [-1, -3], the function should return 1.

using System;

class Solution
{
    public int solution(int[] A)
    {
        Array.Sort(A);

        // If the highest number is negative or zero
        int prev = A[A.Length - 1];
        if (prev < 1)
            return 1;

        int min = int.MaxValue;
        // If the result is lower than the highest number
        for (int i = A.Length - 2; i >= 0; i--)
        {
            if (prev - A[i] > 1) // If these two elements have a gap larger than 1
            {
                if (A[i] + 1 < min) // And if the lowest number in this gap is the new minimum
                {
                    min = A[i] + 1;
                }
            }
            prev = A[i];
        }

        // If the list is consecutive (previous loop didn't update "min"), return highest+1
        return (min != int.MaxValue) ? min : A[A.Length - 1] + 1;
    }
}
