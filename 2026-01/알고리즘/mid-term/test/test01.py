import heapq

class Node:
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None

class BST:
    def __init__(self):
        self.root = None

    def insert(self, data):
        if self.root is None:
            self.root = Node(data)
        else:
            self._insert(self.root, data)

    def _insert(self, node, data):
        if data < node.data:
            if node.left is None:
                node.left = Node(data)
            else:
                self._insert(node.left, data)
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

def heapify_max(arr):
    # heapq는 min heap만 지원하므로, 부호를 반전해서 max heap 구현
    h = [-ord(ch) for ch in arr]
    heapq.heapify(h)
    return [chr(-x) for x in h]

def preorder(tree, idx=0):
    if idx >= len(tree):
        return []
    return [tree[idx]] + preorder(tree, 2*idx+1) + preorder(tree, 2*idx+2)

def inorder(tree, idx=0):
    if idx >= len(tree):
        return []
    return inorder(tree, 2*idx+1) + [tree[idx]] + inorder(tree, 2*idx+2)

def postorder(tree, idx=0):
    if idx >= len(tree):
        return []
    return postorder(tree, 2*idx+1) + postorder(tree, 2*idx+2) + [tree[idx]]

if __name__ == "__main__":
    word = input("영단어 입력: ").strip().lower()
    arr = list(word)
    heap = heapify_max(arr)
    
    print("max heap 배열:", heap)
    print("preorder:", preorder(heap))
    print("inorder:", inorder(heap))
    print("postorder:", postorder(heap))