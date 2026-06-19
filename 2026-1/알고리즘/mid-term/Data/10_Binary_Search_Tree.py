class Node:
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None

class BST:
    def __init__(self):
        self.root = None

    # 노드 검색
    def search(self, data):
        return self._search(self.root, data)

    def _search(self, node, data):
        # 노드가 None이거나 데이터가 일치하는 경우 해당 노드를 반환
        if (node is None or node.data == data):
            return node
        
        # 데이터가 노드의 데이터보다 작은 경우 왼쪽 서브트리에서 검색
        if (data < node.data):
            return self._search(node.left, data)
        
        # 데이터가 노드의 데이터보다 큰 경우 오른쪽 서브트리에서 검색
        return self._search(node.right, data)
    
    # 노드 삽입
    def insert(self, data):
        # 트리가 비어있는 경우 새로운 노드를 루트로 설정
        if not self.root:
            self.root = Node(data)

        # 트리가 비어있지 않은 경우 재귀적으로 적절한 위치에 노드를 삽입
        else:
            self._insert(self.root, data)

    def _insert(self, node, data):
        # 데이터가 노드의 데이터보다 작은 경우 왼쪽 서브트리에 삽입
        if (data < node.data):
            if node.left is None:
                node.left = Node(data)
            
            else:
                self._insert(node.left, data)

        # 데이터가 노드의 데이터보다 큰 경우 오른쪽 서브트리에 삽입       
        else:
            if node.right is None:
                node.right = Node(data)
            
            else:
                self._insert(node.right, data)
    
    # 노드 삭제
    def delete(self, data):
        self.root = self._delete(self.root, data)

    def _delete(self, node, data):
        # 노드가 None인 경우 삭제할 노드가 존재하지 않으므로 None 반환
        if (node is None):
            return node

        # 데이터가 노드의 데이터보다 작은 경우 왼쪽 서브트리에서 삭제
        if (data < node.data):
            node.left = self._delete(node.left, data)

        # 데이터가 노드의 데이터보다 큰 경우 오른쪽 서브트리에서 삭제
        elif (data > node.data):
            node.right = self._delete(node.right, data)

        # 데이터가 노드의 데이터와 일치하는 경우 해당 노드를 삭제
        else:
            # 노드가 하나의 자식만 가지거나 자식이 없는 경우
            if (node.left is None):
                return node.right
            
            elif (node.right is None):
                return node.left

            # 노드가 두 개의 자식을 가지는 경우
            tmp = self._find_successor(node)
            node.data = tmp.data
            node.right = self._delete(node.right, tmp.data)

        return node
    
    # 최소값 찾기
    def _find_min(self, node):
        while (node.left is not None):
            node = node.left

        return node
    
    # 최대값 찾기
    def _find_max(self, node):
        while (node.right is not None):
            node = node.right

        return node

    # inorder 순회 기준 successor 찾기
    def _find_successor(self, node):
        if (node is None or node.right is None):
            return None

        return self._find_min(node.right)

    # inorder 순회 기준 predecessor 찾기
    def _find_predecessor(self, node):
        if (node is None or node.left is None):
            return None

        return self._find_max(node.left)