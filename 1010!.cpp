#include <iostream>
#include <cstring>
#include <time.h>

using namespace std;

bool become[8][8];
bool image[3][3];

void show()
{
	memset(image, false, sizeof(image));
	srand((unsigned)time(NULL));
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			int sec = rand() % 2;
			image[i][j] = sec;
		}
	}
	bool image_decide[3][3];
	memset(image_decide, 0, sizeof(image_decide));
	int x = 0,y = 0;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (image[i][j] == 0)
			{
				continue;
			}
			else if (image[i][j] == 1)
			{
				image_decide[x][y++] = image[i][j];
			}
		}
		y = 0;
		x++;
	}
	memset(image, 0, sizeof(image));
	x = 0;
	y = 0;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (image_decide[j][i] == 0)
			{
				continue;
			}
			else if (image_decide[j][i] == 1)
			{
				image[y++][x] = image_decide[j][i];
			}
		}
		y = 0;
		x++;
	}
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (image[i][j] == 1)
			{
				cout << "* ";
			}
			else if (image[i][j] == 0)
			{
				cout << "  ";
			}
		}
		cout << endl; 
	}
}

void checkDisap()
{
	for (int i = 0; i < 8; ++i)
	{
		bool flag = true;
		if (become[i][0] == 1)
		{
			for (int a = 0; a < 8; ++a)
			{
				if (become[i][a] != 1)
				{
					flag = false;
					break;
				}
			}
			if (flag == true)
			{
				for (int a = 0; a < 8; ++a)
				{
					become[i][a] = 0;
				}
			}
		}
	}

	for (int i = 0; i < 8; ++i)
	{
		bool flag = true;
		if (become[0][i] == 1)
		{
			for (int a = 0; a < 8; ++a)
			{
				if (become[a][i] != 1)
				{
					flag = false;
					break;
				}
			}
			if (flag == true)
			{
				for (int a = 0; a < 8; ++a)
				{
					become[a][i] = 0;
				}
			}
		}
	}
}

bool ifCanPut(bool image[3][3])
{
	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < 6; ++j)
		{
			if (become[i][j] == 1)
			{
				continue;
			}
			bool fault = false;
			for (int a = 0; a < 3; ++a)
			{
				for (int b = 0; b < 3; ++b)
				{
					if (become[i + a][j + b] == 1 && image[a][b] == 1)
					{  
						fault = true;
						break;
					}
				}
				if (fault)
				{
					break;
				}
			}
			if (fault)
			{
				continue;
			}
			return true;
		}
	}
	return false;
}

bool singleCanPut(int x, int y, bool image[3][3])
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (become[x + i][y + j] == 1 && image[i][j] == 1)
			{
				return false;
			}
		}
	}
	return true;
}

void printSurface()
{
	system("cls");
	cout << "  0 1 2 3 4 5 6 7" << endl;
	for (int i = 0; i < 8; ++i)
	{
		cout << i << " ";
		for (int j = 0; j < 8; ++j)
		{
			if (become[i][j] == 0)
			{
				cout << ". ";
			}
			else
			{
				cout << "# ";
			}
		}
		cout << endl;
	}
	cout << endl << endl;
	return ;
}

void setSurface(int x, int y, bool image[3][3])
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if(image[i][j] == 1)
			{
				become[x + i][y + j] = 1;
			}
		}
	}
	return ;
}

int main()
{
	printSurface();
	show();

enter:
	cout << "Please enter the coordinate (e.g. 0 0):";
	int x, y;
	cin >> x >> y;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (x >= 8 || y >= 8 || (x >= 6 && image[i + x][j + y] == 1) || (y >= 6 && image[i + x][j + y] == 1))
			{
				cout << "You have entered a wrong coordinate!" << endl;
				goto enter;
			}
		}
	}
	if (!singleCanPut(x, y, image))
	{
		cout << "You can't put it there!" << endl;
		goto enter;
	}

run:
	setSurface(x, y, image);
	printSurface();
	checkDisap();
	printSurface();
	show();
	if (!ifCanPut(image))
	{
		goto end;
	}
	goto enter;

end:
	cout << "Game Over!" << endl;

	return 0;
}
