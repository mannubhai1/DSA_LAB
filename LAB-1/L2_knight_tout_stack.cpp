#include <iostream>
#include <stack>
#include <bits/stdc++.h>

using namespace std;

const int N = 8; // size of the chessboard
int dx[] = {2, 1, -1, -2, -2, -1, 1, 2};
int dy[] = {1, 2, 2, 1, -1, -2, -2, -2};

bool isValid(int x, int y)
{
    return (x >= 0 && x < N && y >= 0 && y < N);
}

int getDegree(int x, int y, int chessboard[N][N])
{
    int cnt = 0;
    for (int i = 0; i < 8; i++)
    {
        int newX = x + dx[i];
        int newY = y + dy[i];
        if (isValid(newX, newY) && chessboard[newX][newY] == -1)
            cnt++;
    }
    return cnt;
}

void knightTour(int x, int y, int chessboard[N][N], stack<pair<int, int>> &s)
{
    chessboard[x][y] = 0;
    s.push(make_pair(x, y));

    while (!s.empty())
    {
        int minDegree = 8;
        int minX = -1, minY = -1;
        for (int i = 0; i < 8; i++)
        {
            int newX = x + dx[i];
            int newY = y + dy[i];
            if (isValid(newX, newY) && chessboard[newX][newY] == -1)
            {
                int degree = getDegree(newX, newY, chessboard);
                if (degree < minDegree)
                {
                    minDegree = degree;
                    minX = newX;
                    minY = newY;
                }
            }
        }
        if (minX == -1 && minY == -1)
        {
            s.pop();
            if (!s.empty())
            {
                x = s.top().first;
                y = s.top().second;
            }
        }
        else
        {
            x = minX;
            y = minY;
            chessboard[x][y] = s.size();
            s.push(make_pair(x, y));
        }
    }
}

int main()
{
    int chessboard[N][N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            chessboard[i][j] = -1;

    stack<pair<int, int>> s;
    knightTour(0, 0, chessboard, s);

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            printf("%d ", chessboard[i][j]);
        printf("\n");
    }
    return 0;
}
