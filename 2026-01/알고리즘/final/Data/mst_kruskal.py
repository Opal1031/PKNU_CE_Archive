"""
간단한 Kruskal 알고리즘 구현
주요 아이디어:
1) 모든 정점을 서로 다른 집합으로 초기화 (MAKE-SET)
2) 간선들을 가중치가 작은 것부터 정렬
3) 간선을 하나씩 보면서 두 정점이 서로 다른 집합이면 선택하고 UNION

V: 정점 수, E: 간선 수
시간복잡도: O(E log E) (간선 정렬이 가장 큰 비용)
"""


class DSU:
	# Disjoint Set Union: 서로소 집합을 관리하여 cycle 생성을 빠르게 확인한다.
	def __init__(self, n, union_by='rank', verbose=False):
		# parent[i]는 i의 부모 노드 (초기에는 자신)
		self.parent = list(range(n))
		# rank 또는 size를 선택적으로 사용
		self.union_by = union_by
		self.verbose = verbose
		self.rank = [0] * n
		self.size = [1] * n

	# x가 속한 집합의 대표(root)를 찾는다.
	# 경로 압축을 사용하면 거의 O(1)에 가깝게 동작한다.
	def find(self, x):
		# 경로 압축을 사용한 find
		if (self.parent[x] != x):
			self.parent[x] = self.find(self.parent[x])
		return self.parent[x]

	# 두 정점이 속한 집합을 합친다.
	# 이미 같은 집합이면 cycle이 생기므로 False를 반환한다.
	def union(self, a, b):
		# 두 집합을 합침. 합쳐졌으면 True, 이미 같은 집합이면 False
		ra = self.find(a)
		rb = self.find(b)
		if (ra == rb):
			if (self.verbose):
				print(f"union({a},{b}) -> already same root {ra}")
			return False

		# union by size 또는 rank 중 선택
		if (self.union_by == 'size'):
			# 작은 트리를 큰 트리 아래로 붙임
			if (self.size[ra] < self.size[rb]):
				ra, rb = rb, ra
			self.parent[rb] = ra
			self.size[ra] += self.size[rb]
		else:
			# 기본: union by rank
			if (self.rank[ra] < self.rank[rb]):
				ra, rb = rb, ra
			self.parent[rb] = ra
			if (self.rank[ra] == self.rank[rb]):
				self.rank[ra] += 1

		if (self.verbose):
			print(f"union({a},{b}) -> root {ra} absorbs {rb}")
			print(' parent:', self.parent)
			if (self.union_by == 'size'):
				print(' size:  ', self.size)
			else:
				print(' rank:  ', self.rank)
		return True


def kruskal(n, edges, union_by='rank', verbose=False):
	"""n: 정점 수 (0..n-1), edges: (u, v, w) 리스트
	union_by: 'rank' or 'size'
	verbose: if True, DSU prints union steps
	반환값: (total_weight, mst_edges 리스트)
	시간복잡도: O(E log E)
	"""
	dsu = DSU(n, union_by=union_by, verbose=verbose)
	# 가중치 오름차순 정렬
	edges_sorted = sorted(edges, key=lambda x: x[2])
	mst = []
	total = 0
	for u, v, w in edges_sorted:
		# 서로 다른 집합이면 간선 선택 (union 내부에서 find 수행)
		if (dsu.union(u, v)):
			mst.append((u, v, w))
			total += w
			if (len(mst) == n - 1):
				break
	return total, mst

