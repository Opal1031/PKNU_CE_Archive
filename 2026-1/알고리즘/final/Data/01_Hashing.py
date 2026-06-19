"""
Hashing

해시 테이블은 key를 해시 함수로 배열의 index에 대응시켜 저장한다.
충돌이 발생하면 Chaining 또는 Open Addressing 방식으로 해결한다.

평균 시간복잡도: search/insert/delete = O(1)
최악 시간복잡도: search/insert/delete = O(n)
"""


class ChainNode:
	def __init__(self, key, value=None, next_node=None):
		self.key = key
		self.value = key if (value is None) else value
		self.next = next_node

class ChainingHashTable:
	# Chaining: 같은 index에 여러 key가 들어오면 연결 리스트로 저장한다.
	def __init__(self, size=11, hash_method="division"):
		self.size = size
		self.hash_method = hash_method
		self.table = [None for _ in range(size)]

	# division 기법은 해시값을 테이블 크기로 나눈 나머지를 사용한다.
	def _division_hash(self, key):
		return hash(key) % self.size

	# multiplication 기법은 황금비 기반 상수를 이용해 분포를 만든다.
	def _multiplication_hash(self, key):
		constant = 0.6180339887
		normalized = abs(hash(key))
		fraction = (normalized * constant) % 1
		return int(self.size * fraction)

	# 선택한 기법에 따라 실제 해시값을 구한다.
	def _hash(self, key):
		if (self.hash_method == "multiplication"):
			return self._multiplication_hash(key)

		return self._division_hash(key)

	# 같은 주소에 들어온 값은 연결 리스트로 이어 붙인다.
	# 평균 시간복잡도: O(1), 최악 시간복잡도: O(n)
	def insert(self, key, value=None):
		index = self._hash(key)
		node = self.table[index]

		while (node is not None):
			if (node.key == key):
				node.value = key if (value is None) else value
				return True

			node = node.next

		self.table[index] = ChainNode(key, value, self.table[index])
		return True

	# key가 들어갈 bucket만 확인한 뒤 연결 리스트를 따라 탐색한다.
	# 평균 시간복잡도: O(1), 최악 시간복잡도: O(n)
	def search(self, key):
		index = self._hash(key)
		node = self.table[index]

		while (node is not None):
			if (node.key == key):
				return node.value

			node = node.next

		return None

	# 연결 리스트에서 key를 찾아 앞뒤 연결을 바꿔 삭제한다.
	# 평균 시간복잡도: O(1), 최악 시간복잡도: O(n)
	def delete(self, key):
		index = self._hash(key)
		node = self.table[index]
		previous = None

		while (node is not None):
			if (node.key == key):
				if (previous is None):
					self.table[index] = node.next

				else:
					previous.next = node.next

				return True

			previous = node
			node = node.next

		return False

	# 전체 table을 출력용 리스트로 바꾼다.
	# 시간복잡도: O(n + m) (n: table 크기, m: 저장된 원소 수)
	def display(self):
		result = []

		for index in range(self.size):
			node = self.table[index]
			bucket = []

			while (node is not None):
				bucket.append((node.key, node.value))
				node = node.next

			result.append(bucket)

		return result

