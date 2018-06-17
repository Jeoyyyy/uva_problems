#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <unordered_set>
#include <unordered_map>
using namespace std;

#define MAXN 10000
#define MAXM 50000

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
	int T;
	cin >> T;
	for (int t = 0; t < T; ++t)
	{
		int n, m;
		cin >> n >> m;
		int balance[n];
		for (int i = 0; i < n; ++i)
		{
			cin >> balance[i];
		}
		vector<int> sets(n, -1);
		unordered_map<int, vector<int>> circle;
		for (int i = 0; i < m; ++i)
		{
			int f1, f2;
			cin >> f1 >> f2;
			_union(f1, f2, sets);
		}
		for(int i = 0; i < sets.size(); i++){
			int x = find(i, sets);
			if(circle.count(x) == 0){
				circle[x] = vector<int>();
			}
			circle[x].push_back(i);
		}
		int flag = 0;
		for(auto& x : circle){
			vector<int> friends = x.second;
			int sum = 0;
			for (int i = 0; i < friends.size(); ++i)
			{
				sum += balance[friends[i]];
			}
			if(sum != 0){
				cout << "IMPOSSIBLE" << endl;
				flag = 1;
				break;
			}
		}
		if(flag == 0){
			cout << "POSSIBLE" << endl;
		}
	}
	return 0;
}