"""
BFS (Breadth-First Search) Shortest Path

가중치가 없는 그래프에서 시작 정점으로부터 각 정점까지의 최단 간선 수를 구한다.
큐를 사용해서 가까운 정점부터 방문한다.

V: 정점 수, E: 간선 수
BFS 시간복잡도: O(V + E)
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

	# BFS는 d와 pi를 사용해 순회 순서, 거리, 선행자를 모두 구한다.
	# 시간복잡도: O(V + E)
	def bfs(self, start):
		if (start not in self.graph):
			return [], {}, {}

		distance = {}
		previous = {}

		# 처음에는 모든 정점을 미방문(-1) 상태로 둔다.
		for vertex in self.graph:
			distance[vertex] = -1
			previous[vertex] = None

		distance[start] = 0
		# 파이썬 리스트를 큐처럼 사용한다. pop(0)을 쓰지 않기 위해 앞 인덱스 `front`를 둔다.
		queue = [start]
		front = 0
		order = []

		while (front < len(queue)):
			vertex = queue[front]
			front += 1
			order.append(vertex)

			for neighbor in self.graph[vertex]:
				# 아직 방문하지 않은(거리=-1) 이웃이면 거리와 선행자를 기록하고 큐에 넣는다.
				if (distance[neighbor] == -1):
					distance[neighbor] = distance[vertex] + 1
					previous[neighbor] = vertex
					queue.append(neighbor)

		return order, distance, previous

	# BFS에서 얻은 pi를 따라 최단 경로를 복원한다.
	# 시간복잡도: O(V) (경로 길이에 비례)
	def shortest_path(self, start, goal):
		if (start not in self.graph or goal not in self.graph):
			return None

		_, distance, previous = self.bfs(start)

		if (goal not in previous):
			return None

		if (distance[goal] == -1):
			return None

		# goal에서 start로 선행자(previous)를 따라가며 경로를 복원한다.
		path = []
		current = goal

		while (current is not None):
			path.append(current)
			current = previous[current]

		path.reverse()
		return path

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
	graph.add_edge("C", "E")
	graph.add_edge("D", "F")
	graph.add_edge("E", "F")

	# BFS 순회, 거리, 선행자 확인
	print(graph.display())
	print(graph.bfs("A"))
	print(graph.shortest_path("A", "F"))
