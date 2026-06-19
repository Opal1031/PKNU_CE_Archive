"""
DFS (Depth-First Search) Traversal

깊이우선탐색은 한 정점에서 갈 수 있는 곳까지 깊게 들어간 뒤 되돌아온다.
연결 그래프에서는 시작 정점 기준 순회를, disconnected graph에서는 dfs_all로
모든 component를 순회할 수 있다.

V: 정점 수, E: 간선 수
DFS 시간복잡도: O(V + E)
"""


class Graph:
	def __init__(self, directed=False):
		self.directed = directed
		self.graph = {}

	# 인접 리스트로 그래프를 저장한다.
	# 시간복잡도: O(1)
	def add_vertex(self, vertex):
		if (vertex not in self.graph):
			self.graph[vertex] = []

	# 무방향 그래프면 양쪽 방향 간선을 모두 넣는다.
	# 시간복잡도: O(deg(source) + deg(target))
	def add_edge(self, source, target):
		self.add_vertex(source)
		self.add_vertex(target)

		if (target not in self.graph[source]):
			self.graph[source].append(target)

		if (not self.directed and source not in self.graph[target]):
			self.graph[target].append(source)

	# 특정 정점의 이웃 목록을 반환한다.
	# 시간복잡도: O(1)
	def neighbors(self, vertex):
		return self.graph.get(vertex, [])

	# DFS(G, v): 재귀적으로 방문을 수행한다.
	# visited는 호출자가 관리하는 딕셔너리로,
	# visited[v] = True이면 이미 방문한 상태이다.
	# 전체 DFS 과정에서 각 정점과 간선을 한 번씩 확인하므로 O(V + E)
	def _dfs_visit(self, v, visited, order):
		visited[v] = True
		order.append(v)

		for u in self.graph.get(v, []):
			if (not visited.get(u, False)):
				self._dfs_visit(u, visited, order)

	# DFS-ALL(G): 그래프의 모든 정점을 탐색한다 (disconnected 처리).
	# 시간복잡도: O(V + E)
	def dfs_all(self):
		# 모든 정점을 미방문(False)으로 초기화
		visited = {v: False for v in self.graph}
		order_all = []

		for v in self.graph:
			if (not visited[v]):
				self._dfs_visit(v, visited, order_all)

		return order_all

	# 시작 정점에서 깊이우선탐색을 수행하고 순회 순서를 반환한다.
	# 시간복잡도: O(V + E) (start에서 도달 가능한 부분 기준)
	def dfs(self, start):
		if (start not in self.graph):
			return []

		visited = {v: False for v in self.graph}
		order = []
		self._dfs_visit(start, visited, order)
		return order

	# 현재 그래프 상태를 보기 쉽게 출력한다.
	# 시간복잡도: O(V + E)
	def display(self):
		result = {}

		for vertex in self.graph:
			result[vertex] = list(self.graph[vertex])

		return result


if __name__ == "__main__":
	graph = Graph(directed=False)
	graph.add_edge("A", "B")
	graph.add_edge("A", "C")
	graph.add_edge("B", "D")
	graph.add_edge("B", "E")
	graph.add_edge("C", "F")
	graph.add_edge("E", "G")

	print(graph.display())
	print(graph.dfs("A"))
