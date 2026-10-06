#include <iostream>
#include <vector>

struct Node {
  int key;
  int value;
  Node *next;

  Node(int key, int value) : key(key), value(value), next(nullptr) {}
};

class Graph {
public:
  int V;                             // Number of vertices
  std::vector<std::vector<int>> adj; // Adjacency list

  Graph(int V) : V(V), adj(V) {}

  void addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u); // For undirected graph
  }

  void dfsUtil(int v, std::vector<bool> &visited) {
    visited[v] = true;
    std::cout << v << " ";

    for (int i : adj[v]) {
      if (!visited[i]) {
        dfsUtil(i, visited);
      }
    }
  }

  void dfs(int start) {
    std::vector<bool> visited(V, false);
    dfsUtil(start, visited);
  }

  void bfs(int start) {
    std::vector<bool> visited(V, false);
    std::vector<int> queue;

    visited[start] = true;
    queue.push_back(start);

    while (!queue.empty()) {
      int v = queue.front();
      queue.erase(queue.begin());
      std::cout << v << " ";

      for (int i : adj[v]) {
        if (!visited[i]) {
          visited[i] = true;
          queue.push_back(i);
        }
      }
    }
  }

  int numberOfIslands() {
    std::vector<bool> visited(V, false);
    int count = 0;

    for (int i = 0; i < V; ++i) {
      if (!visited[i]) {
        dfsUtil(i, visited);
        count++;
      }
    }

    return count;
  }

  int orangeRotting(std::vector<std::vector<int>> &grid) {
    int rows = grid.size();
    if (rows == 0)
      return 0;
    int cols = grid[0].size();

    std::vector<std::pair<int, int>> directions = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    std::vector<std::pair<int, int>> rotten;
    int freshCount = 0;

    for (int r = 0; r < rows; ++r) {
      for (int c = 0; c < cols; ++c) {
        if (grid[r][c] == 2) {
          rotten.push_back({r, c});
        } else if (grid[r][c] == 1) {
          freshCount++;
        }
      }
    }

    int minutes = 0;
    while (!rotten.empty() && freshCount > 0) {
      std::vector<std::pair<int, int>> newRotten;
      for (auto [r, c] : rotten) {
        for (auto [dr, dc] : directions) {
          int nr = r + dr;
          int nc = c + dc;
          if (nr >= 0 && nr < rows && nc >= 0 && nc < cols &&
              grid[nr][nc] == 1) {
            grid[nr][nc] = 2;
            newRotten.push_back({nr, nc});
            freshCount--;
          }
        }
      }
      rotten = newRotten;
      minutes++;
    }

    return freshCount == 0 ? minutes : -1;
  }
};