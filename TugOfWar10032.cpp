/*
I used 3D dp for this problem.

First let's consider boolean array dp[i][j][k] which is true when it is possible to select k people from i people whose total
weight is j.

So the i increment by 1 every time, meaning we add 1 people to the list every step. Then we could either select this person
or not. If we select this person, dp[i][j][k] = dp[i-1][j - weight[j]][k-1]. If not, dp[i][j][l] = dp[i-1][j][k]. Note here 
if j < weight[i] then we can not select this person. If j == weight[i], we could either not select this person or only select
this only one person. 

Since it is a boolean array, we could make it a 2D long int array by using each digit of dp[i][j] to represent dp[i][j][k]. 
Since n <= 100, and we only care about selecting half of the people, so we could only use  51 bits.

We could reduce the memory usage further more by using only two 1D arrays because dp[i] is only related to dp[i-1]. After 
adding the last person, we let j goes from sum of weights / 2 to 0 and find the first j that dp[n-1][j][n/2] is true if n is 
even and similarly if n is odd.
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <bitset>
#include <cstring>
using namespace std;

int main(int argc, char const *argv[])
{
	int caseNum;
	cin >> caseNum;
	for (int caseno = 0; caseno < caseNum; caseno++) {
		int n;
		cin >> n;
		int weights[n];
		int weightSum = 0;
		for (int i = 0; i < n; i++) {
			cin >> weights[i];
			weightSum += weights[i];
		}
		long long dp[2][weightSum / 2 + 1];
		memset(dp, 0, sizeof(dp));
		long long* prev;
		long long* cur;
		// dp[1][0] = 1;
		for (int i = 0; i < n; i++) {
			cur = dp[i%2];
			prev = dp[(i+1)%2];
			for(int j = 0; j <= weightSum/2; j++){
				if(j > weights[i]){
					cur[j] = (prev[j - weights[i]] << 1) | prev[j];
				}
				else if(j == weights[i]){
					cur[j] = 2 | prev[j];
				}
				else{
					cur[j] = prev[j];
				}
			}
		}
		// n is even, two side must have the same number of people
		if(n%2 == 0){
			for(int j = weightSum/2; j >= 0; j--){
				if(cur[j] & (1ll << n/2)){
					cout << j << ' ' << weightSum - j << endl;
					break;
				}
				if(j == 0){
					cout << 0 << ' ' << weightSum << endl;
				}
			}
		}
		// n is odd, numbers of people of two side differ by 1
		else{
			for(int j = weightSum/2; j >= 0; j--){
				// cout << bitset<64>(cur[j]) << endl;
				if(cur[j] & (1ll << n/2) || cur[j] & (1ll << (n/2+1))){
					cout << j << ' ' << weightSum - j << endl;
					break;
				}
				if(j == 0)
					cout << 0 << ' ' << weightSum << endl;
			}
		}
		if (caseno != caseNum - 1)
			cout << endl;
	}
	return 0;
}