class OpenAddressingHashTable:
	# Open Addressing: 충돌이 나면 정해진 규칙으로 다음 위치를 탐사한다.
	EMPTY = object()
	DELETED = object()

	def __init__(self, size=11, hash_method="division"):
		self.size = size
		self.hash_method = hash_method
		self.table = [self.EMPTY for _ in range(size)]

	# division 기법은 해시값을 테이블 크기로 나눈 나머지를 사용한다.
	def _division_hash(self, key):
		return hash(key) % self.size

	# multiplication 기법은 황금비 기반 상수를 이용해 분포를 만든다.
	def _multiplication_hash(self, key):
		constant = 0.6180339887
		normalized = abs(hash(key))
		fraction = (normalized * constant) % 1
		return int(self.size * fraction)

	def _hash(self, key):
		if (self.hash_method == "multiplication"):
			return self._multiplication_hash(key)

		return self._division_hash(key)

	# probing 간격은 자식 클래스에서 필요에 맞게 바꾼다.
	def _step(self, key):
		return 1

	# i번째 탐사 위치를 계산한다.
	def _probe(self, key, i):
		return (self._hash(key) + i * self._step(key)) % self.size

	# 빈 칸이나 삭제 칸을 찾아 값을 넣는다.
	# 평균 시간복잡도: O(1), 최악 시간복잡도: O(n)
	def insert(self, key, value=None):
		first_deleted = None

		for i in range(self.size):
			index = self._probe(key, i)
			slot = self.table[index]

			if (slot is self.EMPTY):
				if (first_deleted is not None):
					index = first_deleted

				self.table[index] = (key, key if (value is None) else value)
				return True

			if (slot is self.DELETED):
				if (first_deleted is None):
					first_deleted = index

			elif (slot[0] == key):
				self.table[index] = (key, key if (value is None) else value)
				return True

		if (first_deleted is not None):
			self.table[first_deleted] = (key, key if (value is None) else value)
			return True

		return False

	# probing 순서대로 key를 찾고, EMPTY를 만나면 탐색을 종료한다.
	# 평균 시간복잡도: O(1), 최악 시간복잡도: O(n)
	def search(self, key):
		# 빈 칸을 만나면 더 이상 탐색할 필요가 없다.
		for i in range(self.size):
			index = self._probe(key, i)
			slot = self.table[index]

			if (slot is self.EMPTY):
				return None

			if (slot is not self.DELETED and slot[0] == key):
				return slot[1]

		return None

	# 실제 삭제 대신 DELETED 표식을 남겨 뒤쪽 원소의 탐색 경로를 유지한다.
	# 평균 시간복잡도: O(1), 최악 시간복잡도: O(n)
	def delete(self, key):
		# 삭제된 칸은 DELETED 표식으로 남겨 탐사 경로를 유지한다.
		for i in range(self.size):
			index = self._probe(key, i)
			slot = self.table[index]

			if (slot is self.EMPTY):
				return False

			if (slot is not self.DELETED and slot[0] == key):
				self.table[index] = self.DELETED
				return True

		return False

	# 전체 table을 출력용 리스트로 바꾼다.
	# 시간복잡도: O(n)
	def display(self):
		result = []

		for slot in self.table:
			if (slot is self.EMPTY):
				result.append(None)

			elif (slot is self.DELETED):
				result.append("DELETED")

			else:
				result.append(slot)

		return result

class LinearProbingHashTable(OpenAddressingHashTable):
	# 선형 탐사: 한 칸씩 순서대로 이동한다.
	# i번째 위치: h(k) + i
	def _probe(self, key, i):
		return (self._hash(key) + i) % self.size


class QuadraticProbingHashTable(OpenAddressingHashTable):
	# 이차 탐사: 이동 거리를 제곱으로 늘린다.
	# i번째 위치: h(k) + i^2
	def _probe(self, key, i):
		return (self._hash(key) + i * i) % self.size


class DoubleHashingHashTable(OpenAddressingHashTable):
	# 두 번째 해시값을 탐사 간격으로 사용한다.
	# i번째 위치: h1(k) + i * h2(k)
	def _step(self, key):
		if (self.size <= 1):
			return 1

		return 1 + (hash(key) % (self.size - 1))

	def _probe(self, key, i):
		return (self._hash(key) + i * self._step(key)) % self.size


if __name__ == "__main__":
	chain_table = ChainingHashTable(size=7)
	chain_table.insert(10)
	chain_table.insert(17)
	print(chain_table.display())
	print(chain_table.search(17))

	linear_table = LinearProbingHashTable(size=7)
	linear_table.insert(10)
	linear_table.insert(17)
	print(linear_table.display())
	print(linear_table.search(10))

	quadratic_table = QuadraticProbingHashTable(size=7)
	quadratic_table.insert(10)
	quadratic_table.insert(17)
	print(quadratic_table.display())
	print(quadratic_table.search(17))

	double_table = DoubleHashingHashTable(size=7)
	double_table.insert(10)
	double_table.insert(17)
	print(double_table.display())
	print(double_table.search(10))
