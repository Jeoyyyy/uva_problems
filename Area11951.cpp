#include <iostream>
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{
	int T;
	cin >> T;
	for (int t = 0; t < T; ++t)
	{
		int N, M, K;
		cin >> N >> M >> K;
		int columnSum[N][M];
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < M; ++j)
			{
				cin >> columnSum[i][j];
				if(i > 0){
					columnSum[i][j] += columnSum[i-1][j];
				}
			}
		}
		int maxArea = 0;
		int minCost = 0;
		for (int i = 0; i < N; ++i)
		{
			for (int j = i; j < N; ++j)
			{
				int area = 0;
				int cost = 0;
				int startCol = 0;
				for (int k = 0; k < M; ++k)
				{
					if(i == 0){
						cost += columnSum[j][k];
					}
					else{
						cost += columnSum[j][k] - columnSum[i-1][k];
					}
					while(cost > K){
						if(i == 0){
							cost -= columnSum[j][startCol];
						}
						else{
							cost -= columnSum[j][startCol] - columnSum[i-1][startCol];
						}
						startCol += 1;
					}
					area = (j - i + 1) * (k - startCol + 1);
					if(maxArea < area){
						maxArea = area;
						minCost = cost;
					}
					else if(maxArea == area && minCost > cost){
						minCost = cost;
					}
				}
			}
		}
		printf("Case #%d: %d %d\n", t + 1, maxArea, minCost);
	}
	return 0;
}