#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>
using namespace std;

int main(int argc, char const *argv[])
{
	while(1){
		int rows, cols;
		cin >> rows >> cols;
		if(cin.eof())
			break;
		int grid[rows][cols];
		for(int i = 0; i < rows; i++){
			for(int j = 0; j < cols; j++){
				cin >> grid[i][j];
			}
		}

		int dp[rows][cols]; //dp[i][j] is the minimum weight of path end in grid[i][j]
		string path[rows][cols];

		int minEndRow, minLen = 0x7fffffff;
		for(int i = 0; i < rows; i++){
			dp[i][0] = grid[i][0];
			path[i][0] = "";
			if(cols == 1){
				if(dp[i][0] < minLen){
					minLen = dp[i][0];
					minEndRow = i;
				}
			}
		}
		if(cols == 1){
			cout << minEndRow + 1 << endl;
			cout << minLen << endl;
			continue;
		}

		for(int j = 1; j < cols; j++){
			for(int i = 0; i < rows; i++){
				int min = std::min( std::min(dp[(i-1+rows)%rows][j-1], dp[i][j-1]), dp[(i+1)%rows][j-1] );
				dp[i][j] = min + grid[i][j];
				//If there are more than one minimum path, choose the path with least lexicographic order
				vector<string> pathsToChoose;
				if(dp[(i-1+rows)%rows][j-1] == min){
					string s = path[(i-1+rows)%rows][j-1] + to_string((i-1+rows)%rows);
					pathsToChoose.push_back(s);
				}
				if(dp[i][j-1] == min){
					string s = path[i][j-1] + to_string(i);
					pathsToChoose.push_back(s);
				}
				if(dp[(i+1)%rows][j-1] == min){
					string s = path[(i+1)%rows][j-1] + to_string((i+1)%rows);
					pathsToChoose.push_back(s);
				}
				sort(pathsToChoose.begin(), pathsToChoose.end());
				path[i][j] = pathsToChoose[0];

				if(j == cols - 1){
					if(dp[i][j] < minLen){
						minLen = dp[i][j];
						minEndRow = i;
					}
					else if(dp[i][j] == minLen && path[i][j] < path[minEndRow][j]){
						minEndRow = i;
					}
				}
			}
		}
		for(int i = 0; i < path[minEndRow][cols - 1].length(); i++){
			if(path[minEndRow][cols - 1][i] == '9'){
				cout << "10 ";
			}
			else{
				cout << char( int(path[minEndRow][cols - 1][i]) + 1 ) << ' ';
			}
		}
		cout << minEndRow + 1 << endl;
		cout << minLen << endl;
	}

	return 0;
}