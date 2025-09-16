import math
import sys
import argparse
import pygame
import imageio.v2 as imageio

# Taking Input
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

    adj = {i: [] for i in range(1, n + 1)}
    for i in range(3, len(lines)):
        a, b, w = lines[i].split()
        a, b, w = int(a), int(b), float(w)
        adj[a].append((b, w))
        adj[b].append((a, w))

    for i in range(1, n + 1):
        adj[i].sort(key=lambda t: t[0])

    return n, start, end, coords, adj

# Dijkstra with steps for Vizulization
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

def reconstruct_path_nodes(prev, start, end):
    path = []
    v = end
    if v is None:
        return path
    while v is not None:
        path.append(v)
        if v == start:
            break
        v = prev[v]
    if not path or path[-1] != start:
        return []
    path.reverse()
    return path

def reconstruct_path_edges(prev, start, end):
    path = reconstruct_path_nodes(prev, start, end)
    edges = set()
    for i in range(len(path) - 1):
        u, v = path[i], path[i + 1]
        edges.add((min(u, v), max(u, v)))
    return edges

def write_path_output(path_nodes, dist, out_path="017157582.txt"):
    if path_nodes:
        line1 = " ".join(str(i) for i in path_nodes)
        line2 = " ".join(f"{dist[v]:.4f}" for v in path_nodes)
    else:
        line1 = ""
        line2 = "inf"
    with open(out_path, "w") as f:
        f.write(line1 + "\n")
        f.write(line2 + "\n")

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

def progress_bar(i, total, width=40, prefix="MP4"):
    if total <= 0:
        total = 1
    pct = i / total
    filled = int(width * pct)
    bar = "█" * filled + "-" * (width - filled)
    sys.stdout.write(f"\r{prefix} [{bar}] {i}/{total} ({pct*100:.1f}%)")
    sys.stdout.flush()
    if i == total:
        sys.stdout.write("\n")

# Pygame Vizulization
import os
import math
import pygame
import imageio.v2 as imageio

