# include <windows.h> //библиотека для Sleep()
# include <conio.h> // библиотека для  _kbhit() и _getch()
# include <ctime> // библиотека для time
# include <iostream>

using namespace std;
int move_x, //в какую сторону змейка движется (вдоль x)
move_y, //в какую сторону змейка движется (вдоль у)
sn_size, //текущий размер змейки
position_x[1000], position_y[1000], //массивы, хранящие координаты х и у частей змейки соответственно
point_x = -1, point_y = -1; //координаты еды

char ascii, // тут находится ASCII код нажатой клавиши
a[1000][1000]; //игровое поле (выводится на экран в виде матрицы)
const int N = 15, M = 15, //высота, ширина игрового поля соответственно 
waaait = 300; //через этот промежуток времени змейка передвигается (в миллисекундах)

void start_options()
// начальные установки
{
	sn_size = 2;
	//начальный размер змейки - 2

	position_x[1] = 1;
	position_y[1] = 2;
	position_x[2] = 1;
	position_y[2] = 1;
	// змейка занимает две клетки вправо от координаты {1,1}

	move_x = 1;
	move_y = 0;
	// змейка движется вниз
}

void check_key()
// функция, считывающая нажатую клавишу
{
	ascii = _getch();
	// считываем нажатую клавишу с помощью функции getch()
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
		// изменение направления движения змейки
	}
}

void snake_delete()
// удаляем змейку с поля (путем замены всех частей ее тела пробелами)
{
	for (int i = 1; i <= sn_size; ++i)
		a[position_x[i]][position_y[i]] = ' ';
}

void check_out()
// проверяем, вышла ли змейка за пределы поля
{
	if (position_x[1] > N) position_x[1] = 1;
	if (position_x[1] < 1) position_x[1] = N;
	if (position_y[1] > M) position_y[1] = 1;
	if (position_y[1] < 1) position_y[1] = M;
}

void show_snake()
//  показываем змейку
{
	if (move_x == 1 && move_y == 0) a[position_x[1]][position_y[1]] = 'v';
	if (move_x == -1 && move_y == 0) a[position_x[1]][position_y[1]] = '^';
	if (move_x == 0 && move_y == 1) a[position_x[1]][position_y[1]] = '>';
	if (move_x == 0 && move_y == -1) a[position_x[1]][position_y[1]] = '<';
	// изменение тип головы

	for (int i = 2; i <= sn_size; ++i)
		a[position_x[i]][position_y[i]] = '*';
	// показываем змейку
}
bool game_over()
// проверяем, съела ли змейка саму себя
{
	for (int i = 2; i <= sn_size; ++i)
		if (position_x[1] == position_x[i] && position_y[1] == position_y[i]) return true;
	return false;
	// если змейка съела саму себя возвращаем true, если нет-false
}
void move_snake()
// функция передвижения змейки
{
	snake_delete();
	// чистим игровое поле от змейки

	for (int i = sn_size; i >= 2; --i)
	{
		position_x[i] = position_x[i - 1];
		position_y[i] = position_y[i - 1];
	}
	// передвигаем змейку

	position_x[1] += move_x;
	position_y[1] += move_y;
	// передвигаем голову змейки

	check_out();
	// проверка на выход за пределы поля

	if (position_x[1] == point_x && position_y[1] == point_y)
	{
		sn_size++;
		point_x = -1;
		point_y = -1;
	}
	// если голова змейки там же где и еда, то увеличиваем размер змейки и очищаем координаты еды

	show_snake();
	// показываем змейку

	if (game_over() == true)
		// если змейка укусила себя
	{
		cout << "Game over" << endl;
		cout << "Points picked up : " << sn_size - 2 << endl;
		// выводим сообщение о конце игры
		Sleep(2000);
		system("pause");
		// приостанавливаем игру
		exit(0);
		// завершение
	}
}
bool food_check()
// функция проверки наличия еды на карте
{
	if (point_x == -1 && point_y == -1) return false;
	// если еды нет, возвращаем false
	return true;
	// если определены-true
}
void place_food()
// добавление еды на карту
{
	srand(time(NULL)); //генератор случайных чисел
	for (int i = 1; i <= 9; ++i)
	{
		int x = rand(), y = rand(); //генерируем случайные координаты	
		if (x < 0) x *= -1;
		if (y < 0) y *= -1;
		x %= (N + 1);
		y %= (M + 1);
		if (x == 0) ++x;
		if (y == 0) ++y;
		if (a[x][y] != '*' && a[x][y] != 'v' && a[x][y] != '^' && a[x][y] != '<' && a[x][y] != '>')
			// редактирование координат
		{
			point_x = x;
			point_y = y;
			a[x][y] = '+';
			return;
			// ставим еду в эти координаты
		}
	}
}

void show_field()
// функция для вывода таблицы
{
	system("cls");
	// очистка консоль
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

	// выводим игровое поле
}
int main()
{
	for (int i = 0; i <= N + 1; ++i)
		for (int j = 0; j <= M + 1; ++j)
			a[i][j] = ' '; // создаем поле

	start_options();
	// задаем начльное состояние змейки

	for (;;)
		//цикл игры
	{
		if (_kbhit() == true)
			// если нажата клавиша
			check_key();
		// обрабатываем нажатую клавишу

		move_snake();
		// передвигаем змейку

		if (food_check() == false)
			place_food();
		// ставим еду, в случае ее отсутствия
		show_field();
		// показываем игровое поле 

		Sleep(waaait); //(wait);
					   // "паузим" программу время wait
	}
}