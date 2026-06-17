"""
Longest Path in DAG

DAG(Directed Acyclic Graph)에서 시작 정점으로부터 각 정점까지의 최장 거리를 구한다.
일반 그래프의 최장 경로 문제는 어렵지만, DAG에서는 위상정렬 순서대로 DP를 적용할 수 있다.

V: 정점 수, E: 간선 수
시간복잡도: O(V + E)
"""

NEG_INF = -10**18


def topological_sort(n, edges):
	# 진입차수를 이용해 위상정렬 순서를 만든다.
	# 시간복잡도: O(V + E)
	graph = [[] for _ in range(n)]
	indegree = [0] * n

	for u, v, w in edges:
		graph[u].append((v, w))
		indegree[v] += 1

	queue = []
	for i in range(n):
		if (indegree[i] == 0):
			queue.append(i)

	order = []
	front = 0
	while (front < len(queue)):
		u = queue[front]
		front += 1
		order.append(u)

		for v, w in graph[u]:
			indegree[v] -= 1
			if (indegree[v] == 0):
				queue.append(v)

	if (len(order) != n):
		raise ValueError("Graph is not a DAG.")

	return order, graph


def longest_path_dag(n, edges, start):
	"""n: 정점 수 (0..n-1), edges: (u, v, w) 리스트
	start: 시작 정점
	반환값: (distance, previous)
	시간복잡도: O(V + E)
	"""
	order, graph = topological_sort(n, edges)
	distance = [NEG_INF] * n
	previous = [-1] * n
	distance[start] = 0

	# 위상정렬 순서대로 간선을 완화하면 최장 거리 DP가 된다.
	for u in order:
		if (distance[u] == NEG_INF):
			continue

		for v, w in graph[u]:
			if (distance[v] < distance[u] + w):
				distance[v] = distance[u] + w
				previous[v] = u

	return distance, previous


def longest_path(previous, start, target):
	# previous 배열을 따라 target에서 start까지 거꾸로 이동한다.
	# 시간복잡도: O(V)
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
