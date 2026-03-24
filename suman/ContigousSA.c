#include <stdio.h>
#include <stdlib.h>

#define MAX 100000

// Simple hash map using array (for demo, assumes sums are in range)
int freq[2 * MAX + 1];

int countZeroSumSubarrays(int arr[], int n) {
    int prefix_sum = 0;
    int count = 0;

    // Initialize frequency array
    for (int i = 0; i < 2 * MAX + 1; i++)
        freq[i] = 0;

    // To handle prefix sum = 0
    freq[MAX] = 1;

    for (int i = 0; i < n; i++) {
        prefix_sum += arr[i];

        // Shift index to avoid negative indexing
        int index = prefix_sum + MAX;

        count += freq[index];
        freq[index]++;
    }

    return count;
}

int main() {
    int arr[] = {1, -1, 2, -2, 3};
    int n = sizeof(arr) / sizeof(arr[0]);

    int result = countZeroSumSubarrays(arr, n);
    printf("Total subarrays with sum 0: %d\n", result);

    return 0;
}
