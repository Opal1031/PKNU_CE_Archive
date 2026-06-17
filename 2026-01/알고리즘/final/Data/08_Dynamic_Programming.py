"""
Dynamic Programming demo

Longest Path in DAG 시간복잡도: O(V + E)
Matrix Chain Multiplication 시간복잡도: O(n^3)
LCS 시간복잡도: O(nm)
Maximum Sum Interval 시간복잡도: O(n)
0/1 Knapsack 시간복잡도: O(nW)
Weighted Interval Scheduling 시간복잡도: O(n log n)
"""

from dp_longest_path import longest_path_dag
from dp_longest_path import longest_path
from dp_matrix_chain import matrix_chain_order
from dp_matrix_chain import build_parenthesization
from dp_lcs import lcs
from dp_maximum_sum_interval import maximum_sum_interval
from dp_knapsack import knapsack_01
from dp_weighted_interval_scheduling import weighted_interval_scheduling


def demo_longest_path():
	# DAG 최장경로 예제: (출발 정점, 도착 정점, 가중치)
	n = 6
	edges = [
		(0, 1, 5), (0, 2, 3),
		(1, 3, 6), (1, 2, 2),
		(2, 4, 4), (2, 5, 2), (2, 3, 7),
		(3, 5, 1), (3, 4, -1),
		(4, 5, -2),
	]
	start = 0
	distance, previous = longest_path_dag(n, edges, start)

	print('Longest Path in DAG:')
	for vertex in range(n):
		path = longest_path(previous, start, vertex)
		print(start, '->', vertex, ': distance =', distance[vertex], ', path =', path)


def demo_matrix_chain():
	# A1: 30x35, A2: 35x15, A3: 15x5, ...
	dimensions = [30, 35, 15, 5, 10, 20, 25]
	minimum_cost, split = matrix_chain_order(dimensions)
	parenthesization = build_parenthesization(split, 0, len(dimensions) - 2)

	print('\nMatrix Chain Multiplication:')
	print('minimum cost:', minimum_cost)
	print('parenthesization:', parenthesization)


def demo_lcs():
	a = "ABCBDAB"
	b = "BDCABA"
	length, sequence = lcs(a, b)

	print('\nLCS:')
	print('A:', a)
	print('B:', b)
	print('length:', length)
	print('sequence:', sequence)


def demo_maximum_sum_interval():
	arr = [-2, 1, -3, 4, -1, 2, 1, -5, 4]
	best_sum, start, end = maximum_sum_interval(arr)

	print('\nMaximum Sum Interval:')
	print('array:', arr)
	print('maximum sum:', best_sum)
	print('interval:', arr[start:end + 1], 'index =', (start, end))


def demo_knapsack():
	weights = [2, 3, 4, 5]
	values = [3, 4, 5, 6]
	capacity = 5
	max_value, selected = knapsack_01(weights, values, capacity)

	print('\n0/1 Knapsack:')
	print('weights:', weights)
	print('values:', values)
	print('capacity:', capacity)
	print('maximum value:', max_value)
	print('selected item indexes:', selected)


def demo_weighted_interval_scheduling():
	# 구간은 (시작 시간, 끝나는 시간, 가중치) 형태이다.
	intervals = [
		(1, 4, 3), (3, 5, 2), (0, 6, 4),
		(4, 7, 4), (3, 9, 6), (5, 9, 3),
		(6, 10, 8), (8, 11, 5),
	]
	max_weight, selected = weighted_interval_scheduling(intervals)

	print('\nWeighted Interval Scheduling:')
	print('maximum weight:', max_weight)
	print('selected intervals:', selected)


def demo():
	print('--- Demo Dynamic Programming ---')
	demo_longest_path()
	demo_matrix_chain()
	demo_lcs()
	demo_maximum_sum_interval()
	demo_knapsack()
	demo_weighted_interval_scheduling()


if (__name__ == "__main__"):
	demo()
