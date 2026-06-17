"""
Weighted Interval Scheduling

겹치지 않는 구간들 중 가중치 합이 최대가 되는 집합을 선택한다.
끝나는 시간 기준으로 정렬한 뒤, 각 구간 i와 겹치지 않는 마지막 구간 p[i]를 이용한다.

n: 구간 수
시간복잡도: O(n log n)
"""


def binary_search_previous(intervals, index):
	# index번째 구간과 겹치지 않으면서 가장 늦게 끝나는 구간을 찾는다.
	# 시간복잡도: O(log n)
	start = intervals[index][0]
	left = 0
	right = index - 1
	answer = -1

	while (left <= right):
		mid = (left + right) // 2
		if (intervals[mid][1] <= start):
			answer = mid
			left = mid + 1
		else:
			right = mid - 1

	return answer


def weighted_interval_scheduling(intervals):
	"""intervals: (start, finish, weight) 리스트
	반환값: (최대 가중치, 선택된 구간 리스트)
	시간복잡도: O(n log n)
	"""
	intervals_sorted = sorted(intervals, key=lambda x: x[1])
	n = len(intervals_sorted)
	p = [-1] * n

	for i in range(n):
		p[i] = binary_search_previous(intervals_sorted, i)

	dp = [0] * (n + 1)
	for i in range(1, n + 1):
		weight = intervals_sorted[i - 1][2]
		include = weight + dp[p[i - 1] + 1]
		exclude = dp[i - 1]
		dp[i] = max(include, exclude)

	# dp 값을 따라가며 실제 선택된 구간을 복원한다.
	selected = []
	i = n
	while (i > 0):
		weight = intervals_sorted[i - 1][2]
		include = weight + dp[p[i - 1] + 1]

		if (include > dp[i - 1]):
			selected.append(intervals_sorted[i - 1])
			i = p[i - 1] + 1
		else:
			i -= 1

	selected.reverse()
	return dp[n], selected
