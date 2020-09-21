using System;

class Solution
{
    public int solution(int[] A)
    {
        Array.Sort(A);
        
        // If the highest number is negative or zero
        int prev = A[A.Length-1];
        if (prev < 1)
            return 1;

        // If the result is lower than the highest
        for (int i = A.Length-2; i > 0; i--)
        {
            if ((prev - A[i]) > 1)
            {
                return prev - 1;
            }
            prev = A[i];
        }

        // If the list is consecutive (previous loop wasn't returned out of), return highest+1
        return A[A.Length - 1] + 1;
    }
}
