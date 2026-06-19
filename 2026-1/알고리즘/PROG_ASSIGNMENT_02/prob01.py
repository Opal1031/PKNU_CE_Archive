import time
import os

# 단어를 파일에서 읽어와 리스트로 반환하는 함수
def LoadWords(file_path):
	with open(file_path, "r", encoding = "utf-8") as f:
		text = f.read().lower()

	words = []
	current = []

	for ch in text:
		if ("a" <= ch <= "z"):
			current.append(ch)
			
		else:
			if current:
				words.append("".join(current))
				current = []

	if current:
		words.append("".join(current))

	return words

# 버블 정렬
def BubbleSort(arr):
	for i in range(len(arr) - 1):
		for j in range(len(arr) - 1 - i):
			if (arr[j] > arr[j + 1]):
				arr[j], arr[j + 1] = arr[j + 1], arr[j]

	return arr

# 삽입 정렬
def InsertionSort(arr):
	for i in range(1, len(arr)):
		key = arr[i]
		j = i - 1
		
		while (j >= 0 and arr[j] > key):
			arr[j + 1] = arr[j]
			j -= 1
			
		arr[j + 1] = key

	return arr

# 합병 정렬
def MergeSort(arr):
	if (len(arr) <= 1):
		return arr

	mid = len(arr) // 2
	left = MergeSort(arr[:mid])
	right = MergeSort(arr[mid:])

	i = 0
	j = 0
	k = 0

	while (i < len(left) and j < len(right)):
		if left[i] <= right[j]:
			arr[k] = left[i]
			i += 1
			
		else:
			arr[k] = right[j]
			j += 1
			
		k += 1

	while (i < len(left)):
		arr[k] = left[i]
		i += 1
		k += 1

	while (j < len(right)):
		arr[k] = right[j]
		j += 1
		k += 1

	return arr

# 빠른 정렬 - 파티션 함수 (마지막 요소를 피벗으로 선택)
def _partition(arr, low, high):
	pivot = arr[high]
	i = low - 1

	for j in range(low, high):
		if (arr[j] <= pivot):
			i += 1
			arr[i], arr[j] = arr[j], arr[i]

	arr[i + 1], arr[high] = arr[high], arr[i + 1]
	
	return i + 1

# 빠른 정렬 - 재귀 함수
def _quick_sort(arr, low, high):
	if (low < high):
		pi = _partition(arr, low, high)
		
		_quick_sort(arr, low, pi - 1)
		_quick_sort(arr, pi + 1, high)

# 빠른 정렬 (마지막 요소를 피벗으로 선택)
def QuickSortLastPivot(arr):
	_quick_sort(arr, 0, len(arr) - 1)

	return arr

# 힙 정렬 - 배열을 힙으로 변환하는 함수
def _heapify(arr, n, i):
	largest = i
	left = 2 * i + 1
	right = 2 * i + 2

	if (left < n and arr[left] > arr[largest]):
		largest = left

	if (right < n and arr[right] > arr[largest]):
		largest = right

	if (largest != i):
		arr[i], arr[largest] = arr[largest], arr[i]
		_heapify(arr, n, largest)

# 힙 정렬
def HeapSort(arr):
	n = len(arr)

	for i in range(n // 2 - 1, -1, -1):
		_heapify(arr, n, i)

	for i in range(n - 1, 0, -1):
		arr[0], arr[i] = arr[i], arr[0]
		_heapify(arr, i, 0)

	return arr

# 파이썬 표준 정렬
def PythonBuiltinSort(arr):
	arr.sort()
	
	return arr

# 정렬 알고리즘 실행 시간 측정
def MeasureSortTime(sort_function, words):
	test_data = words.copy()
	
	start = time.perf_counter()
	result = sort_function(test_data)
	end = time.perf_counter()

	return end - start

base_dir = os.path.dirname(os.path.abspath(__file__))
file_path = os.path.join(base_dir, "harry_full.txt")
words = LoadWords(file_path)

print(f"총 단어 수: {len(words)}")

algorithms = [
	("버블 정렬", BubbleSort),
	("삽입 정렬", InsertionSort),
	("합병 정렬", MergeSort),
	("빠른 정렬", QuickSortLastPivot),
	("힙 정렬", HeapSort),
	("파이썬 표준 정렬", PythonBuiltinSort),
]

print("\n정렬 알고리즘 실행 시간(초):")

for name, function in algorithms:
	time = MeasureSortTime(function, words)
	
	print(f"{name}: {time:.6f}초")