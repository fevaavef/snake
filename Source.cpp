# include <windows.h> //���������� ��� Sleep()
# include <conio.h> // ���������� ���  _kbhit() � _getch()
# include <ctime> // ���������� ��� time
# include <iostream>

using namespace std;
int move_x, //� ����� ������� ������ �������� (����� x)
move_y, //� ����� ������� ������ �������� (����� �)
sn_size, //������� ������ ������
position_x[1000], position_y[1000], //�������, �������� ���������� � � � ������ ������ ��������������
point_x = -1, point_y = -1; //���������� ���

char ascii, // ��� ��������� ASCII ��� ������� �������
a[1000][1000]; //������� ���� (��������� �� ����� � ���� �������)
const int N = 15, M = 15, //������, ������ �������� ���� �������������� 
waaait = 300; //����� ���� ���������� ������� ������ ������������� (� �������������)

void start_options()
// ��������� ���������
{
	sn_size = 2;
	//��������� ������ ������ - 2

	position_x[1] = 1;
	position_y[1] = 2;
	position_x[2] = 1;
	position_y[2] = 1;
	// ������ �������� ��� ������ ������ �� ���������� {1,1}

	move_x = 1;
	move_y = 0;
	// ������ �������� ����
}

void check_key()
// �������, ����������� ������� �������
{
	ascii = _getch();
	// ��������� ������� ������� � ������� ������� getch()
	switch (ascii)
	{
	case 'w':
		if (move_x != 1 || move_y != 0)
		{
			move_x = -1; move_y = 0;
		}
		break;
	case 'a':
		if (move_x != 0 || move_y != 1)
		{
			move_x = 0; move_y = -1;
		}
		break;
	case 's':
		if (move_x != -1 || move_y != 0)
		{
			move_x = 1; move_y = 0;
		}
		break;
	case 'd':
		if (move_x != 0 || move_y != -1)
		{
			move_x = 0; move_y = 1;
		}
		break;
		// ��������� ����������� �������� ������
	}
}

void snake_delete()
// ������� ������ � ���� (����� ������ ���� ������ �� ���� ���������)
{
	for (int i = 1; i <= sn_size; ++i)
		a[position_x[i]][position_y[i]] = ' ';
}

void check_out()
// ���������, ����� �� ������ �� ������� ����
{
	if (position_x[1] > N) position_x[1] = 1;
	if (position_x[1] < 1) position_x[1] = N;
	if (position_y[1] > M) position_y[1] = 1;
	if (position_y[1] < 1) position_y[1] = M;
}

void show_snake()
//  ���������� ������
{
	if (move_x == 1 && move_y == 0) a[position_x[1]][position_y[1]] = 'v';
	if (move_x == -1 && move_y == 0) a[position_x[1]][position_y[1]] = '^';
	if (move_x == 0 && move_y == 1) a[position_x[1]][position_y[1]] = '>';
	if (move_x == 0 && move_y == -1) a[position_x[1]][position_y[1]] = '<';
	// ��������� ��� ������

	for (int i = 2; i <= sn_size; ++i)
		a[position_x[i]][position_y[i]] = '*';
	// ���������� ������
}
bool game_over()
// ���������, ����� �� ������ ���� ����
{
	for (int i = 2; i <= sn_size; ++i)
		if (position_x[1] == position_x[i] && position_y[1] == position_y[i]) return true;
	return false;
	// ���� ������ ����� ���� ���� ���������� true, ���� ���-false
}
void move_snake()
// ������� ������������ ������
{
	snake_delete();
	// ������ ������� ���� �� ������

	for (int i = sn_size; i >= 2; --i)
	{
		position_x[i] = position_x[i - 1];
		position_y[i] = position_y[i - 1];
	}
	// ����������� ������

	position_x[1] += move_x;
	position_y[1] += move_y;
	// ����������� ������ ������

	check_out();
	// �������� �� ����� �� ������� ����

	if (position_x[1] == point_x && position_y[1] == point_y)
	{
		sn_size++;
		point_x = -1;
		point_y = -1;
	}
	// ���� ������ ������ ��� �� ��� � ���, �� ����������� ������ ������ � ������� ���������� ���

	show_snake();
	// ���������� ������

	if (game_over() == true)
		// ���� ������ ������� ����
	{
		cout << "Game over" << endl;
		cout << "Points picked up : " << sn_size - 2 << endl;
		// ������� ��������� � ����� ����
		Sleep(2000);
		system("pause");
		// ���������������� ����
		exit(0);
		// ����������
	}
}
bool food_check()
// ������� �������� ������� ��� �� �����
{
	if (point_x == -1 && point_y == -1) return false;
	// ���� ��� ���, ���������� false
	return true;
	// ���� ����������-true
}
void place_food()
// ���������� ��� �� �����
{
	srand(time(NULL)); //��������� ��������� �����
	for (int i = 1; i <= 9; ++i)
	{
		int x = rand(), y = rand(); //���������� ��������� ����������	
		if (x < 0) x *= -1;
		if (y < 0) y *= -1;
		x %= (N + 1);
		y %= (M + 1);
		if (x == 0) ++x;
		if (y == 0) ++y;
		if (a[x][y] != '*' && a[x][y] != 'v' && a[x][y] != '^' && a[x][y] != '<' && a[x][y] != '>')
			// �������������� ���������
		{
			point_x = x;
			point_y = y;
			a[x][y] = '+';
			return;
			// ������ ��� � ��� ����������
		}
	}
}

void show_field()
// ������� ��� ������ �������
{
	system("cls");
	// ������� �������
	for (int i = 0; i <= N + 1; ++i)
		for (int j = 0; j <= M + 1; ++j)
		{
			if (i == 0 || j == 0 || i == N + 1 || j == M + 1)
			{
				cout << "#";
			}
			else
			{
				cout << a[i][j];
			}
			if (j <= M)
			{
				cout << "";
			}
			else
			{
				cout << endl;
			}
		}

	// ������� ������� ����
}
int main()
{
	for (int i = 0; i <= N + 1; ++i)
		for (int j = 0; j <= M + 1; ++j)
			a[i][j] = ' '; // ������� ����

	start_options();
	// ������ �������� ��������� ������

	for (;;)
		//���� ����
	{
		if (_kbhit() == true)
			// ���� ������ �������
			check_key();
		// ������������ ������� �������

		move_snake();
		// ����������� ������

		if (food_check() == false)
			place_food();
		// ������ ���, � ������ �� ����������
		show_field();
		// ���������� ������� ���� 

		Sleep(waaait); //(wait);
					   // "������" ��������� ����� wait
	}
}