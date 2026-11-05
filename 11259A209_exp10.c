#include <stdio.h>
#define MAX 20
int adj[MAX][MAX];
int visited[MAX];
int n;
void bfs(int start) {
int queue[MAX], front = 0, rear = 0, i;
for (i = 0; i < n; i++)
visited[i] = 0;
visited[start] = 1;
queue[rear++] = start;
printf("BFS Traversal: ");
while (front < rear) {
int curr = queue[front++];
printf("%d ", curr);
for (i = 0; i < n; i++) {
if (adj[curr][i] == 1 && !visited[i]) {
visited[i] = 1;
queue[rear++] = i;
}
}
}
printf("\n");
}
void dfsUtil(int v) {
int i;
visited[v] = 1;
printf("%d ", v);
for (i = 0; i < n; i++) {
if (adj[v][i] == 1 && !visited[i])
dfsUtil(i);
}
}
void dfs(int start) {
int i;
for (i = 0; i < n; i++)
visited[i] = 0;
printf("DFS Traversal: ");
dfsUtil(start);
printf("\n");
}
int main() {
int edges, i, u, v, start, choice;
printf("Enter number of vertices: ");
scanf("%d", &n);
printf("Enter number of edges: ");
scanf("%d", &edges);
for (i = 0; i < n; i++)
for (v = 0; v < n; v++)
adj[i][v] = 0;
printf("Enter edges (u v) for an undirected graph:\n");
for (i = 0; i < edges; i++) {
scanf("%d %d", &u, &v);
adj[u][v] = 1;
adj[v][u] = 1;
}
printf("Enter starting vertex: ");
scanf("%d", &start);
do {
printf("\n--- Graph Traversal Menu ---\n");
printf("1. BFS\n2. DFS\n3. Exit\n");
printf("Enter your choice: ");
scanf("%d", &choice);
switch (choice) {
case 1:
bfs(start);
break;
case 2:
dfs(start);
break;
case 3:
printf("Exiting program.\n");
break;
default:
printf("Invalid choice.\n");
}
} while (choice != 3);
return 0;
}
