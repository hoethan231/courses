import math
import matplotlib.pyplot as plt

def main():
    
    ### Taking In Coordinates ###
    coords = [(-1,-1)]
    try:
        with open("coords.txt", "r") as file:
            for line in file.readlines():
                x, y = line.strip().split()
                coords.append((float(x),float(y)))
    except:
        print("Error: Could not find/open coords.txt")
        return
    
    try:
        with open("input.txt", "r") as file:
            lines = [ln.strip() for ln in file.readlines()]
    except:
        print("Error: Could not find/open input.txt")
        return
    
    n, start, end = int(lines[0]), int(lines[1]), int(lines[2])
    
    if len(coords) < n:
        print(f"Error: coords.txt has {len(coords)} points but n = {n}")
        return
    
    ### Make Adjacency List ###
    adjancencyList = {i: set() for i in range(n+1)}

    for i in range(3, len(lines)):
        line = lines[i].split()
        a, b, w = int(line[0]), int(line[1]), float(line[2])
        adjancencyList[a].add((b, w))
        adjancencyList[b].add((a, w))
    
    
    ### Dijkstra's Algorithm ###
    dist = [math.inf] * (n+1)
    dist[start] = 0
    visited = [False] * (n+1)
    
    for _ in range(n):
        best = math.inf
        u = None
        for i in range(1, n+1):
            if not visited[i] and dist[i] < best:
                best = dist[i]
                u = i

        if u is None:
            break
        visited[u] = True

        for v, w in adjancencyList[u]:
            if not visited[v] and (dist[u] + w < dist[v]):
                dist[v] = dist[u] + w
                
    
    ### Plotting ###
    fig, ax = plt.subplots()
    seen = set()
    for u, nbrs in adjancencyList.items():
        x1, y1 = coords[u]
        for v, w in nbrs:
            key = tuple(sorted((u, v)))
            if key in seen:
                continue
            seen.add(key)
            x2, y2 = coords[v]
            ax.plot([x1, x2], [y1, y2], color="grey")
            mx, my = (x1 + x2)/2, (y1 + y2)/2
            ax.text(mx, my, f"{w:.2f}", fontsize=8)

    xs = [coords[i][0] for i in range(n)]
    ys = [coords[i][1] for i in range(n)]
    ax.scatter(xs, ys)

    for i, (x, y) in enumerate(coords):
        ax.text(x, y, f" {i}", va="center", fontsize=9)

    ax.set_aspect("equal", adjustable="box")
    ax.grid(True, which="both")
    ax.set_xlabel("X")
    ax.set_ylabel("Y")
    ax.set_title("Graph on 2D Grid")
    plt.show()
    
if __name__ == "__main__":
    main()