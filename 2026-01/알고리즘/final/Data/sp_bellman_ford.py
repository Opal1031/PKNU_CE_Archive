"""
Bellman-Ford shortest path algorithm

가중치가 있는 방향 그래프에서 한 시작 정점으로부터 다른 모든 정점까지의
최단 거리를 구합니다. 음수 가중치 간선은 허용하지만, 음수 사이클이 있으면
최단 거리를 정의할 수 없으므로 이를 검사합니다.

V: 정점 수, E: 간선 수
시간복잡도: O(VE)
"""

INF = 10**18


def bellman_ford(n, edges, start):
	"""n: 정점 수 (0..n-1), edges: (u, v, w) 리스트
	start: 시작 정점
	반환값: (distance, previous)
	음수 사이클이 있으면 ValueError를 발생시킵니다.
	시간복잡도: O(VE)
	"""
	distance = [INF] * n
	previous = [-1] * n

	distance[start] = 0

	# 모든 간선을 n-1번 확인하며 최단 거리를 갱신한다.
	for _ in range(n - 1):
		updated = False

		for u, v, w in edges:
			# 아직 u에 도달할 수 없으면 이 간선으로는 갱신할 수 없다.
			if (distance[u] == INF):
				continue

			if (distance[v] > distance[u] + w):
				distance[v] = distance[u] + w
				previous[v] = u
				updated = True

		# 더 이상 갱신이 없으면 남은 반복은 생략한다.
		if (not updated):
			break

	# n-1번 이후에도 갱신된다면 시작 정점에서 도달 가능한 음수 사이클이 존재한다.
	for u, v, w in edges:
		if (distance[u] != INF and distance[v] > distance[u] + w):
			raise ValueError("Graph contains a negative weight cycle.")

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