def run_visualization(n, start, end, coords, adj, out_path="017157582.txt", window=(1000, 750), popup=False):
    # --- Hard-coded video settings ---
    VIDEO_PATH = "017157582.mp4"
    FPS = 60

    # Headless by default (no OS window)
    if not popup:
        os.environ.setdefault("SDL_VIDEODRIVER", "dummy")

    pygame.init()
    pygame.font.init()

    # Create window or a hidden / dummy display
    flags = 0
    if popup and hasattr(pygame, "HIDDEN"):
        flags |= 0  # visible normal window
    elif not popup and hasattr(pygame, "HIDDEN"):
        flags |= pygame.HIDDEN  # hidden window (still offscreen)
    screen = pygame.display.set_mode(window, flags)  # works with dummy driver too
    pygame.display.set_caption("Dijkstra — red edges: traversed, blue: current, red nodes: neighbors, green: final path")
    clock = pygame.time.Clock()

    # Precompute all algorithm steps so we know total frames (for progress bar)
    steps = list(dijkstra_steps(n, start, adj))
    total_frames = len(steps)
    if total_frames == 0:
        raise RuntimeError("No frames produced. Check inputs (coords/input).")

    # Final path (from the last step's prev/dist)
    last_state = steps[-1]
    if last_state["dist"][end] < math.inf:
        final_path_nodes = reconstruct_path_nodes(last_state["prev"], start, end)
        final_path_edges = reconstruct_path_edges(last_state["prev"], start, end)
    else:
        final_path_nodes = []
        final_path_edges = set()

    # Write the path output once (second line = cumulative costs to each vertex in path)
    write_path_output(final_path_nodes, last_state["dist"], out_path)

    # Open MP4 writer
    writer = imageio.get_writer(VIDEO_PATH, fps=FPS, codec="libx264")  # add bitrate="6M" to shrink size

    W, H = window
    w2s = make_world_to_screen(coords, W, H, margin=70)

    WHITE = (255, 255, 255)
    BLACK = (0, 0, 0)
    GRAY = (180, 180, 180)
    RED = (220, 30, 30)
    BLUE = (40, 100, 230)
    GREEN = (30, 170, 60)

    r = max(5, min(10, int(min(W, H) / 90)))

    # Unique undirected edges & weights
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

    # Draw helper per step
    def draw_step(state, is_last=False):
        screen.fill(WHITE)

        legend_lines = [
            "Ethan Ho, CMPE 252 Homework 1",
            "Colors: blue=current, red nodes=neighbors, red edges=traversed, green=final path",
        ]
        yoff = 8
        for line in legend_lines:
            screen.blit(bigfont.render(line, True, BLACK), (10, yoff))
            yoff += 24

        traversed = state["traversed_edges"]
        # edges
        for (u, v) in edges:
            x1, y1 = node_pos[u]
            x2, y2 = node_pos[v]
            color = RED if ((u, v) in traversed or (v, u) in traversed) else GRAY
            width = 3 if color == RED else 1
            pygame.draw.line(screen, color, (x1, y1), (x2, y2), width)

        # final path (on last frame)
        if is_last and final_path_edges:
            for (u, v) in final_path_edges:
                x1, y1 = node_pos[u]
                x2, y2 = node_pos[v]
                pygame.draw.line(screen, GREEN, (x1, y1), (x2, y2), 6)

        # edge labels
        for (sx, sy, surf) in edge_labels:
            screen.blit(surf, (sx - surf.get_width() // 2, sy - surf.get_height() // 2))

        # nodes
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

        # node labels
        for i, surf in node_labels:
            x, y = node_pos[i]
            screen.blit(surf, (x + r + 2, y - surf.get_height() // 2))

        # status
        if is_last:
            dist_text = "unreachable" if last_state["dist"][end] == math.inf else f"{last_state['dist'][end]:.6f}"
            status = f"Done — shortest distance to {end}: {dist_text} | wrote: {out_path} | video: {VIDEO_PATH}"
        else:
            status = f"Processing node {state['current']}" if state["current"] is not None else "Processing…"
        screen.blit(bigfont.render(status, True, BLACK), (10, H - 32))

    try:
        for i, state in enumerate(steps, start=1):
            # keep window responsive if showing it
            if popup:
                for event in pygame.event.get():
                    if event.type == pygame.QUIT:
                        raise KeyboardInterrupt

            draw_step(state, is_last=(i == total_frames))

            if popup:
                pygame.display.flip()

            # capture the frame and write to mp4
            frame = pygame.surfarray.array3d(screen).swapaxes(0, 1)  # (H, W, 3)
            writer.append_data(frame)

            # console progress bar
            progress_bar(i, total_frames, width=40, prefix="MP4")

            if popup:
                clock.tick(FPS)

    except KeyboardInterrupt:
        print("\nInterrupted by user.")
    finally:
        writer.close()
        pygame.quit()


def main():
    parser = argparse.ArgumentParser(description="Dijkstra visualization in Pygame (writes path to txt + MP4)")
    parser.add_argument("--coords", default="coords.txt", help="Path to coords.txt")
    parser.add_argument("--input",  default="input.txt",  help="Path to input.txt")
    parser.add_argument("--out",    default="017157582.txt", help="Output text file")
    parser.add_argument("--width",  type=int, default=1000, help="Window width")
    parser.add_argument("--height", type=int, default=750,  help="Window height")
    parser.add_argument("--popup",  action="store_true", help="Show a live Pygame window (default: no popup)")
    args = parser.parse_args()

    n, start, end, coords, adj = load_graph(args.coords, args.input)
    run_visualization(n, start, end, coords, adj,
                      out_path=args.out, window=(args.width, args.height),
                      popup=args.popup)


if __name__ == "__main__":
    main()