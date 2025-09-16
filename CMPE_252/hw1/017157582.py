import math
import sys
import argparse
import pygame

# Loading Files
def load_graph(coord_path="coords.txt", input_path="input.txt"):
    coords = [(-1, -1)]
    with open(coord_path, "r") as file:
        for line in file:
            x, y = line.strip().split()
            coords.append((float(x), float(y)))

    with open(input_path, "r") as file:
        lines = [ln.strip() for ln in file.readlines()]

    n = int(lines[0]); start = int(lines[1]); end = int(lines[2])

    if len(coords) - 1 < n:
        raise ValueError(f"coords.txt has {len(coords)-1} points but n = {n}")

    adj = {i: set() for i in range(1, n + 1)}
    for i in range(3, len(lines)):
        a, b, w = lines[i].split()
        a, b, w = int(a), int(b), float(w)
        adj[a].add((b, w))
        adj[b].add((a, w))

    return n, start, end, coords, adj

# Dijkstra with steps for visuals
def dijkstra_steps(n, start, adj):
    dist = [math.inf] * (n + 1)
    visited = [False] * (n + 1)
    prev = [None] * (n + 1)
    dist[start] = 0.0

    traversed = set()

    for _ in range(n):
        best = math.inf
        u = None
        for i in range(1, n + 1):
            if not visited[i] and dist[i] < best:
                best = dist[i]
                u = i

        if u is None:
            break

        nbrs = [v for (v, _w) in adj[u]]

        yield {
            "current": u,
            "neighbors": nbrs,
            "traversed_edges": set(traversed),
            "dist": dist[:],
            "prev": prev[:],
            "visited": visited[:],
        }

        visited[u] = True

        for v, w in adj[u]:
            key = (min(u, v), max(u, v))
            traversed.add(key)
            if not visited[v] and (dist[u] + w < dist[v]):
                dist[v] = dist[u] + w
                prev[v] = u

            yield {
                "current": u,
                "neighbors": nbrs,
                "traversed_edges": set(traversed),
                "dist": dist[:],
                "prev": prev[:],
                "visited": visited[:],
            }

    yield {
        "current": None,
        "neighbors": [],
        "traversed_edges": set(traversed),
        "dist": dist[:],
        "prev": prev[:],
        "visited": visited[:],
    }

def make_world_to_screen(coords, width, height, margin=60):
    xs = [coords[i][0] for i in range(1, len(coords))]
    ys = [coords[i][1] for i in range(1, len(coords))]
    min_x, max_x = min(xs), max(xs)
    min_y, max_y = min(ys), max(ys)
    span_x = max(max_x - min_x, 1e-9)
    span_y = max(max_y - min_y, 1e-9)

    draw_w = width - 2 * margin
    draw_h = height - 2 * margin
    scale = min(draw_w / span_x, draw_h / span_y)

    def world_to_screen(x, y):
        sx = margin + (x - min_x) * scale
        sy = height - margin - (y - min_y) * scale
        return int(round(sx)), int(round(sy))

    return world_to_screen

def reconstruct_path_edges(prev, start, end):
    """Return set of undirected edge keys along the start→end shortest path."""
    path_edges = set()
    v = end
    if v is None:
        return path_edges
    while v is not None and v != start:
        u = prev[v]
        if u is None:
            return set()  # unreachable
        key = (min(u, v), max(u, v))
        path_edges.add(key)
        v = u
    return path_edges

