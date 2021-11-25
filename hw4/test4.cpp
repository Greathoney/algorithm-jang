// C++ implementation of the above approach
#include <bits/stdc++.h>
#define maxN 31
#define maxW 31
using namespace std;

// 3D array to store
// states of DP
int dp[maxN][maxW][maxW];

// w1_r represents remaining capacity of 1st knapsack
// w2_r represents remaining capacity of 2nd knapsack
// i represents index of the array arr we are working on
int maxWeight(int* arr, int n, int w1_r, int w2_r, int i)
{
	// Base case
	if (i == n)
		return 0;
	if (dp[i][w1_r][w2_r] != -1)
		return dp[i][w1_r][w2_r];

	// Variables to store the result of three
	// parts of recurrence relation
	int fill_w1 = 0, fill_w2 = 0, fill_none = 0;

	if (w1_r >= arr[i])
		fill_w1 = arr[i] +
		maxWeight(arr, n, w1_r - arr[i], w2_r, i + 1);

	if (w2_r >= arr[i])
		fill_w2 = arr[i] +
		maxWeight(arr, n, w1_r, w2_r - arr[i], i + 1);

	fill_none = maxWeight(arr, n, w1_r, w2_r, i + 1);

	// Store the state in the 3D array
	dp[i][w1_r][w2_r] = max(fill_none, max(fill_w1, fill_w2));

	return dp[i][w1_r][w2_r];
}

// Driver code
int main()
{
	// Input array
	int arr[] = { 8, 2, 3 };

	// Initializing the array with -1
	memset(dp, -1, sizeof(dp));

	// Number of elements in the array
	int n = sizeof(arr) / sizeof(arr[0]);

	// Capacity of knapsacks
	int w1 = 10, w2 = 3;

	// Function to be called
	cout << maxWeight(arr, n, w1, w2, 0);
	return 0;
}
