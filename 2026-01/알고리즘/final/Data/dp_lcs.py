"""
LCS (Longest Common Subsequence)

두 문자열에서 순서를 유지하며 공통으로 나타나는 가장 긴 부분수열을 구한다.
연속될 필요는 없고, 상대적인 순서만 유지하면 된다.

n: 첫 번째 문자열 길이, m: 두 번째 문자열 길이
시간복잡도: O(nm)
"""


def lcs(a, b):
	"""a, b: 비교할 문자열
	반환값: (LCS 길이, LCS 문자열)
	시간복잡도: O(nm)
	"""
	n = len(a)
	m = len(b)
	dp = [[0] * (m + 1) for _ in range(n + 1)]

	# dp[i][j] = a[:i]와 b[:j]의 LCS 길이
	for i in range(1, n + 1):
		for j in range(1, m + 1):
			if (a[i - 1] == b[j - 1]):
				dp[i][j] = dp[i - 1][j - 1] + 1
			else:
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])

	# dp 표를 거꾸로 따라가며 실제 LCS 문자열을 복원한다.
	result = []
	i = n
	j = m
	while (i > 0 and j > 0):
		if (a[i - 1] == b[j - 1]):
			result.append(a[i - 1])
			i -= 1
			j -= 1
		elif (dp[i - 1][j] >= dp[i][j - 1]):
			i -= 1
		else:
			j -= 1

	result.reverse()
	return dp[n][m], "".join(result)
