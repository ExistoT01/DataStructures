#include "myStack.h"


class solution {
private:
	int dx[4] = { -1,1,0,0 };
	int dy[4] = { 0,0,-1,1 };
	string direction[4] = { "北", "南", "西", "东" };
	
public:	
	void maze(vector<vector<char> >& grid, PosType current, PosType end) {
		int nRow, nCol;
		nRow = grid.size();
		nCol = grid[0].size();
		MyStack* stk = new MyStack();
		stk->push(current);
		grid[current.x][current.y] = '1';

		while (!stk->empty()) {
			PosType pos = stk->top();
			stk->pop();

			if (pos.x == end.x && pos.y == end.y) {
				grid[pos.x][pos.y] = '0';
				printMaze(grid);
				return;
			}

			int dir = getDirection(pos.x, pos.y, end.x, end.y);

			PosType newPos;
			for (int i = 0; i < 4; ++i) {
				newPos.x = pos.x + dx[dir % 4];
				newPos.y = pos.y + dy[dir % 4];
				dir++;
				if (newPos.x >= 0 && newPos.x < nRow
					&& newPos.y >= 0 && newPos.y < nCol
					&& grid[newPos.x][newPos.y] == '0' ) {
					stk->push(newPos);
					grid[newPos.x][newPos.y] = '1';
				}
			}
		}

	}

	// 贪心求起点最优方向，以起点到终点的横纵坐标之差为准
	int getDirection(int x1, int y1, int x2, int y2) {
		int diff_x, diff_y;
		diff_x = abs(x1 - x2);
		diff_y = abs(y1 - y2);
		if (diff_x < diff_y) {
			if (x2 > x1)
				return 1;
			else
				return 0;
		}
		else {
			if (y2 > y1)
				return 3;
			else
				return 2;
		}
	}

	void dfs(vector<vector<char> >& grid, MyStack* stk, PosType current, PosType end) {
		int nRow, nCol;
		nRow = grid.size();
		nCol = grid[0].size();

		if (current.x == end.x && current.y == end.y) {
			printMaze(grid);
			printStack(stk);
			return;
		}

		int nx, ny;

		grid[current.x][current.y] = '1';

		int dir = getDirection(current.x, current.y, end.x, end.y);

		for (int i = 0; i < 4; ++i) {
			nx = current.x + dx[dir % 4];
			ny = current.y + dy[dir % 4];
			if (nx >= 0 && nx < nRow
				&& ny >= 0 && ny < nCol
				&& grid[nx][ny] == '0') {
				grid[nx][ny] = '1';
				PosType newPos(nx, ny, direction[dir % 4], stk->top().index + 1);
				stk->push(newPos);

				dfs(grid, stk, newPos, end);

				stk->pop();
				grid[nx][ny] = '0';
			}
			dir++;
		}

	}

	void mazeSolution(vector<vector<char> >& grid, PosType start, PosType end) {
		MyStack* steps = new MyStack();
		steps->push(start);

		dfs(grid, steps, start, end);
	}
	
	void printMaze(vector<vector<char> >& grid) {
		for (auto it = grid.begin(); it != grid.end(); ++it) {
			for (int i = 0; i < (*it).size(); ++i) {
				cout << (*it)[i] << " ";
			}
			cout << endl;
		}
	}

	void printPosition(PosType p) {
		cout << "( " << p.x << ", " << p.y << " )" << endl;
	}

	void printStack(MyStack* stk) {
		MyStack* transfer = new MyStack();
		ListNode* cur = stk->getHead();
		while (cur) {
			transfer->push(cur->val);
			cur = cur->next;
		}

		while (!transfer->empty()) {
			cout << setw(2) << transfer->top().index+1 << ". ";
			cout << "row:" << transfer->top().x << " ";
			cout << "col:" << transfer->top().y << " ";
			transfer->pop();
			if (transfer->empty()) {
				cout << endl << endl;
				break;
			}
			cout << "direction: " << transfer->top().dir << " ";
			cout << endl << endl;			
		}
	}


};

int main() {
	solution sol;
	vector<vector<char> > grid = 
	{ {'#','#','#','#','#','#','#','#','#','#'},
{'#','0','0','#','0','0','0','#','0','#'},
{'#','0','0','#','0','0','0','#','0','#'},
{'#','0','0','#','0','#','#','#','0','#'},
{'#','0','#','#','0','0','0','#','0','#'},
{'#','0','0','0','0','#','0','0','0','#'},
{'#','0','#','0','0','0','#','0','0','#'},
{'#','#','#','0','#','0','#','#','0','#'},
{'#','0','0','0','0','0','0','0','0','#'},
{'#','#','#','#','#','#','#','#','#','#'} };

	vector<vector<char> > gridCopy(grid);
	//sol.printMaze(gridCopy);

	PosType start(3, 2, "起点", 0);
	PosType end(1, 8, "终点", 0);
	sol.mazeSolution(gridCopy, start, end);
	//sol.maze(gridCopy, start, end);

	return 0;
}