"""
Floyd-Warshall shortest path algorithm

모든 정점 쌍 사이의 최단 거리를 구합니다.
음수 가중치 간선은 허용하지만, 음수 사이클이 있으면 최단 거리를
정의할 수 없으므로 이를 검사합니다.

V: 정점 수, E: 간선 수
시간복잡도: O(V^3)
"""

INF = 10**18


def floyd_warshall(n, edges, directed=True):
	"""n: 정점 수 (0..n-1), edges: (u, v, w) 리스트
	directed: 방향 그래프 여부
	반환값: (distance, next_vertex)
	음수 사이클이 있으면 ValueError를 발생시킵니다.
	시간복잡도: O(V^3)
	"""
	distance = [[INF] * n for _ in range(n)]
	next_vertex = [[-1] * n for _ in range(n)]

	# 자기 자신까지의 거리는 0이다.
	for i in range(n):
		distance[i][i] = 0
		next_vertex[i][i] = i

	# 간선 정보를 거리 행렬에 반영한다.
	for u, v, w in edges:
		if (w < distance[u][v]):
			distance[u][v] = w
			next_vertex[u][v] = v

		if (not directed and w < distance[v][u]):
			distance[v][u] = w
			next_vertex[v][u] = u

	# k를 중간 정점으로 사용할 때 더 짧아지는 경로가 있는지 확인한다.
	for k in range(n):
		for i in range(n):
			for j in range(n):
				if (distance[i][k] == INF or distance[k][j] == INF):
					continue

				if (distance[i][j] > distance[i][k] + distance[k][j]):
					distance[i][j] = distance[i][k] + distance[k][j]
					next_vertex[i][j] = next_vertex[i][k]

	# distance[i][i]가 음수이면 i를 포함하는 음수 사이클이 존재한다.
	for i in range(n):
		if (distance[i][i] < 0):
			raise ValueError("Graph contains a negative weight cycle.")

	return distance, next_vertex


def shortest_path(next_vertex, start, target):
	# next_vertex를 따라 start에서 target까지의 경로를 복원한다.
	# 시간복잡도: O(V) (경로 길이에 비례)
	if (next_vertex[start][target] == -1):
		return None

	path = [start]
	current = start

	while (current != target):
		current = next_vertex[current][target]
		path.append(current)

	return path


def print_result(distance, next_vertex):
	# 모든 정점 쌍의 최단 거리와 경로를 출력한다.
	# 시간복잡도: O(V^3) (각 정점 쌍마다 경로를 복원할 수 있음)
	n = len(distance)

	for i in range(n):
		for j in range(n):
			if (distance[i][j] == INF):
				print(i, '->', j, ': unreachable')
			else:
				path = shortest_path(next_vertex, i, j)
				print(i, '->', j, ': distance =', distance[i][j], ', path =', path)
