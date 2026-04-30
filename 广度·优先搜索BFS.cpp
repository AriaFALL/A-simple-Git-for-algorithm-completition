#include<iostream>
#include<vector>
#include<queue>

using namespace std;

const int dx[4]={-1,1,0,0};
const int dy[4]={0,0,-1,1};

struct POS{
    int x;
    int y;
    int step;
};

int bfs(vector<vector<int>>&gird,int startx,int starty,int endx,int endy){
    int row =gird.size();
    int col=gird[0].size();
    queue<POS> q;
    q.push({startx,starty,0});
    vector<vector<bool>> visited(row,vector<bool>(col));

    while(!q.empty()){
        POS cur=q.front();
        q.pop();

        if(cur.x==endx&&cur.y==endy){
            return cur.step;
        }

        for(int i=0;i<4;i++){
             int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];
            if (nx >= 0 && nx < row && ny >= 0 && ny < col 
                && !visited[nx][ny] && gird[nx][ny] != 1) {
                
                visited[nx][ny] = true; // 【关键】入队时立马标记！
                q.push({nx, ny, cur.step + 1});
        }
    }
}
return -1;
}