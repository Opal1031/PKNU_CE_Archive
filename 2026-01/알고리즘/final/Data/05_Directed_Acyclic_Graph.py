"""
Directed Acyclic Graph (DAG) - Topological Sorts

두 가지 위상정렬 알고리즘을 구현합니다:
1) Kahn의 알고리즘 (진입차수 기반)
2) DFS 기반 위상정렬 (후위 순서 역전)

함수들은 그래프를 다음 형태로 받습니다:
graph: dict - 각 정점이 키, 값은 그 정점에서 나가는 인접 정점의 리스트

V: 정점 수, E: 간선 수
시간복잡도: O(V + E)
"""

from typing import Dict, List, Any


def kahn_topological_sort(graph: Dict[Any, List[Any]]) -> List[Any]:
	"""Kahn의 알고리즘을 사용한 위상정렬

	시간복잡도: O(V + E)

	graph: 정점 -> 인접 정점들의 리스트
	반환값: 위상정렬된 정점들의 리스트
	사이클(위상정렬 불가능)일 경우 ValueError를 발생시킵니다.
	"""
	# 모든 정점에 대해 진입차수를 0으로 초기화
	indeg = {u: 0 for u in graph}
	for u in graph:
		for v in graph[u]:
			if v not in indeg:
				indeg[v] = 0
			indeg[v] += 1

	# 진입차수 0인 정점들을 큐에 넣음 (list + index 방식으로 O(1) 암묵 pop)
	queue: List[Any] = [u for u, d in indeg.items() if d == 0]
	idx = 0
	topo_order: List[Any] = []

	while idx < len(queue):
		u = queue[idx]
		idx += 1
		topo_order.append(u)
		for v in graph.get(u, []):
			indeg[v] -= 1
			if indeg[v] == 0:
				queue.append(v)

	# 결과 길이가 정점 수와 다르면 사이클이 존재
	if len(topo_order) != len(indeg):
		raise ValueError("Graph has at least one cycle; topological sort not possible.")

	return topo_order


def dfs_topological_sort(graph: Dict[Any, List[Any]]) -> List[Any]:
	"""DFS 기반 위상정렬

	각 정점에 대해 DFS를 수행하여 방문 완료 시점에 스택에 추가하고,
	모든 정점을 처리한 뒤 스택을 역순으로 반환합니다.

	사이클이 발견되면 ValueError를 발생시킵니다.
	시간복잡도: O(V + E)
	"""
	visited = {}  # 0: unvisited, 1: visiting, 2: visited
	topo_stack: List[Any] = []

	def dfs(u: Any) -> None:
		state = visited.get(u, 0)
		if state == 1:
			# 되돌아오는 간선(back edge) -> 사이클
			raise ValueError("Graph has a cycle; topological sort not possible (back edge detected).")
		if state == 2:
			return

		visited[u] = 1
		for v in graph.get(u, []):
			dfs(v)
		visited[u] = 2
		topo_stack.append(u)

	# 그래프의 모든 정점을 순회
	for u in list(graph.keys()):
		if visited.get(u, 0) == 0:
			dfs(u)

	# 후위 순서로 쌓였으므로 역전하여 반환
	topo_stack.reverse()
	return topo_stack


if __name__ == "__main__":
	# 예시 DAG: (4)->(1), (4)->(0), (5)->(0), (5)->(2), (2)->(3), (3)->(1)
	example_graph = {
		5: [0, 2],
		4: [0, 1],
		2: [3],
		3: [1],
		0: [],
		1: [],
	}

	print("Example graph:")
	for u in sorted(example_graph):
		print(f"  {u} -> {example_graph[u]}")

	print("\nKahn's algorithm topological sort:")
	try:
		order_kahn = kahn_topological_sort(example_graph)
		print(order_kahn)
	except ValueError as e:
		print("Kahn failed:", e)

	print("\nDFS-based topological sort:")
	try:
		order_dfs = dfs_topological_sort(example_graph)
		print(order_dfs)
	except ValueError as e:
		print("DFS failed:", e)
