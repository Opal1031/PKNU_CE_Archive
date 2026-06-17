import random
import time

# 정렬되지 않은 배열 기반 최대 우선순위 큐
class ArrayMaxPQ:
	# 초기화
	def __init__(self):
		self.data = []

    # 삽입
	def add(self, value):
		self.data.append(value)

    # 최대값 추출
	def extract_max(self):
		max_idx = 0
		max_value = self.data[0]

		for i in range(1, len(self.data)):
			if (self.data[i] > max_value):
				max_value = self.data[i]
				max_idx = i

		last_idx = len(self.data) - 1
		self.data[max_idx], self.data[last_idx] = self.data[last_idx], self.data[max_idx]
		self.data.pop()
		
		return max_value

    # 큐가 비어있는지 확인
	def empty(self):
		return len(self.data) == 0

# 힙 기반 최대 우선순위 큐
class HeapMaxPQ:
	# 초기화
	def __init__(self):
		self.heap = []

    # 삽입
	def add(self, value):
		self.heap.append(value)
		self._up(len(self.heap) - 1)

    # 최대값 추출
	def extract_max(self):
		max_value = self.heap[0]
		last = self.heap.pop()

		if self.heap:
			self.heap[0] = last
			self._down(0)

		return max_value

    # 큐가 비어있는지 확인
	def empty(self):
		return len(self.heap) == 0

    # 힙 속성 유지 위해 위로 이동
	def _up(self, idx):
		while (idx > 0):
			parent = (idx - 1) // 2

			if self.heap[idx] > self.heap[parent]:
				self.heap[idx], self.heap[parent] = self.heap[parent], self.heap[idx]
				idx = parent
				
			else:
				break

    # 힙 속성 유지 위해 아래로 이동
	def _down(self, idx):
		n = len(self.heap)

		while True:
			left = 2 * idx + 1
			right = 2 * idx + 2
			largest = idx

			if (left < n and self.heap[left] > self.heap[largest]):
				largest = left

			if (right < n and self.heap[right] > self.heap[largest]):
				largest = right

			if (largest == idx):
				break

			self.heap[idx], self.heap[largest] = self.heap[largest], self.heap[idx]
			idx = largest

# 우선순위 큐 연산 시간 측정
def MeasurePQTime(pq, initial_values, action_coins, action_values):
	for value in initial_values:
		pq.add(value)

	start = time.perf_counter()

    # action_coins[i]가 0이면 action_values[i]를 삽입, 1이면 최대값 추출
	for i in range(m):
		coin = action_coins[i]
		value = action_values[i]

		if (coin == 0):
			pq.add(value)
			
		else:
			pq.extract_max()

	end = time.perf_counter()
	
	return end - start

n = 100000
m = 100000

initial_values = [random.randint(0, n) for _ in range(n)]
action_coins = [random.randint(0, 1) for _ in range(m)]
action_values = [random.randint(0, n) for _ in range(m)]

array_time = MeasurePQTime(ArrayMaxPQ(), initial_values, action_coins, action_values)
heap_time = MeasurePQTime(HeapMaxPQ(), initial_values, action_coins, action_values)

print(f"N = {n}, M = {m}")
print("\n최대 우선순위 큐 구현별 실행 시간(초):")
print(f"배열 기반 구현: {array_time:.6f}초")
print(f"힙 기반 구현: {heap_time:.6f}초")