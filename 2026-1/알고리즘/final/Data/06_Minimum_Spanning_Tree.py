"""
Minimum Spanning Tree demo

Kruskal과 Prim을 같은 그래프에 실행해 MST 결과를 비교한다.
V: 정점 수, E: 간선 수
Kruskal 시간복잡도: O(E log E)
Prim 시간복잡도: O(V^2 + E)
"""

from mst_kruskal import kruskal
from mst_prim import prim


def demo():
	# 예제 그래프 (정점 수, 간선 리스트)
	n = 6
	edges = [
		(0, 1, 4), (0, 2, 4), (1, 2, 2), (1, 3, 5),
		(2, 3, 5), (2, 4, 11), (3, 4, 2), (3, 5, 1), (4, 5, 7),
	]

	print('--- Demo graph MST ---')
	# Kruskal 실행
	total_k, mst_k = kruskal(n, edges)
	print('Kruskal weight:', total_k)
	for u, v, w in mst_k:
		print(u, '-', v, ':', w)

	# Prim 실행 (mst_prim의 prim은 edges를 직접 받음)
	total_p, mst_p = prim(n, edges)
	print('\nPrim weight:', total_p)
	for u, v, w in mst_p:
		print(u, '-', v, ':', w)


if (__name__ == "__main__"):
	demo()
