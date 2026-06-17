"""
Maximum Sum Interval

연속된 구간(subarray) 중 합이 가장 큰 구간을 찾는다.
현재 위치에서 끝나는 최적해를 이용하는 Kadane 알고리즘으로 해결한다.

n: 배열 길이
시간복잡도: O(n)
"""


def maximum_sum_interval(arr):
	"""arr: 숫자 리스트
	반환값: (최대 합, 시작 index, 끝 index)
	시간복잡도: O(n)
	"""
	if (not arr):
		return 0, -1, -1

	best_sum = arr[0]
	current_sum = arr[0]
	best_start = 0
	best_end = 0
	current_start = 0

	for i in range(1, len(arr)):
		# 이전 구간을 이어가는 것보다 새로 시작하는 것이 크면 새 구간을 시작한다.
		if (current_sum + arr[i] < arr[i]):
			current_sum = arr[i]
			current_start = i
		else:
			current_sum += arr[i]

		if (best_sum < current_sum):
			best_sum = current_sum
			best_start = current_start
			best_end = i

	return best_sum, best_start, best_end
