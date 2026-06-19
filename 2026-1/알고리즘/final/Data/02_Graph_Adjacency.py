"""
Graph Adjacency Representation

그래프를 저장하는 대표적인 두 방식:
1) Adjacency List: 각 정점마다 연결된 이웃 목록을 저장
2) Adjacency Matrix: 정점 쌍마다 간선 존재 여부를 2차원 배열에 저장

V: 정점 수, E: 간선 수
"""


class AdjacencyListGraph:
	# 인접 리스트는 공간복잡도 O(V + E)로 sparse graph에 유리하다.
	def __init__(self, directed=False):
		self.directed = directed
		self.graph = {}

	# 정점은 딕셔너리, 간선은 인접 리스트로 저장한다.
	# 평균 시간복잡도: O(1)
	def add_vertex(self, vertex):
		if (vertex not in self.graph):
			self.graph[vertex] = []

	# 간선을 추가하고, 무방향 그래프면 반대 방향도 함께 넣는다.
	# 시간복잡도: O(deg(source) + deg(target))
	def add_edge(self, source, target):
		self.add_vertex(source)
		self.add_vertex(target)

		if (target not in self.graph[source]):
			self.graph[source].append(target)

		if (not self.directed and source not in self.graph[target]):
			self.graph[target].append(source)

	# 간선을 제거할 때는 무방향 그래프의 역방향도 같이 지운다.
	# 시간복잡도: O(deg(source) + deg(target))
	def remove_edge(self, source, target):
		if (source in self.graph and target in self.graph[source]):
			self.graph[source].remove(target)

		if (not self.directed and target in self.graph and source in self.graph[target]):
			self.graph[target].remove(source)

	# 정점을 지우기 전에 연결된 모든 간선을 먼저 제거한다.
	# 시간복잡도: O(V + E)
	def remove_vertex(self, vertex):
		if (vertex not in self.graph):
			return

		for neighbor in list(self.graph[vertex]):
			self.remove_edge(vertex, neighbor)

		if (vertex in self.graph):
			del self.graph[vertex]

		for neighbors in self.graph.values():
			if (vertex in neighbors):
				neighbors.remove(vertex)

	# 특정 정점에 연결된 이웃 정점들을 돌려준다.
	# 시간복잡도: O(1)
	def neighbors(self, vertex):
		return self.graph.get(vertex, [])

	# 현재 인접 리스트 전체를 보기 쉬운 형태로 반환한다.
	# 시간복잡도: O(V + E)
	def display(self):
		result = {}

		for vertex in self.graph:
			result[vertex] = list(self.graph[vertex])

		return result


class AdjacencyMatrixGraph:
	# 인접 행렬은 공간복잡도 O(V^2), 간선 존재 확인은 O(1)이다.
	def __init__(self, vertices=None, directed=False, weighted=False):
		self.directed = directed
		self.weighted = weighted
		self.vertices = []
		self.index = {}
		self.matrix = []

		if (vertices is not None):
			for vertex in vertices:
				self.add_vertex(vertex)

	# 새 정점을 추가하면 행과 열을 하나씩 늘린다.
	# 시간복잡도: O(V)
	def add_vertex(self, vertex):
		if (vertex in self.index):
			return

		self.index[vertex] = len(self.vertices)
		self.vertices.append(vertex)

		for row in self.matrix:
			row.append(0)

		self.matrix.append([0 for _ in range(len(self.vertices))])

	# 가중치 그래프면 가중치를 쓰고, 아니면 1로 저장한다.
	def _edge_value(self, weight):
		if (self.weighted):
			return weight

		return 1

	# 인접 행렬의 해당 칸에 값을 넣는다.
	# 시간복잡도: O(1) (새 정점 추가가 필요하면 O(V))
	def add_edge(self, source, target, weight=1):
		self.add_vertex(source)
		self.add_vertex(target)

		source_index = self.index[source]
		target_index = self.index[target]
		value = self._edge_value(weight)

		self.matrix[source_index][target_index] = value

		if (not self.directed):
			self.matrix[target_index][source_index] = value

	# 간선이 있으면 해당 칸을 0으로 되돌린다.
	# 시간복잡도: O(1)
	def remove_edge(self, source, target):
		if (source not in self.index or target not in self.index):
			return

		source_index = self.index[source]
		target_index = self.index[target]

		self.matrix[source_index][target_index] = 0

		if (not self.directed):
			self.matrix[target_index][source_index] = 0

	# 두 정점 사이에 간선이 있는지 확인한다.
	# 시간복잡도: O(1)
	def has_edge(self, source, target):
		if (source not in self.index or target not in self.index):
			return False

		return self.matrix[self.index[source]][self.index[target]] != 0

	# 행렬에서 0이 아닌 값들을 이웃 정점으로 모은다.
	# 시간복잡도: O(V)
	def neighbors(self, vertex):
		if (vertex not in self.index):
			return []

		vertex_index = self.index[vertex]
		neighbors = []

		for target_index, value in enumerate(self.matrix[vertex_index]):
			if (value != 0):
				neighbors.append(self.vertices[target_index])

		return neighbors

	# 정점 목록과 행렬을 함께 반환한다.
	# 시간복잡도: O(V^2)
	def display(self):
		return {
			"vertices": list(self.vertices),
			"matrix": [list(row) for row in self.matrix],
		}


if __name__ == "__main__":
	list_graph = AdjacencyListGraph(directed=False)
	list_graph.add_edge("A", "B")
	list_graph.add_edge("A", "C")
	list_graph.add_edge("B", "D")
	print(list_graph.display())
	print(list_graph.neighbors("A"))

	# 인접 행렬 예시
	matrix_graph = AdjacencyMatrixGraph(directed=False, weighted=False)
	matrix_graph.add_edge("A", "B")
	matrix_graph.add_edge("A", "C")
	matrix_graph.add_edge("B", "D")
	print(matrix_graph.display())
	print(matrix_graph.neighbors("A"))
