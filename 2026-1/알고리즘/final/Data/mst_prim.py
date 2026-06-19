"""
간단한 Prim 알고리즘 (O(n^2)) 구현
힙을 사용하지 않고 기초 문법(리스트와 반복문)만으로 구현했습니다.
아이디어:
 - 임의의 시작 정점에서 출발하여, 현재 트리에 인접한 최소 가중치 간선을 반복적으로 선택
 - 방문 여부와 각 정점까지의 최소 비용(key)를 관리

V: 정점 수, E: 간선 수
시간복잡도: O(V^2 + E) (인접 행렬 생성 O(V^2 + E), Prim 반복 O(V^2))
"""

INF = 10**18


def build_adj_matrix(n, edges):
	# 인접 행렬 형태로 변환. 존재하지 않는 간선은 INF
	# 시간복잡도: O(V^2 + E)
	mat = [[INF] * n for _ in range(n)]
	for u in range(n):
		mat[u][u] = 0
	for u, v, w in edges:
		# 무향 그래프
		if (w < mat[u][v]):
			mat[u][v] = w
			mat[v][u] = w
	return mat


def prim(n, edges, start=0):
	"""n: 정점 수, edges: (u,v,w) 리스트. 반환: (total, mst_edges)
	시간복잡도: O(V^2 + E)
	"""
	g = build_adj_matrix(n, edges)
	in_mst = [False] * n
	key = [INF] * n
	parent = [-1] * n

	key[start] = 0
	total = 0
	mst_edges = []

	for _ in range(n):
		# MST에 포함되지 않은 정점 중 key가 가장 작은 정점 선택 (선형 탐색)
		u = -1
		minv = INF
		for v in range(n):
			if ((not in_mst[v]) and (key[v] < minv)):
				minv = key[v]
				u = v
		if (u == -1):
			break
		in_mst[u] = True
		# 부모가 있으면 간선 추가
		if (parent[u] != -1):
			mst_edges.append((parent[u], u, g[parent[u]][u]))
			total += g[parent[u]][u]

		# 선택된 정점 u를 통해 key 갱신
		for v in range(n):
			if ((not in_mst[v]) and (g[u][v] < key[v])):
				key[v] = g[u][v]
				parent[v] = u

	return total, mst_edges

