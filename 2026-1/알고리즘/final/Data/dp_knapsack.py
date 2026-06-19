"""
0/1 Knapsack

각 물건을 넣거나 넣지 않는 선택만 가능할 때, 무게 제한 안에서 가치 합을 최대화한다.
dp[i][w] = 앞 i개 물건만 고려하고 용량이 w일 때의 최대 가치

n: 물건 수, W: 배낭 용량
시간복잡도: O(nW)
"""


def knapsack_01(weights, values, capacity):
	"""weights: 각 물건의 무게, values: 각 물건의 가치
	capacity: 배낭 용량
	반환값: (최대 가치, 선택된 물건 index 리스트)
	시간복잡도: O(nW)
	"""
	n = len(weights)
	dp = [[0] * (capacity + 1) for _ in range(n + 1)]

	for i in range(1, n + 1):
		weight = weights[i - 1]
		value = values[i - 1]

		for w in range(capacity + 1):
			dp[i][w] = dp[i - 1][w]

			if (weight <= w):
				dp[i][w] = max(dp[i][w], dp[i - 1][w - weight] + value)

	# dp 표를 거꾸로 보며 선택된 물건을 복원한다.
	selected = []
	w = capacity
	for i in range(n, 0, -1):
		if (dp[i][w] != dp[i - 1][w]):
			selected.append(i - 1)
			w -= weights[i - 1]

	selected.reverse()
	return dp[n][capacity], selected
