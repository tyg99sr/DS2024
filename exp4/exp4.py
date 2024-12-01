import heapq


class Graph:
    def __init__(self):
        self.vertices = {}

    def add_vertex(self, vertex):
        if vertex not in self.vertices:
            self.vertices[vertex] = []

    def add_edge(self, vertex1, vertex2, weight=1):
        if vertex1 in self.vertices and vertex2 in self.vertices:
            self.vertices[vertex1].append((vertex2, weight))
            self.vertices[vertex2].append((vertex1, weight))


# 广度优先搜索（BFS）算法
def bfs(graph, start_vertex):
    visited = set()
    queue = []
    queue.append(start_vertex)
    visited.add(start_vertex)

    while queue:
        current_vertex = queue.pop(0)
        print(current_vertex, end=" ")

        for neighbor, _ in graph.vertices[current_vertex]:
            if neighbor not in visited:
                queue.append(neighbor)
                visited.add(neighbor)


# 深度优先搜索（DFS）算法
def dfs(graph, start_vertex, visited=None):
    if visited is None:
        visited = set()

    visited.add(start_vertex)
    print(start_vertex, end=" ")

    for neighbor, _ in graph.vertices[start_vertex]:
        if neighbor not in visited:
            dfs(graph, neighbor, visited)


# 最短路径算法（Dijkstra算法）
def dijkstra(graph, start_vertex):
    distances = {vertex: float('inf') for vertex in graph.vertices}
    distances[start_vertex] = 0
    priority_queue = [(0, start_vertex)]

    while priority_queue:
        current_distance, current_vertex = heapq.heappop(priority_queue)

        if current_distance > distances[current_vertex]:
            continue

        for neighbor, weight in graph.vertices[current_vertex]:
            distance = current_distance + weight

            if distance < distances[neighbor]:
                distances[neighbor] = distance
                heapq.heappush(priority_queue, (distance, neighbor))

    return distances


# 最小支撑树算法（Prim算法）
def prim(graph, start_vertex):
    mst = []
    visited = set([start_vertex])
    edges = []

    for neighbor, weight in graph.vertices[start_vertex]:
        edges.append((start_vertex, neighbor, weight))

    while edges:
        edges.sort(key=lambda x: x[2])
        vertex1, vertex2, weight = edges.pop(0)

        if vertex2 not in visited:
            visited.add(vertex2)
            mst.append((vertex1, vertex2, weight))

            for neighbor, new_weight in graph.vertices[vertex2]:
                if neighbor not in visited:
                    edges.append((vertex2, neighbor, new_weight))

    return mst


if __name__ == "__main__":
    # 创建图并添加顶点和边
    graph = Graph()
    graph.add_vertex('A')
    graph.add_vertex('B')
    graph.add_vertex('C')
    graph.add_vertex('D')
    graph.add_vertex('E')
    graph.add_vertex('F')

    graph.add_edge('A', 'B', 2)
    graph.add_edge('A', 'C', 3)
    graph.add_edge('B', 'D', 4)
    graph.add_edge('C', 'E', 5)
    graph.add_edge('C', 'F', 6)
    graph.add_edge('D', 'E', 7)
    graph.add_edge('E', 'F', 8)

    print("广度优先搜索（BFS）遍历结果：")
    bfs(graph, 'A')
    print()

    print("深度优先搜索（DFS）遍历结果：")
    dfs(graph, 'A')
    print()

    print("从顶点'A'出发的最短路径：")
    shortest_paths = dijkstra(graph, 'A')
    for vertex, distance in shortest_paths.items():
        print(f"到顶点{vertex}的最短距离为：{distance}")
    print()

    print("以顶点'A'为起点的最小支撑树：")
    mst_result = prim(graph, 'A')
    for edge in mst_result:
        print(f"{edge[0]} - {edge[1]} 边的权重为：{edge[2]}")