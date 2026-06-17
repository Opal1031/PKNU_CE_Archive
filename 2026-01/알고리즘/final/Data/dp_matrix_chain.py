"""
Matrix Chain Multiplication

여러 행렬 A1 A2 ... An을 곱할 때, 곱셈 순서에 따라 연산 횟수가 달라진다.
DP로 최소 scalar multiplication 횟수와 괄호 위치를 구한다.

n: 행렬 개수
시간복잡도: O(n^3)
"""

INF = 10**18


def matrix_chain_order(dimensions):
	"""dimensions: [p0, p1, ..., pn]
	행렬 Ai의 크기: p(i-1) x p(i)
	반환값: (minimum_cost, split)
	시간복잡도: O(n^3)
	"""
	n = len(dimensions) - 1
	cost = [[0] * n for _ in range(n)]
	split = [[-1] * n for _ in range(n)]

	# length는 곱할 행렬 구간의 길이이다.
	for length in range(2, n + 1):
		for i in range(n - length + 1):
			j = i + length - 1
			cost[i][j] = INF

			for k in range(i, j):
				q = cost[i][k] + cost[k + 1][j] + dimensions[i] * dimensions[k + 1] * dimensions[j + 1]

				if (q < cost[i][j]):
					cost[i][j] = q
					split[i][j] = k

	return cost[0][n - 1], split


def build_parenthesization(split, i, j):
	# split 배열을 따라 최적 괄호 구조를 문자열로 만든다.
	# 시간복잡도: O(n)
	if (i == j):
		return "A" + str(i + 1)

	k = split[i][j]
	left = build_parenthesization(split, i, k)
	right = build_parenthesization(split, k + 1, j)
	return "(" + left + " x " + right + ")"