def run_visualization(n, start, end, coords, adj, window=(1000, 750)):
    pygame.init()
    pygame.display.set_caption("Dijkstra (Pygame) — edges: gray→red, current: blue, neighbors: red, final path: green")
    screen = pygame.display.set_mode(window)
    clock = pygame.time.Clock()

    W, H = window
    w2s = make_world_to_screen(coords, W, H, margin=70)

    WHITE = (255, 255, 255)
    BLACK = (0, 0, 0)
    GRAY = (180, 180, 180)
    RED = (220, 30, 30)
    BLUE = (40, 100, 230)
    GREEN = (30, 170, 60)

    r = max(5, min(10, int(min(W, H) / 90)))

    seen = set()
    edges = []
    weights = {}
    for u in range(1, n + 1):
        for v, w in adj[u]:
            key = (min(u, v), max(u, v))
            if key in seen:
                continue
            seen.add(key)
            edges.append(key)
            weights[key] = w

    node_pos = {i: w2s(*coords[i]) for i in range(1, n + 1)}
    font = pygame.font.SysFont(None, 18)
    bigfont = pygame.font.SysFont(None, 24)

    node_labels = [(i, font.render(str(i), True, BLACK)) for i in range(1, n + 1)]
    edge_labels = []
    for (u, v) in edges:
        x1, y1 = coords[u]; x2, y2 = coords[v]
        mx, my = (x1 + x2) / 2.0, (y1 + y2) / 2.0
        smx, smy = w2s(mx, my)
        edge_labels.append((smx, smy, font.render(f"{weights[(u, v)]:.2f}", True, BLACK)))

    steps_gen = dijkstra_steps(n, start, adj)
    try:
        state = next(steps_gen)
    except StopIteration:
        state = {
            "current": None,
            "neighbors": [],
            "traversed_edges": set(),
            "dist": [math.inf] * (n + 1),
            "prev": [None] * (n + 1),
            "visited": [False] * (n + 1),
        }

    final_path_edges = None

    paused = False
    step_delay_ms = 5
    last_step_time = 0

    running = True
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            elif event.type == pygame.KEYDOWN:
                if event.key in (pygame.K_ESCAPE, pygame.K_q):
                    running = False
                elif event.key == pygame.K_SPACE:
                    paused = not paused
                elif event.key == pygame.K_RIGHT:
                    if paused:
                        try:
                            state = next(steps_gen)
                        except StopIteration:
                            pass
                elif event.key == pygame.K_r:
                    steps_gen = dijkstra_steps(n, start, adj)
                    try:
                        state = next(steps_gen)
                    except StopIteration:
                        pass
                    paused = False
                    last_step_time = 0
                    final_path_edges = None

        now = pygame.time.get_ticks()
        if not paused and (now - last_step_time >= step_delay_ms):
            last_step_time = now
            try:
                state = next(steps_gen)
            except StopIteration:
                paused = True

        if state["current"] is None and final_path_edges is None:
            if state["dist"][end] < math.inf:
                final_path_edges = reconstruct_path_edges(state["prev"], start, end)
            else:
                final_path_edges = set()

        screen.fill(WHITE)

        legend_lines = [
            "Space: pause/resume   R: restart   Q/Esc: quit",
            f"Step delay: {step_delay_ms} ms",
            "Colors: blue = current node, red nodes = current neighbors, red edges = traversed, green = final path",
        ]
        yoff = 8
        for line in legend_lines:
            screen.blit(bigfont.render(line, True, BLACK), (10, yoff))
            yoff += 24

        traversed = state["traversed_edges"]
        for (u, v) in edges:
            x1, y1 = node_pos[u]
            x2, y2 = node_pos[v]
            color = RED if ((u, v) in traversed or (v, u) in traversed) else GRAY
            width = 3 if color == RED else 1
            pygame.draw.line(screen, color, (x1, y1), (x2, y2), width)

        if final_path_edges:
            for (u, v) in final_path_edges:
                x1, y1 = node_pos[u]
                x2, y2 = node_pos[v]
                pygame.draw.line(screen, GREEN, (x1, y1), (x2, y2), 6)

        for (sx, sy, surf) in edge_labels:
            screen.blit(surf, (sx - surf.get_width() // 2, sy - surf.get_height() // 2))

        current = state["current"]
        neighbor_set = set(state["neighbors"])
        for i in range(1, n + 1):
            x, y = node_pos[i]
            if current is not None and i == current:
                col = BLUE
            elif i in neighbor_set:
                col = (220, 30, 30)
            else:
                col = (210, 210, 210)
            pygame.draw.circle(screen, col, (x, y), r)
            pygame.draw.circle(screen, BLACK, (x, y), r, 1)

        for i, surf in node_labels:
            x, y = node_pos[i]
            screen.blit(surf, (x + r + 2, y - surf.get_height() // 2))

        if state["current"] is None:
            dist_text = "unreachable" if state["dist"][end] == math.inf else f"{state['dist'][end]:.3f}"
            status = f"Done — shortest distance to {end}: {dist_text}"
        else:
            status = f"Processing node {state['current']}"
        screen.blit(bigfont.render(status, True, BLACK), (10, H - 32))

        pygame.display.flip()
        clock.tick(60)

    pygame.quit()

def main():
    parser = argparse.ArgumentParser(description="Dijkstra visualization in Pygame (with final green path)")
    parser.add_argument("--coords", default="coords.txt", help="Path to coords.txt")
    parser.add_argument("--input", default="input.txt", help="Path to input.txt")
    parser.add_argument("--width", type=int, default=1000, help="Window width")
    parser.add_argument("--height", type=int, default=750, help="Window height")
    args = parser.parse_args()

    n, start, end, coords, adj = load_graph(args.coords, args.input)
    run_visualization(n, start, end, coords, adj, window=(args.width, args.height))

if __name__ == "__main__":
    main()