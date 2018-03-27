#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

vector<vector<int>> visited;
vector<string> v;


// We define our path structure
typedef struct path
{
    // Start potition
    int start_i, start_j;
    // Length of path
    int length;
} path;

// Depth First Search to go through our longest path after BFS
void DFS(int x, int y, vector<string> &maze, vector<vector<int>> &visited, vector<string> &v, char &count)
{
    for(int k = x-1; k <= x+1; k++)
    {
        for(int l= y-1;l <= y+1; l++)
        {
                if((k == x-1 && l == y-1)||(k == x-1 && l == y+1)||(k == x+1 && l == y+1)||(k == x+1 &&l == y-1))
                    continue; 
                if(k >= 0 && k < maze.size() &&  l >= 0  && l < maze[0].length() &&  maze[k][l] == '.' && visited[k][l] == 0) 
                {
                visited[k][l] = 1;
                v[k].replace(l,1,1,count);
                count++;
                DFS(k, l, maze, visited, v,count);
            }
        
        }
    }       
}

bool compare(path a, path b)
{ 
    return a.length < b.length; 
}

int main()
{      
    // Opening our file
    string filename;
    cout << "which file do you want to open?" << endl;
    cin >> filename;
    ifstream file(filename.c_str()); 
    // Reading the maze 
    string myString;
    vector<string> matrix;
    while(getline(file, myString))
    {
        matrix.push_back(myString);
    }
    // Breath First Search --> with a queue we are looking for ALL paths
    vector<string> final(matrix);
    int id = 1, i,j,k,l;
    int r = matrix.size(), c = matrix[0].length();
    vector<path> paths;
    vector<vector<int> > visited(r, vector<int> (c,0));
    queue<pair<int,int>> myQueue;  
    stack<pair<int,int>> stack;
    // BFS
    for(i = 0; i < r ; i++)
        {
            for(j = 0 ; j < c; j++)
            {
                // If Not path or visited
                if(matrix[i][j] == '#' || visited[i][j])
                    continue;
                // if path or not visited
                myQueue.push(make_pair(i,j));
                int length = 0;
                // We start doing DFS in each node with the last firt
                while(!myQueue.empty())
                {
                    pair<int,int> top = myQueue.front();
                    myQueue.pop();
                    visited[top.first][top.second] = id;
                    length++;
                    for(k = top.first - 1; k <= top.first + 1; k++)
                        {
                            for(l = top.second - 1; l <= top.second + 1; l++)
                            {
                                // We visit the adjacents to our current position
                                if((k == top.first - 1 && l == top.second - 1) || \
                                    (k == top.first - 1 && l == top.second + 1) || \
                                    (k == top.first + 1 && l == top.second + 1) || \
                                    (k == top.first + 1 && l == top.second - 1))
                                    continue; 
                                // If out of the matrix, skip this iteration
                                if(k < 0 || l < 0 || k > r-1 || l > c-1)
                                    continue;
                                // If not path or visited, skip this iteration
                                if(matrix[k][l] == '#' || visited[k][l])
                                    continue;
                                // Add to the queue and keep checking until you can't go further
                                pair<int,int> nxt = make_pair(k,l);
                                visited[k][l] = id;
                                myQueue.push(nxt);
                            }
                        }
                }
                // We add the path we found until all visited
                path nxt_step = {i,j,length};
                paths.push_back(nxt_step);
                id++;
            }
        }
    // We only care about the longest path
    sort(paths.begin(), paths.end(), compare);
    // We clear the array so for the DFS
    for(i=0;i<r;i++)
        for(j=0;j<c;j++)
            visited[i][j]=0;
    char count = '0';
    // We need to cruze our longest path length

    stack.push(make_pair(paths[paths.size()-1].start_i,paths[paths.size()-1].start_j));
    final[paths[paths.size()-1].start_i].replace(paths[paths.size()-1].start_j,1,1,count);    
    //Applying depth first search to only the path with maximum length  
    DFS(paths[paths.size()-1].start_i,paths[paths.size()-1].start_j, matrix, visited, final,count);
    // Print max path length
    cout << count << endl;
    // Print our Resulting Maze
    for(i = 0;i < r; i++) {
            for(j = 0; j < c; j++)
                cout << final[i][j];
            cout << endl;
        }
    return 0;
}