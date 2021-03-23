#include <iostream>
#include <cstring>
using namespace std;

const int SIZE = 5005;
const int END = -1;

int n, m, head[SIZE];
struct Edge {
    int from, to, next;
    Edge() {
        from = to = 0, next = END;
    }
    Edge(int f, int t, int n) {
        from = f, to = t, next = n;
    }
} edges[SIZE * 2];
void AddEdge(int from, int to, int ind) {
    if(head[from] == END || to < edges[head[from]].to) {
        edges[ind] = Edge(from, to, head[from]);
        head[from] = ind;
        return;
    }
    if(edges[head[from]].next == END) {
        edges[ind] = Edge(from, to, END);
        edges[head[from]].next = ind;
        return;
    }
    for(int i = head[from]; i != END; i = edges[i].next) {
        if(to < edges[edges[i].next].to) {
            edges[ind] = Edge(from, to, edges[i].next);
            edges[i].next = ind;
            break;
        }
        if(edges[i].next == END) {
            edges[ind] = Edge(from, to, END);
            edges[i].next = ind;
            break;
        }
    }
    return;
}

int ans[SIZE], tmpAns[SIZE], bannedEdge = END;
bool visited[SIZE];
void InitData() {
    memset(head, END, sizeof(head));
    memset(ans, 0x3f3f3f, sizeof(ans));
}

void ReadData() {
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int from, to;
        cin >> from >> to;
        AddEdge(from, to, i);
        AddEdge(to, from, i + m);
    }
}
void GiveAns() {
    for(int i = 1;i <= n; i++) {
        cout << ans[i] << ' ';
    }
    cout << endl;
}
bool CheckEdge(int i) {
    if(bannedEdge == END) {
        return false;
    }
    return i == bannedEdge || i == bannedEdge + m;
}
bool CheckIfShouldBreak(int k) {
    for(int i = 1; i <= k; i++) {
        if(ans[i] < tmpAns[i]) {
            return true;
        }
        if(ans[i] > tmpAns[i]) {
            return false;
        }
    }
    return false;
}
bool shouldBreak = false;
void Dfs(int node) {
    tmpAns[++tmpAns[0]] = node;
    if(CheckIfShouldBreak(tmpAns[0])) {
        shouldBreak = true;
        return;
    }
    if(tmpAns[0] == n) {
        for(int i = 1; i <= n; i++) {
            ans[i] = tmpAns[i];
        }
        return;
    }

    visited[node] = true;
    for(int i = head[node]; i != END; i = edges[i].next) {
        if(visited[edges[i].to] || CheckEdge(i)) {
            continue;
        }
        Dfs(edges[i].to);
        if(shouldBreak) {
            return;
        }
    }
}

int main() {
    InitData();
    ReadData();
    if(m == n - 1) {
        tmpAns[0] = 0;
        Dfs(1);
        GiveAns();
    }
    if(m == n) {
        for(int i = 0; i < m; i++) {
            bannedEdge = i;
            tmpAns[0] = 0;
            shouldBreak = false;
            memset(visited, false, sizeof(visited));
            Dfs(1);
        }
        GiveAns();
    }
    return 0;
}