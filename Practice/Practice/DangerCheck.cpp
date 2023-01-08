#include <iostream>
#include <vector>

using namespace std;

struct Line
{
    Line(int x, int y) : x(x), y(y) {}

    Line operator+(const Line& other) const
    {
        return Line(x + other.x, y + other.y);
    }
    int x;
    int y;
};

void Danger(vector<vector<bool>>& dangerous, const vector<vector<int>>& board, const Line& pos)
{
    dangerous[pos.y][pos.x] = true;
    vector<Line> direction = {
        {0, 1},
        {1, 0},
        {0, -1},
        {-1, 0},
        {1, 1},
        {1, -1},
        {-1, 1},
        {-1, -1}
    };
    for (int i = 0; i < 8; i++)
    {
        Line newPos = pos + direction[i];
        if (newPos.x == -1 || newPos.x == board[0].size())
            continue;
        if (newPos.y == -1 || newPos.y == board.size())
            continue;
        if (dangerous[newPos.y][newPos.x] == true)
            continue;
        dangerous[newPos.y][newPos.x] = true;
    }
}

int solution(vector<vector<int>> board) {
    int ySize = board.size();
    int xSize = board[0].size();
    vector<vector<bool>> dangerous(ySize, vector<bool>(xSize, false));
    
    for (int y = 0; y < ySize; y++)
    {
        for (int x = 0; x < xSize; x++)
        {
            if (board[y][x] == 1)
                Danger(dangerous, board, Line(x, y));
        }
    }

    int answer = 0;

    for (int y = 0; y < ySize; y++)
    {
        for (int x = 0; x < xSize; x++)
        {
            if (dangerous[y][x] == false)
                answer++;
        }
    }
    return answer;
}

int main()
{
    vector<vector<int>> board = {
        {0,0,0,0,0},
        {0,1,0,1,0},
        {0,0,0,0,0},
        {0,1,0,1,0},
        {0,0,0,0,0} };
    int answer = solution(board);

	return 0;
}