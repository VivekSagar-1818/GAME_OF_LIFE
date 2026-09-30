# Conway's Game of Life (Raylib C++)

![Game of Life Demo](demo.gif)

An interactive, 2D desktop replica of John Conway's famous zero-player cellular automaton—**Conway's Game of Life**—built in C++ using the [Raylib](https://www.raylib.com/) library.

---

## Overview

Conway's Game of Life simulates the evolution of an ecosystem over an infinite or bounded grid. Each cell exists in one of two states: **alive** (`true`) or **dead** (`false`). In each discrete generation, every cell's state updates simultaneously based on the number of live neighbors adjacent to it.

This implementation runs at **10 FPS** on an $800 \times 600$ viewport, allowing visible frame-by-frame progression. It includes an interactive mouse-input feature that allows users to inject new life directly into the active simulation.

---

## Simulation Rules

At each iteration, every cell evaluates its 8 neighbors (Moore neighborhood) using Conway's core rules:

1. **Underpopulation:** Any live cell with fewer than 2 live neighbors dies.
2. **Survival:** Any live cell with 2 or 3 live neighbors lives on to the next generation.
3. **Overpopulation:** Any live cell with more than 3 live neighbors dies.
4. **Reproduction:** Any dead cell with exactly 3 live neighbors becomes a live cell.

---

## Key Features

- **Double-Buffered State Updates:** Every cell contains both `alive` and `nextalive` states in a `Cell` struct. This prevents race conditions where updated cells prematurely influence neighbors within the same generation pass.
- **Interactive Mouse Spawning (Custom Input):**
  - Left-clicking (`MOUSE_BUTTON_LEFT`) dynamically spawns a cluster of cells centered at the mouse cursor.
  - Spawns the clicked cell `(row, col)` along with its immediate adjacent neighbors `(row, col + 1)`, `(row, col - 1)`, and `(row - 1, col)`.
  - Enables real-time perturbation, pattern testing, and reviving stagnant grids without restarting.
- **Boundary-Safe Neighbor Checking:** Neighbor lookups use an offset array `offsets[8][2]` combined with strict coordinate clamping (`neighbourx >= 0 && neighbourx < rows && neighboury >= 0 && neighboury < colms`) to prevent out-of-bounds array access at the grid edges.
- **Default Seed:** Launches with initial pre-configured sample cells active at coordinates `(2, 2)`, `(2, 3)`, and `(3, 2)`.

---

## Grid & Technical Specs

| Parameter | Value |
| :--- | :--- |
| **Window Dimensions** | 800 × 600 pixels |
| **Cell Size** | 20 × 20 pixels |
| **Grid Resolution** | 30 Rows × 40 Columns (1,200 cells) |
| **Target Frame Rate** | 10 FPS |
| **Graphics Library** | Raylib |
| **Language** | C++ |

---

## Simulation Lifecycle

Inside the main game loop (`while (!WindowShouldClose())`):

1. **Handle User Input:** Detects mouse clicks, maps `(GetMouseX(), GetMouseY())` to grid row and column coordinates, and activates the targeted cell cluster.
2. **Compute Next Generation:** Iterates across all cells, invokes the `countneighbours(i, j)` lambda to sum surrounding active cells, and determines `nextalive` according to Conway's rules.
3. **Render Active Cells:** Clears the canvas (`BLACK`) and renders all currently `alive` cells as solid rectangles (`WHITE`).
4. **Advance Generation:** Commits `nextalive` values to `alive` across all cells for the subsequent frame.

---

## Build & Run

### Prerequisites
- A C++ compiler supporting C++11 or newer (`g++`, `clang++`, or MSVC)
- [Raylib](https://www.raylib.com/) installed and linked

### Compilation Commands

**Linux / macOS:**
```bash
g++ -std=c++17 GAME_OF_LIFE.cpp -o game_of_life -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
./game_of_life
