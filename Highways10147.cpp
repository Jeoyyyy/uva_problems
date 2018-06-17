/*
Data structure:
	- sets(implemented by array)
	- priority queue
	- pair

This problem is a minimum spanning tree problem. I used Kruskal's algorithm.

Towns are regarded as verteces and highways are regarded as edges in the graph. This is a complete graph, meaning
there is a edge between each pair of verteces. All these edge are pushed to a min heap. Everytime pop an edge from the heap and
add output this edge if it does not create a cycle. 

To identify cycle, I used sets. Verteces that are interconnected are put in one set.  So if the two endpoints of the edge
are already in a set, adding the edge would create a cycle.

*/

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <queue>
#include <cmath>
using namespace std;

struct Coordinates {
	int x;
	int y;
};

int find(int a, vector<int>& sets)
{
	if(sets[a] < 0)
		return a;
	else{
		return find(sets[a], sets);
	}
}

bool _union(int a, int b, vector<int>& sets)
{
	int set1 = find(a, sets);
	int set2 = find(b, sets);
	if(set1 == set2){
		return false;
	}
	else{
		if(sets[set1] < sets[set2]){
			sets[set1] += sets[set2];
			sets[set2] = set1;
		}
		else{
			sets[set2] += sets[set1];
			sets[set1] = set2;
		}
		return true;
	}
}

int main(int argc, char const *argv[])
{
	int caseNum;
	cin >> caseNum;
	for(int caseno = 0; caseno < caseNum; caseno++){
		int townNum;
		int highwayNum;
		
		cin >> townNum;

		Coordinates towns[townNum+1];
		priority_queue<pair<double, pair<int, int>>, vector<pair<double, pair<int, int>>>, greater<pair<double, pair<int, int>>> > pq;
		vector<int> sets (townNum + 1, -1);

		for(int i = 1; i < townNum + 1; i++){
			cin >> towns[i].x >> towns[i].y;
		}

		cin >> highwayNum;
		int connectedTownsNum = 1;
		for(int i = 0; i < highwayNum; i++){
			int t1, t2;
			cin >> t1 >> t2;
			if(_union(t1, t2, sets)){
				connectedTownsNum++;
			}
		}

		if(caseno != 0)
			cout << endl;

		if(connectedTownsNum == townNum){
			cout << "No new highways need" << endl;
			continue;
		}

		for(int i = 1; i < townNum + 1; i++){
			for(int j = i; j < townNum + 1; j++){
				pair<int, int> p (i, j);
				double dis = sqrt(pow(towns[i].x - towns[j].x, 2) + pow(towns[i].y - towns[j].y, 2));
				pair<double, pair<int, int>> edge (dis, p);
				pq.push(edge);
			}
		}
		while(connectedTownsNum != townNum){
			pair<double, pair<int, int>> edge = pq.top();
			pq.pop();
			int t1 = edge.second.first;
			int t2 = edge.second.second;
			if(_union(t1, t2, sets)){
				connectedTownsNum++;
				cout << t1 << ' ' << t2 << endl;
			}
		}

	}
	return 0;
}