def read_input(filename):
	with open(filename, 'r', encoding = 'utf-8') as f:
		lines = [line.strip() for line in f if line.strip()]
		
	n = int(lines[0])
	graph = []
	
	for i in range(1, n + 1):
		graph.append(list(map(int, lines[i].split())))
		
	m = int(lines[n + 1])
	
	return n, graph, m

def is_safe(node, color, colors, graph, n):
	for neighbor in range(n):
		if graph[node][neighbor] == 1 and colors[neighbor] == color:
			return False
		
	return True

def solve(node, colors, graph, n, m):
	if node == n:
		return True
	
	for color in range(1, m + 1):
		if is_safe(node, color, colors, graph, n):
			colors[node] = color
			
			if solve(node + 1, colors, graph, n, m):
				return True
			
			colors[node] = 0
			
	return False

def can_color(graph, n, m):
	colors = [0] * n
	
	return solve(0, colors, graph, n, m)

if __name__ == "__main__":
	n, graph, m = read_input("../input2.txt")  
	
	if can_color(graph, n, m):
		print("Yes")
		
	else:
		print("No")