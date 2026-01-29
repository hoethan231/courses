import math
import argparse

def load_directed_graph(input_path="input.txt"):
    with open(input_path, "r") as f:
        lines = [ln.strip() for ln in f if ln.strip()]
    n = int(lines[0]); start = int(lines[1]); goal = int(lines[2])

    out_adj = {i: [] for i in range(1, n + 1)}
    rev_adj = {i: [] for i in range(1, n + 1)}

    for ln in lines[3:]:
        i, j, w = ln.split()
        i, j, w = int(i), int(j), float(w)
        out_adj[i].append((j, w))
        rev_adj[j].append((i, w))

    for i in range(1, n + 1):
        out_adj[i].sort(key=lambda t: t[0])
        rev_adj[i].sort(key=lambda t: t[0])

    return n, start, goal, out_adj, rev_adj

def dijkstra_on_reversed(n, goal, rev_adj):
    V = [math.inf] * (n + 1)
    visited = [False] * (n + 1)
    V[goal] = 0.0

    for _ in range(n):
        u, best = None, math.inf
        for i in range(1, n + 1):
            if not visited[i] and V[i] < best:
                best = V[i]; u = i
        if u is None:
            break
        visited[u] = True

        for p, w in rev_adj[u]:
            if not visited[p] and V[u] + w < V[p]:
                V[p] = V[u] + w
    return V

def reconstruct_path_from_values(start, goal, out_adj, V):
    if math.isinf(V[start]):
        return []
    path = [start]
    u = start
    for _ in range(len(out_adj) + 5):
        if u == goal:
            break
        candidates = []
        for v, w in out_adj[u]:
            candidates.append((w + V[v], v))
        if not candidates:
            return []
        candidates.sort(key=lambda t: (t[0], t[1]))
        best_cost, v = candidates[0]
        if math.isinf(best_cost):
            return []  
        path.append(v)
        u = v
    if path[-1] != goal:
        return []
    return path

def write_hw2_output(path_nodes, V, out_path="017157582.txt"):
    line1 = " ".join(map(str, path_nodes)) if path_nodes else ""
    vals = []
    for i in range(1, len(V)):
        vals.append("inf" if math.isinf(V[i]) else f"{V[i]:.6f}")
    line2 = " ".join(vals)
    with open(out_path, "w") as f:
        f.write(line1 + "\n")
        f.write(line2 + "\n")

def main():
    ap = argparse.ArgumentParser(description="HW2 cost-to-go solver (directed graph)")
    ap.add_argument("--input", default="input.txt")
    ap.add_argument("--out",   default="017157582.txt")
    args = ap.parse_args()

    n, start, goal, out_adj, rev_adj = load_directed_graph(args.input)
    V = dijkstra_on_reversed(n, goal, rev_adj)  
    path = reconstruct_path_from_values(start, goal, out_adj, V)
    write_hw2_output(path, V, args.out)

if __name__ == "__main__":
    main()
