/*
Data structure:
	- array

The idea is very basic backtracking with pruning.

First build a adjacent matrix to represent the graph. Then do backtracking on the graph and output the route when reached the
fire location. 

Before backtracking, do depth first search starting from the fire location to identify which locations are connected with it.
So when backtracking, we can prune if the fire location is not reachable by the next location.

*/


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <bitset>
#include <cstring>
using namespace std;

int graph[22][22] = {0};
int visited[22] = {0};
int routeCount = 0;
int caseCount = 0;
int N;
int reachable[22] = {0};
vector<int> route;

void checkReachable(int x){
	reachable[x] = 1;
	for (int i = 1; i <= 21; ++i)
	{
		if(graph[x][i] && !reachable[i]){
			checkReachable(i);
		}
	}
}

void printRoute()
{
	for(int i = 0; i < route.size(); i++){
		cout << route[i] << ' ';
	}
	cout << N << endl;
}

void dfs(int x)
{
	if(x == N){
		routeCount += 1;
		printRoute();
		return;
	}
	visited[x] = 1;
	route.push_back(x);

	for(int i = 1; i <= 21; i++){
		if(graph[x][i] && !visited[i] && reachable[i]){
			dfs(i);
		}
	}
	route.pop_back();
	visited[x] = 0;
}

int main(int argc, char const *argv[])
{
	while(1){
		cin >> N;
		if(cin.eof())
			return 0;
		memset(graph, 0, sizeof(int) * 22 * 22);
		memset(visited, 0, sizeof(int) * 22);
		memset(reachable, 0, sizeof(int) * 22);
		routeCount = 0;
		caseCount++;

		route.clear();

		while(1){
			int v1, v2;
			cin >> v1 >> v2;
			if(v1 == 0 && v2 == 0){
				break;
			}
			graph[v1][v2] = 1;
			graph[v2][v1] = 1;
		}
		checkReachable(N);
		cout << "CASE " << caseCount << ":" << endl;
		dfs(1);
		cout << "There are " << routeCount << " routes from the firestation to streetcorner " << N << '.' << endl;
	}


	return 0;
}