RED = "RED"
BLACK = "BLACK"

class Node:
	def __init__(self, key=None, color=BLACK, left=None, right=None, parent=None, is_nil=False):
		self.key = key
		self.color = color
		self.left = left
		self.right = right
		self.parent = parent
		self.is_nil = is_nil

class RedBlackTree:
	def __init__(self):
		# 단일 NIL 센티널 노드: 모든 리프와 루트의 부모가 이 노드를 가리킨다.
		self.NIL = Node(is_nil=True, color=BLACK)
		self.NIL.left = self.NIL
		self.NIL.right = self.NIL
		self.NIL.parent = self.NIL
		self.root = self.NIL

	# search 시간복잡도: O(log n) - 트리 높이에 비례
	def search(self, key):
		# 이진 탐색트리의 성질을 이용해 키를 찾는다.
		node = self.root

		while (node != self.NIL and node.key != key):
			if (key < node.key):
				node = node.left

			else:
				node = node.right

		return None if (node == self.NIL) else node

    # left_rotate 시간복잡도: O(1)
	def left_rotate(self, x):
		# x를 기준으로 왼쪽 회전을 수행한다.
		y = x.right
		x.right = y.left

		if (y.left != self.NIL):
			y.left.parent = x

		y.parent = x.parent

		if (x.parent == self.NIL):
			self.root = y
		elif (x == x.parent.left):
			x.parent.left = y

		else:
			x.parent.right = y

		y.left = x
		x.parent = y

    # right_rotate 시간복잡도: O(1)
	def right_rotate(self, y):
		# y를 기준으로 오른쪽 회전을 수행한다.
		x = y.left
		y.left = x.right

		if (x.right != self.NIL):
			x.right.parent = y

		x.parent = y.parent

		if (y.parent == self.NIL):
			self.root = x
		elif (y == y.parent.right):
			y.parent.right = x

		else:
			y.parent.left = x

		x.right = y
		y.parent = x

	# 새 노드는 처음에 RED로 넣고, 이후 규칙을 복구한다.
	# 삽입 후 RED-RED 위반을 회전과 색 변경으로 복구한다.

	# insert 시간복잡도: O(log n) - 트리 높이에 비례
	def insert(self, key):
		node = Node(key=key, color=RED, left=self.NIL, right=self.NIL, parent=self.NIL)

		parent = self.NIL
		current = self.root

		# 중복 키는 오른쪽 서브트리에 삽입한다.
		while current != self.NIL:
			parent = current

			if node.key < current.key:
				current = current.left

			else:
				current = current.right

		node.parent = parent

		if parent == self.NIL:
			self.root = node

		elif node.key < parent.key:
			parent.left = node

		else:
			parent.right = node

		self.insert_fixup(node)

	# 부모가 RED이면, 조부모는 반드시 BLACK이므로, 삼촌의 색에 따라 3가지 경우로 나뉜다.
	# z: 새로 삽입된 노드, y: z의 삼촌 노드
	def insert_fixup(self, z):
		while z.parent.color == RED:
			# 경우 1~3: 부모가 조부모의 왼쪽 자식인 경우
			if z.parent == z.parent.parent.left:
				y = z.parent.parent.right

				# 경우 1: 삼촌이 RED인 경우
				if y.color == RED:
					z.parent.color = BLACK
					y.color = BLACK
					z.parent.parent.color = RED

					z = z.parent.parent

				# 경우 2~3: 삼촌이 BLACK인 경우
				else:
					# 경우 2: z가 부모의 오른쪽 자식인 경우
					if z == z.parent.right:
						# 안쪽 자식 형태면 먼저 회전해서 경우 3으로 만든다.
						z = z.parent
						self.left_rotate(z)

					# 경우 3: z가 부모의 왼쪽 자식인 경우
					z.parent.color = BLACK
					z.parent.parent.color = RED
					self.right_rotate(z.parent.parent)

			# 경우 4~6: 부모가 조부모의 오른쪽 자식인 경우 (대칭)
			else:
				y = z.parent.parent.left

				# 경우 4: 삼촌이 RED인 경우
				if y.color == RED:
					z.parent.color = BLACK
					y.color = BLACK
					z.parent.parent.color = RED

					z = z.parent.parent

				# 경우 5~6: 삼촌이 BLACK인 경우
				else:
					# 경우 5: z가 부모의 왼쪽 자식인 경우
					if z == z.parent.left:
						# 안쪽 자식 형태면 먼저 회전해서 경우 6으로 만든다.
						z = z.parent
						self.right_rotate(z)

					# 경우 6: z가 부모의 오른쪽 자식인 경우
					z.parent.color = BLACK
					z.parent.parent.color = RED
					self.left_rotate(z.parent.parent)

		self.root.color = BLACK
		self.root.parent = self.NIL
	
	# 서브트리에서 가장 작은 키를 찾는다.
	def _find_min(self, node = None):
		if (node is None):
			node = self.root

		if (node == self.NIL):
			return None
		
		while (node.left != self.NIL):
			node = node.left

		return node

	# 서브트리에서 가장 큰 키를 찾는다.
	def _find_max(self, node = None):
		if (node is None):
			node = self.root

		if (node == self.NIL):
			return None
		
		while (node.right != self.NIL):
			node = node.right
			
		return node

	# u가 있던 자리에 v를 대신 연결한다.
	def transplant(self, u, v):
		if (u.parent == self.NIL):
			self.root = v

		elif (u == u.parent.left):
			u.parent.left = v

		else:
			u.parent.right = v

		v.parent = u.parent

	# 삭제할 노드를 찾은 뒤 일반 BST 삭제를 수행하고, 필요하면 복구한다.
	# z: 삭제할 노드, y: z의 실제 삭제 대상 노드, x: y의 자식 노드

	# delete 시간복잡도: O(log n) - 트리 높이에 비례
	def delete(self, key):
		z = self.search(key)

		if (z is None):
			return False

		z = z
		y = z
		y_original_color = y.color
		if (z.left == self.NIL):
			x = z.right
			self.transplant(z, z.right)
			
		elif (z.right == self.NIL):
			x = z.left
			self.transplant(z, z.left)

		# z의 자식이 둘 다 있는 경우, z의 후계자 y를 찾아서 y를 z의 위치로 옮긴다.
		else:
			y = self._find_min(z.right)
			y_original_color = y.color
			x = y.right

			if (y.parent == z):
				x.parent = y

			else:
				self.transplant(y, y.right)
				y.right = z.right
				y.right.parent = y

			self.transplant(z, y)
			y.left = z.left
			y.left.parent = y
			y.color = z.color

		# 삭제 후 BLACK 높이 불균형이나 RED 위반이 생길 수 있으므로, 필요하면 복구한다.
		if (y_original_color == BLACK):
			self.delete_fixup(x)

		if (self.root != self.NIL):
			self.root.parent = self.NIL

		return True

	# 삭제 후 BLACK 높이 불균형이나 RED 위반을 복구한다.
	# x: 삭제된 노드의 자식 노드, w: x의 형제 노드
	def delete_fixup(self, x):
		while (x != self.root and x.color == BLACK):
			# 경우 1~4: x가 부모의 왼쪽 자식인 경우
			if (x == x.parent.left):
				w = x.parent.right

				# 경우 1: 형제가 RED인 경우
				if (w.color == RED):
					w.color = BLACK
					x.parent.color = RED
					self.left_rotate(x.parent)
					w = x.parent.right

				# 경우 2: 형제가 BLACK이고 형제의 자식이 둘 다 BLACK인 경우
				if (w.left.color == BLACK and w.right.color == BLACK):
					w.color = RED
					x = x.parent

				# 경우 3~4: 형제가 BLACK이고 형제의 자식 중 하나가 RED인 경우
				else:
					# 경우 3: 형제의 오른쪽 자식이 BLACK인 경우 먼저 회전해서 경우 4로 만든다.
					if (w.right.color == BLACK):
						w.left.color = BLACK
						w.color = RED
						self.right_rotate(w)
						w = x.parent.right

					# 경우 4: 형제의 오른쪽 자식이 RED인 경우
					w.color = x.parent.color
					x.parent.color = BLACK
					w.right.color = BLACK
					self.left_rotate(x.parent)
					x = self.root

			# 경우 5~8: x가 부모의 오른쪽 자식인 경우 (대칭)
			else:
				w = x.parent.left

				# 경우 5: 형제가 RED인 경우
				if (w.color == RED):
					w.color = BLACK
					x.parent.color = RED
					self.right_rotate(x.parent)
					w = x.parent.left

				# 경우 6: 형제가 BLACK이고 형제의 자식이 둘 다 BLACK인 경우
				if (w.right.color == BLACK and w.left.color == BLACK):
					w.color = RED
					x = x.parent

				# 경우 7~8: 형제가 BLACK이고 형제의 자식 중 하나가 RED인 경우
				else:
					# 경우 7: 형제의 왼쪽 자식이 BLACK인 경우 먼저 회전해서 경우 8로 만든다.
					if (w.left.color == BLACK):
						w.right.color = BLACK
						w.color = RED
						self.left_rotate(w)
						w = x.parent.left

					# 경우 8: 형제의 왼쪽 자식이 RED인 경우
					w.color = x.parent.color
					x.parent.color = BLACK
					w.left.color = BLACK
					self.right_rotate(x.parent)
					x = self.root

		x.color = BLACK

	# 중위 순회 결과를 리스트로 반환한다.
	def inorder(self):
		result = []

		def _walk(node):
			if node == self.NIL:
				return
			_walk(node.left)
			result.append(node.key)
			_walk(node.right)

		_walk(self.root)
		return result

	# 입력이 키인지 노드 객체인지 구분해서 실제 노드로 바꾼다.
	def _resolve_node(self, target):
		if target is None:
			return self.root
		if isinstance(target, Node):
			return target

		node = self.search(target)
		return node
	
	# h(x): x에서 리프(NIL)까지의 가장 긴 경로에 포함된 에지 수.
	def height(self, target=None):
		node = self._resolve_node(target)
		if node is None:
			return None
		return self._height(node)
	
	# 리프까지의 최대 깊이를 재귀적으로 계산한다.
	def _height(self, node):
		if node == self.NIL:
			return 0
		return 1 + max(self._height(node.left), self._height(node.right))

	# bh(x): x를 제외하고 x에서 리프(NIL)까지 경로에 포함된 블랙 노드 수.
	def black_height(self, target=None):
		node = self._resolve_node(target)
		if node is None:
			return None
		if node == self.NIL:
			return 0

		inclusive = self._black_height_inclusive(node)
		return inclusive - (1 if node.color == BLACK else 0)

	# 현재 노드를 포함한 블랙높이를 계산한다.
	def _black_height_inclusive(self, node):
		if node == self.NIL:
			return 1

		left_bh = self._black_height_inclusive(node.left)
		right_bh = self._black_height_inclusive(node.right)

		if left_bh != right_bh:
			raise ValueError("Red-Black property violation: black heights are inconsistent.")

		return left_bh + (1 if node.color == BLACK else 0)

	# 레드블랙트리의 5가지 성질을 모두 검사한다.
	# 1. 각 노드는 red 혹은 black이다.
	# 2. 루트 노드는 black이다.
	# 3. 모든 리프노드(NIL노드)는 black이다.
	# 4. red 노드의 자식노드들은 전부 black이다(즉, red 노드는 연속되어 등장하지 않는다).
	# 5. 모든 노드에 대해 그 노드로부터 자손인 리프노드에 이르는 모든 경로에는 동일한 개수의 black 노드가 존재한다.
	def validate(self):
		# 3. 모든 리프노드(NIL노드)는 black (구현상 항상 BLACK)
		if self.root == self.NIL:
			return True

		# 2. 루트 노드는 black
		if self.root.color != BLACK:
			return False

		# 각 서브트리의 블랙높이와 RED 규칙을 함께 검사한다.
		def _check(node):
			# 3. 모든 리프노드(NIL노드)는 black (NIL이면 True)
			if node == self.NIL:
				return True, 1

			# 1. 각 노드는 red 혹은 black
			if node.color not in (RED, BLACK):
				return False, 0

			# 4. red 노드의 자식노드들은 전부 black
			if node.color == RED:
				if node.left.color != BLACK or node.right.color != BLACK:
					return False, 0

			# 왼쪽, 오른쪽 서브트리 재귀 검사
			left_ok, left_black_height = _check(node.left)
			right_ok, right_black_height = _check(node.right)

			if not left_ok:
				return False, 0

			if not right_ok:
				return False, 0

			# 5. 모든 경로의 black 노드 개수(black-height)가 같아야 함
			if left_black_height != right_black_height:
				return False, 0

			black_count = left_black_height + (1 if node.color == BLACK else 0)

			return True, black_count

		ok, _ = _check(self.root)
		
		return ok