caseNum = int(input())
for _ in range(caseNum):
	seq = input()
	sub = input()
	# dp[i][j] is the number of distinct subsequences of sub[:i+1] in seq[:j+1]
	dp = [[0 for _ in range(len(seq))] for _ in range(len(sub))]
	if seq[0] == sub[0]:
		dp[0][0] = 1
	for j in range(1, len(seq)):
		if seq[j] == sub[0]:
			dp[0][j] = dp[0][j-1] + 1
		else:
			dp[0][j] = dp[0][j-1]
		
	for i in range(1, len(sub)):
		for j in range(1, len(seq)):
			if seq[j] == sub[i]:
				dp[i][j] = dp[i-1][j-1] + dp[i][j-1]
			else:
				dp[i][j] = dp[i][j-1]
	print(dp[len(sub) - 1][len(seq) - 1])
