"""
Dijkstra shortest path algorithm

가중치가 있는 그래프에서 한 시작 정점으로부터 다른 모든 정점까지의
최단 거리를 구합니다. 단, 다익스트라 알고리즘은 음수 가중치 간선이
없는 경우에만 사용할 수 있습니다.

V: 정점 수, E: 간선 수
시간복잡도: O((V + E) log V) (heapq 사용)
"""

import heapq


INF = 10**18


def build_graph(n, edges, directed=True):
	# edges 리스트를 인접 리스트 형태로 변환한다.
	# 시간복잡도: O(V + E)
	graph = [[] for _ in range(n)]

	for u, v, w in edges:
		if (w < 0):
			raise ValueError("Dijkstra cannot use negative weight edges.")

		graph[u].append((v, w))

		if (not directed):
			graph[v].append((u, w))

	return graph


def dijkstra(n, edges, start, directed=True):
	"""n: 정점 수 (0..n-1), edges: (u, v, w) 리스트
	start: 시작 정점
	directed: 방향 그래프 여부
	반환값: (distance, previous)
	시간복잡도: O((V + E) log V)
	"""
	graph = build_graph(n, edges, directed)
	distance = [INF] * n
	previous = [-1] * n

	distance[start] = 0
	heap = [(0, start)]

	while (heap):
		current_distance, u = heapq.heappop(heap)

		# 이미 더 짧은 거리로 처리된 정점이면 건너뛴다.
		if (current_distance > distance[u]):
			continue

		for v, w in graph[u]:
			new_distance = distance[u] + w

			if (distance[v] > new_distance):
				distance[v] = new_distance
				previous[v] = u
				heapq.heappush(heap, (new_distance, v))

	return distance, previous


def shortest_path(previous, start, target):
	# previous 배열을 따라 target에서 start까지 거꾸로 이동한다.
	# 시간복잡도: O(V) (경로 길이에 비례)
	path = []
	current = target

	while (current != -1):
		path.append(current)
		if (current == start):
			break
		current = previous[current]

	if (not path or path[-1] != start):
		return None

	path.reverse()
	return path


def print_result(distance, previous, start):
	# 모든 정점의 최단 거리와 경로를 출력한다.
	# 시간복잡도: O(V^2) (각 정점마다 경로를 복원할 수 있음)
	for vertex in range(len(distance)):
		if (distance[vertex] == INF):
			print(start, '->', vertex, ': unreachable')
		else:
			path = shortest_path(previous, start, vertex)
			print(start, '->', vertex, ': distance =', distance[vertex], ', path =', path)
