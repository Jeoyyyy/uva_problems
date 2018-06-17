/*
The idea is to use backtracking. It is intuitive to go through every path and see if it meets the requirements. But simply
doing so would be too slow. So we need to prune. There are the following prune conditions:
	- If the distance between the current position and the next checkpoint is more than the steps left to get there
	- If we have stepped into checkpoints or endpoint ahead of time
	- If the remaining not visited points are disconnected.

*/


#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int count;
int rows, cols;
int cr[3];
int cc[3];
int visited[9][9];

int disconnected(int r, int c)
{
	int surround[9];
	surround[0] = r - 1 >= 0 && c - 1 >= 0 && !visited[r-1][c-1];
	surround[1] = r - 1 >= 0 && !visited[r-1][c];
	surround[2] = r - 1 >= 0 && c + 1 < cols && !visited[r-1][c+1];
	surround[3] = c + 1 < cols && !visited[r][c+1];
	surround[4] = r + 1 < rows && c + 1 < cols && !visited[r+1][c+1];
	surround[5] = r + 1 < rows && !visited[r+1][c];
	surround[6] = r + 1 < rows && c - 1 >= 0 && !visited[r+1][c-1];
	surround[7] = c - 1 >= 0 && !visited[r][c-1];
	surround[8] = surround[0];
	int count = 0;
	for(int i = 0; i < 8; i++){
		if(surround[i] != surround[i+1]){
			count++;
		}
	}
	return count >= 4;
}

int prun(int r, int c, int step)
{
	if(step <= rows * cols / 4 && abs(cr[0] - r) + abs(cc[0] - c) > rows * cols / 4 - step){
		return 1;
	}
	if(step <= rows * cols / 2 && abs(cr[1] - r) + abs(cc[1] - c) > rows * cols / 2 - step){
		return 1;
	}
	if(step <= rows * cols * 3 / 4 && abs(cr[2] - r) + abs(cc[2] - c) > rows * cols * 3 / 4 - step){
		return 1;
	}
	if(step < rows * cols && abs(0 - r) + abs(1 - c) > rows * cols - step){
		return 1;
	}
	if(r == cr[0] && c == cc[0] && step != rows * cols / 4)
		return 1;
	if(r == cr[1] && c == cc[1] && step != rows * cols / 2)
		return 1;
	if(r == cr[2] && c == cc[2] && step != rows * cols * 3 / 4)
		return 1;

	if(r == 0 && c == 1 && step != rows * cols){
		return 1;
	}
	if(!(r == 0 && c == 1) && step == rows * cols){
		return 1;
	}
	if(disconnected(r, c))
		return 1;
	return 0;
}

void solve(int r, int c, int step)
{
	if(r == 0 && c == 1 && step == rows * cols){
		count++;
		return;
	}
	if(r - 1 >= 0 && !visited[r-1][c] && !prun(r - 1, c, step + 1)){
		visited[r-1][c] = 1;
		solve(r - 1, c, step + 1);
		visited[r-1][c] = 0;
	}
	if(r + 1 < rows && !visited[r+1][c] && !prun(r + 1, c, step + 1)){
		visited[r + 1][c] = 1;
		solve(r + 1, c, step + 1);
		visited[r + 1][c] = 0;
	}
	if(c - 1 >= 0 && !visited[r][c - 1] && !prun(r, c - 1, step + 1)){
		visited[r][c - 1] = 1;
		solve(r, c - 1, step + 1);
		visited[r][c - 1] = 0;
	}
	if(c + 1 < cols && !visited[r][c + 1] && !prun(r , c + 1, step + 1)){
		visited[r][c + 1] = 1;
		solve(r, c + 1, step + 1);
		visited[r][c + 1] = 0;
	}
	return;
}

int main(int argc, char const *argv[])
{
	int caseno = 0;
	while(true){
		caseno++;
		cin >> rows >> cols;
		if(rows == 0 || cols == 0){
			break;
		}
		cin >> cr[0] >> cc[0] >> cr[1] >> cc[1] >> cr[2] >> cc[2];
		memset(visited, 0, sizeof(int) * 9 * 9);
		count = 0;
		solve(0, 0, 1);
		cout << "Case " << caseno << ": " << count << endl;
	}
	return 0;
}