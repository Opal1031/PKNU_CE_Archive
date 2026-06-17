"""
Shortest Path demo

Bellman-Ford, Dijkstra, Floyd-Warshall을 각각 예제 그래프에 실행한다.
Bellman-Ford: 음수 가중치 간선이 있어도 사용 가능하다.
Dijkstra: 음수 가중치 간선이 없을 때 사용한다.
Floyd-Warshall: 모든 정점 쌍 사이의 최단 거리를 구한다.

Bellman-Ford 시간복잡도: O(VE)
Dijkstra 시간복잡도: O((V + E) log V) (heapq 사용)
Floyd-Warshall 시간복잡도: O(V^3)
"""

from sp_bellman_ford import bellman_ford
from sp_bellman_ford import print_result as print_bellman_ford_result
from sp_dijkstra import dijkstra
from sp_dijkstra import print_result as print_dijkstra_result
from sp_floyd_warshall import floyd_warshall
from sp_floyd_warshall import print_result as print_floyd_warshall_result


def demo():
	# Bellman-Ford 예제 그래프 (음수 가중치 간선 포함 가능)
	n_b = 5
	edges_b = [
		(0, 1, 6), (0, 2, 7),
		(1, 2, 8), (1, 3, 5), (1, 4, -4),
		(2, 3, -3), (2, 4, 9),
		(3, 1, -2),
		(4, 0, 2), (4, 3, 7),
	]
	start_b = 0

	print('--- Demo graph Shortest Path ---')
	# Bellman-Ford 실행
	try:
		distance_b, previous_b = bellman_ford(n_b, edges_b, start_b)
		print('Bellman-Ford result:')
		print_bellman_ford_result(distance_b, previous_b, start_b)
	except ValueError as e:
		print('Bellman-Ford failed:', e)

	# Dijkstra 예제 그래프 (음수 가중치 간선 없음)
	n_d = 6
	edges_d = [
		(0, 1, 4), (0, 2, 2),
		(1, 2, 1), (1, 3, 5),
		(2, 1, 1), (2, 3, 8), (2, 4, 10),
		(3, 4, 2), (3, 5, 6),
		(4, 5, 3),
	]
	start_d = 0

	# Dijkstra 실행
	try:
		distance_d, previous_d = dijkstra(n_d, edges_d, start_d)
		print('\nDijkstra result:')
		print_dijkstra_result(distance_d, previous_d, start_d)
	except ValueError as e:
		print('Dijkstra failed:', e)

	# Floyd-Warshall 예제 그래프 (모든 정점 쌍 최단 거리)
	n_f = 4
	edges_f = [
		(0, 1, 5), (0, 3, 10),
		(1, 2, 3),
		(2, 3, 1),
		(3, 0, 2),
	]

	# Floyd-Warshall 실행
	try:
		distance_f, next_vertex_f = floyd_warshall(n_f, edges_f)
		print('\nFloyd-Warshall result:')
		print_floyd_warshall_result(distance_f, next_vertex_f)
	except ValueError as e:
		print('Floyd-Warshall failed:', e)


if (__name__ == "__main__"):
	demo()
