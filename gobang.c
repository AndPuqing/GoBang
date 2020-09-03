#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

#define width 16
#define high 16

int map[high][width];

void gotoxy(int x, int y)
{
    COORD pos = {x, y};
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); // 获取标准输出设备句柄
    SetConsoleCursorPosition(hOut, pos);           //两个参数分别是指定哪个窗体，具体位置
}
void dawn()
{
    for (int i = 0; i < high; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (map[i][j] == 0)
            {
                _cprintf(" ");
            }
            else if (map[i][j] == 1)
            {
                _cprintf("O");
            }
            else
            {
                _cprintf("@");
            }
            if (j == (width - 1))
            {
                _cprintf("\n");
            }
        }
    }
}
int sum()
{
    for (int i = 0; i < high; i++)
    {
        for (int j = 0; j < width - 4; j++)
        {
            if (map[i][j] == map[i][j + 1] && map[i][j + 1] == map[i][j + 2] && map[i][j + 2] == map[i][j + 3] && map[i][j + 3] == map[i][j + 4] && map[i][j] != 0)
            {
                return 0;
            }
        }
    }
    for (int j = 0; j < width; j++)
    {
        for (int i = 0; i < high - 4; i++)
        {
            if (map[i][j] == map[i + 1][j] && map[i + 1][j] == *(map[i + 2] + j) && *(map[i + 2] + j) == *(map[i + 3] + j) && *(map[i + 3] + j) == *(map[i + 4] + j) && *(map[i] + j) != 0)
            {
                return 0;
            }
        }
    }
    for (int i = 0; i < high - 4; i++)
    {
        for (int j = 0; j < width - 4; j++)
        {
            if (map[i][j] == *(map[i + 1] + j + 1) && *(map[i + 1] + j + 1) == *(map[i + 2] + j + 2) && *(map[i + 2] + j + 2) == *(map[i + 3] + j + 3) && *(map[i + 3] + j + 3) == *(map[i + 4] + j + 4) && *(map[i] + j) != 0)
            {
                return 0;
            }
        }
    }
    for (int i = 0; i < high - 4; i++)
    {
        for (int j = 0; j < width - 4; j++)
        {
            if (map[i][j] == *(map[i + 1] + j + 1) && *(map[i + 1] + j + 1) == *(map[i + 2] + j + 2) && *(map[i + 2] + j + 2) == *(map[i + 3] + j + 3) && *(map[i + 3] + j + 3) == *(map[i + 4] + j + 4) && *(map[i] + j) != 0)
            {
                return 0;
            }
        }
    }
    for (int i = 0; i < high - 4; i++)
    {
        for (int j = 4; j < width; j++)
        {
            if (*(map[i] + j) == *(map[i + 1] + j - 1) && *(map[i + 1] + j - 1) == *(map[i + 2] + j - 2) && *(map[i + 2] + j - 2) == *(map[i + 3] + j - 3) && *(map[i + 3] + j - 3) == *(map[i + 4] + j - 4) && *(map[i] + j) != 0)
            {
                return 0;
            }
        }
    }
    return 1;
}
int ai(int x, int y)
{
    int max = -1;
    int f = 0;
    int g = 0;
    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            if ((map[x + i][y + j] + map[x + 2 * i][y + 2 * j] + map[x + 3 * i][y + 3 * j]) > max && ((i != 0) || (j != 0)))
            {
                max = map[x + i][y + j] + map[x + 2 * i][y + 2 * j] + map[x + 3 * i][y + 3 * j];
                f = i;
                g = j;
            }
            //_cprintf("%d", max);
        }
    }
    while (map[x - f][y - g] != 0)
    {
        int a;
        srand((unsigned)time(NULL));
        a = rand() % 5 - 2;
        f *= a;
        g *= -a;
        if (map[x - f][y - g] == 0)
        {
            break;
        }
    }
    map[x - f][y - g] = -1;
}
int main(void)
{
    for (int i = 0; i < high; i++)
    {
        for (int j = 0; j < width; j++)
        {
            map[i][j] = 0;
        }
    }
    int x = 3, y = 5;
    _cprintf("This is a gobang game software.\nwasd contral motion.The blank contral enter.\nEnjoy it.\n");
    gotoxy(x, y);
    int ch;
    int i = 1;
    int mod = 1;
    while (sum())
    {
        ch = getch();
        switch (ch)
        {
        case 119:
            y--;
            break;
        case 115:
            y++;
            break;
        case 97:
            x--;
            break;
        case 100:
            x++;
            break;
        case 32:
            if (mod == 1)
            {
                map[y][x] = i;
                i *= -1;
            }
            else
            {
                map[y][x] = i;
                ai(y, x);
            }
            break;
        case 113:
            mod *= -1;
            break;
        default:
            break;
        }
        system("cls");
        dawn();
        gotoxy(0, 20);
        if (x > width - 1 || y > high - 1)
        {
            _cprintf("You are out of position.\nPlease go back.");
        }
        else
        {
            if (mod == 1)
            {
                _cprintf("PVP x=%d y=%d", x, y);
            }
            else
            {
                _cprintf("PVE x=%d y=%d", x, y);
            }
        }
        gotoxy(x, y);
    }
    system("cls");
    dawn(map);
    gotoxy(0, 21);
    _cprintf("Game over");
    getch();
}
