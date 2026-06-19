def read_input(filename):
    with open(filename, 'r', encoding = 'utf-8') as f:
        lines = [line.strip() for line in f if line.strip()]
	
    n = int(lines[0])
    numbers = list(map(int, lines[1].split()))

    return n, numbers

class Node:
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None

class BST:
    def __init__(self):
        self.root = None
   
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

    def preorder(self):
        result = []

        def _pre(node):
            if node:
                result.append(node.data)
                _pre(node.left)
                _pre(node.right)
        _pre(self.root)

        return result

    def inorder(self):
        result = []

        def _in(node):
            if node:
                _in(node.left)
                result.append(node.data)
                _in(node.right)
        _in(self.root)

        return result

    def postorder(self):
        result = []

        def _post(node):
            if node:
                _post(node.left)
                _post(node.right)
                result.append(node.data)
        _post(self.root)

        return result

if __name__ == "__main__":
    n, numbers = read_input("mid-term/input2.txt")
    bst = BST()

    for num in numbers:
        bst.insert(num)

    print(' '.join(map(str, bst.preorder())))
    print(' '.join(map(str, bst.inorder())))
    print(' '.join(map(str, bst.postorder())))