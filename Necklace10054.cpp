/*
Data structure:
	- array

This problem is essentially Euler circle problem. Beams are edges and colors are verteces.

For Euler circle to exist in the graph, the graph must be connected and all the degrees of verteces must be even.

If so, then find the Euler circle using Hierholzer's algorithm. So I add the verteces to the path as long as it's degree
is not 0. 

*/


#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <list>
using namespace std;
int N;
int graph[51][51];
int connected[51];
int used[51];
int degree[51];

void checkConnectivity(int x)
{
	connected[x] = 1;
	for(int i = 1; i < 51; i++){
		if(graph[x][i] && !connected[i])
			checkConnectivity(i);
	}
}

bool allConnected()
{
	for(int i = 1; i < 51; i++){
		if(connected[i] != used[i])
			return false;
	}
	return true;
}

bool checkDegree()
{
	for(int i = 1; i < 51; i++){
		if(degree[i] % 2 != 0)
			return false;
	}
	return true;
}

void dfs(list<int>& path, list<int>::iterator it, int x)
{
	for(int i = 1; i < 51; i++){
		if(graph[x][i]){
			graph[x][i]--;
			graph[i][x]--;
			dfs(path, path.insert(it, i), i);
		}
	}
}

int main(int argc, char const *argv[])
{
	int caseNum;
	cin >> caseNum;
	for(int caseno = 1; caseno <= caseNum; caseno++){
		cin >> N;
		list<int> path;
		memset(graph, 0, sizeof(int) * 51 * 51);
		memset(connected, 0, sizeof(int) * 51);
		memset(used, 0, sizeof(int) * 51);
		memset(degree, 0, sizeof(int) * 51);
		int start = 0;
		for(int i = 0; i < N; i ++){
			int v1, v2;
			cin >> v1 >> v2;
			if(start == 0)
				start = v1;
			graph[v1][v2] += 1;
			graph[v2][v1] += 1;
			used[v1] = 1;
			used[v2] = 1;
			degree[v1] += 1;
			degree[v2] += 1;
		}
		if(caseno != 1){
			cout << endl;
		}
		cout << "Case #" << caseno << endl;
		checkConnectivity(start);
		if(!allConnected() || !checkDegree()){
			cout << "some beads may be lost" << endl;
			continue;
		}

		dfs(path, path.insert(path.begin(), start), start);

		for(list<int>::iterator it = path.begin(); next(it)!= path.end(); it++){
			cout << *(it) << ' ' << *next(it) << endl;
		}
	}
	return 0;
}