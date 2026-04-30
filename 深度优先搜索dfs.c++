#include<iostream>
#include<vector>
using namespace std;

vector<int> dx = {1, 0, -1, 0};
vector<int> dy = {0, 1, 0, -1};
vector<vector<int>> path;
bool mark[100][100]; // 初始化

void print_result() {
    int size = path.size();
    for(int i = 0; i < size - 1; i++) {
        cout << '(' << path[i][0] << ',' << path[i][1] << ')' << "->"; 
    }
    printf("(%d,%d)\n", path[size - 1][0], path[size - 1][1]);
}

void sousuo(int x, int y, int n) {
    vector<int> a(2, 0);
    a[0] = x;
    a[1] = y;
    path.push_back(a); // 压入路径
    
    if(x == n - 1 && y == n - 1) {
        print_result();
        path.pop_back();
        return; // 回溯
    }
    
    for(int i = 0; i < 4; i++) {
        int nx = x + dx[i];//不能污染当前层的x,y
        int ny = y + dy[i]; // 右，下，左，上
        
        // 👇 这里全部改成了 nx 和 ny，判断下一步是否合法
        if(nx >= 0 && nx < n && ny >= 0 && ny < n && mark[nx][ny] == false) {
            mark[nx][ny] = true;  // 标记下一步
            
            sousuo(nx, ny, n);    // 往下一步递归
            
            mark[nx][ny] = false; // 释放下一步的标记
        }
    }
    path.pop_back(); // 回归
}

int main() {
    int n;
    cin >> n;
    mark[0][0] = true;
    
    // 起点是 (0,0)，网格大小是 n
    sousuo(0, 0, n); 
    
    return 0;
}