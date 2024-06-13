#include "pch.h"
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <clocale>

using namespace std;
using namespace System;
using namespace System::IO;

#define ENTER 13
#define ESC 27
#define UP 72
#define DOWN 80
#define HOME 71
#define END 79



struct z {
    char name[15];
    int data;
    int money;
    char tip[21];
    char color[10];
};

struct sp {
    char fio[30];
    long summa;
    struct sp* sled;
    struct sp* pred;
};

int menu(int);
void maxim(struct z*, int);
void first(struct z*, int);
void alfalist(struct z*, int, struct sp**);
void kolvo(struct z*, int);
void vstavka(struct z*, char*, int, struct sp**);
void vopros1(struct z*, int);
void diagram(struct z*, int, struct sp**);

int main(array<System::String^>^ args)
{
    int NC;
    char dan[][80] = {
        "Самый дорогой игрок?               ",
        "Какой игрок самый старший?",
        "Алфавитный список всех игроков     ",
        "Количество игроков в зеленой форме ",
        "Диаграмма стоимости игроков ",
        "Игроки по цвету формы и году рождения",
        "Выход             "
    };
    char BlankLine[] = " ";
    int i, n;
    FILE* in;
    struct z* clients;
    setlocale(LC_CTYPE, "Russian");
    Console::CursorVisible::set(false);
    Console::WindowWidth = 80;
    Console::WindowHeight = 50;
    Console::BufferHeight = Console::WindowHeight;
    Console::BufferWidth = Console::WindowWidth;
    Console::ForegroundColor = ConsoleColor::DarkCyan;
    Console::BackgroundColor = ConsoleColor::White;
    Console::Clear();

    if ((in = fopen("spisok.txt", "r")) == NULL)
    {
        printf("\nФайл spisik.txt не открыт !");
        getch(); exit(1);
    }
    fscanf(in, "%d", &NC);
    clients = (struct z*)malloc(NC * sizeof(struct z));
    for (i = 0; i < NC; i++)
        fscanf(in, "%s%d%d%s%s",
            clients[i].name,
            &clients[i].data,
            &clients[i].money,
            clients[i].tip,
            clients[i].color);
    for (i = 0; i < NC; i++)
        printf("\n %-10s %4d %-8d  %-20s  %-11s",
            clients[i].name,
            clients[i].data,
            clients[i].money,
            clients[i].tip,
            clients[i].color);

    getch();

    struct sp* spisok = 0;

    while (1)
    {
        Console::ForegroundColor = System::ConsoleColor::DarkCyan;
        Console::BackgroundColor = System::ConsoleColor::White;
        Console::Clear();
        Console::ForegroundColor = System::ConsoleColor::DarkCyan;
        Console::BackgroundColor = System::ConsoleColor::White;
        Console::CursorLeft = 30;
        Console::CursorTop = 12;
        printf(BlankLine);
        for (i = 0; i < 7; i++)
        {
            Console::CursorLeft = 10;
            Console::CursorTop = i + 5;
            printf(" %s ", dan[i]);
        }
        Console::CursorLeft = 10;
        Console::CursorTop = 12;
        printf(BlankLine);
        n = menu(8);
        switch (n) {
        case 1: maxim(clients, NC); break;
        case 2: first(clients, NC); break;
        case 3: alfalist(clients, NC, &spisok); break;
        case 4: kolvo(clients, NC); break;
        case 5: diagram(clients, NC, &spisok); break;
        case 6: vopros1(clients,NC); break;
        case 7: exit(0);
        }
    }
    return 0;
}
int menu(int n)
{
    char dan[][80] = {
        "Самый дорогой игрок?               ",
        "Какой игрок самый старший?",
        "Алфавитный список всех игроков     ",
        "Количество игроков в зеленой форме ",
        "Диаграмма стоимости игроков ",
        "Игроки по цвету формы и году рождения",
        "Выход             "
    };
    char BlankLine[] = " ";
    int y1 = 0, y2 = n - 1;
    char c = 1;
    while (c != ESC)
    {
        switch (c) {
        case DOWN: y2 = y1; y1++; break;
        case UP: y2 = y1; y1--; break;
        case ENTER: return y1 + 1;
        case HOME: y2 = y1; y1 = 0; break;
        case END: y2 = y1; y1 = n - 1; break;

        }
        if (y1 > n - 1) { y2 = n - 1; y1 = 0; }
        if (y1 < 0) { y2 = 0; y1 = n - 1; }
        Console::ForegroundColor = System::ConsoleColor::White;
        Console::BackgroundColor = System::ConsoleColor::Red;
        Console::CursorLeft = 11;
        Console::CursorTop = y1 + 5;
        printf(dan[y1]);
        Console::ForegroundColor = System::ConsoleColor::DarkCyan;
        Console::BackgroundColor = System::ConsoleColor::White;
        Console::CursorLeft = 11;
        Console::CursorTop = y2 + 5;
        printf(dan[y2]);
        c = getch();
    }
    exit(0);
}
void maxim(struct z* client, int NC)
{
    int i = 0;
    struct z best;
    strcpy(best.name, client[0].name);
    best.money = client[0].money;
    for (i = 1; i < NC; i++)
        if (client[i].money > best.money)
        {
            strcpy(best.name, client[i].name);
            best.money = client[i].money;
        }
    Console::ForegroundColor = System::ConsoleColor::White;
    Console::BackgroundColor = System::ConsoleColor::Red;
    Console::CursorLeft = 10;
    Console::CursorTop = 15;
    printf(" Самый дорогой игрок стоит - %d $ ", best.money);
    Console::CursorLeft = 10;
    Console::CursorTop = 16;
    printf(" Никнейм игрока - %s ", best.name);
    getch();
}
void kolvo(struct z* client, int NC)
{
    int i, k = 0;
    for (i = 0; i < NC; i++)
        if (strcmp(client[i].color, "Green") == 0)
            k++;
    Console::ForegroundColor = ConsoleColor::White;
    Console::BackgroundColor = ConsoleColor::Red;
    Console::CursorLeft = 10;
    Console::CursorTop = 15;
    printf(" Игроков в зеленой форме ");
    Console::CursorLeft = 10;
    Console::CursorTop = 16;
    printf(" Всего : %d ", k);
    getch();
}
void first(struct z* client, int NC)
{
    int i = 0;
    struct z best;
    strcpy(best.name, client[0].name);
    best.data = client[0].data;
    best.money = client[0].money;
    for (i = 1; i < NC; i++)
        if (client[i].data < best.data)
        {
            strcpy(best.name, client[i].name);
            best.data = client[i].data;
            best.money = client[i].money;
        }
    Console::ForegroundColor = System::ConsoleColor::White;
    Console::BackgroundColor = System::ConsoleColor::Red;
    Console::CursorLeft = 10;
    Console::CursorTop = 15;
    printf(" Самый старший игрок - %d года рождения. Его стоимость %d $ ", best.data, best.money);
    Console::CursorLeft = 10;
    Console::CursorTop = 16;
    printf(" Никнейм игрока %s ", best.name);
    getch();
}
void alfalist(struct z* client, int NC, struct sp** spisok) {
    int i, x; struct sp* nt, * z;
    x = 3;
    Console::ForegroundColor = ConsoleColor::Red;
    Console::BackgroundColor = ConsoleColor::White; Console::Clear();
    printf("\n Алфавитный список игроков и Обратный");
    printf("\n=================================================================\n");
    if (!*spisok)
        for (i = 0; i < NC; i++)
            vstavka(client, client[i].name, NC, spisok);
    for (nt = *spisok; nt != 0; nt = nt->sled)
    {
        Console::CursorLeft = 0;
        Console::CursorTop = x + 1;
        printf(" %-20s %d", nt->fio, nt->summa);
        x += 1;
    }
    x = 3;
    Console::CursorLeft = 40;
    Console::CursorTop = x + 1;
    for (nt = *spisok; nt != 0; z = nt, nt = nt->sled);
    for (nt = z, i = 0; nt != 0; i++, nt = nt->pred)
    {
        Console::CursorLeft = 40;
        Console::CursorTop = x + 1;
        printf(" %-20s %d", nt->fio, nt->summa);
        x += 1;
    }
    getch();
}
void vstavka(struct z* client, char* fio, int NC, struct sp** spisok)
{
    int i;
    struct sp* New, * nt, * z = 0;
    for (nt = *spisok; nt != 0 && strcmp(nt->fio, fio) < 0; z = nt, nt = nt->sled);
    if (nt && strcmp(nt->fio, fio) == 0) return;
    New = (struct sp*)malloc(sizeof(struct sp));
    strcpy(New->fio, fio);
    New->sled = nt;//ссылка не следующий
    New->summa = 0;
    if (nt) nt->pred = New;
    New->pred = z; //ссылка не предыдущий
    for (i = 0; i < NC; i++)
        if (strcmp(client[i].name, fio) == 0)
            New->summa += client[i].money;
    if (!z) *spisok = New;
    else z->sled = New;
    return;
}
void vopros1(struct z* client, int NC)
{
    int i;
    struct sp* nov, * nt, * z = 0;
    bool flag = false;
    Console::ForegroundColor = ConsoleColor::DarkCyan;
    Console::BackgroundColor = ConsoleColor::White;
    Console::Clear();
    printf(" Игроки в зеленой форме и рождены в 1991 году \n----------------------------------------------\n");
    for (i = 0; i < NC; i++)
    {

        if (strcmp(client[i].color, "Green") == 0 && client[i].data == 1991)
        {
            printf("  %-20s  %s  %d\n", client[i].name, client[i].color, client[i].data);
            flag = true;
        }
    }
    if (!flag)
    {
        printf(" Такие игроки отсутствуют ");
    }
    getch();
    return;
}

void diagram(struct z* client, int NC, struct sp** spisok)
{
    struct sp* nt;
    int len, i, NColor;
    long sum = 0;
    char str1[20];
    char str2[20];
    System::ConsoleColor Color; Console::ForegroundColor =
        System::ConsoleColor::Yellow;
    Console::BackgroundColor = System::ConsoleColor::White;
    Console::Clear();
    for (i = 0; i < NC; i++) sum = sum + client[i].money;
    if (!*spisok)
        for (i = 0; i < NC; i++)
            vstavka(client, client[i].name, NC, spisok);
    Color = System::ConsoleColor::Black; NColor = 0;
    for (nt = *spisok, i = 0; nt != 0; nt = nt->sled, i++)
    {
        sprintf(str1, "%s", nt->fio);
        sprintf(str2, "%3.1f%%", (nt->summa * 100. / sum));
        Console::ForegroundColor = System::ConsoleColor::DarkCyan;
        Console::BackgroundColor = System::ConsoleColor::White;
        Console::CursorLeft = 5;
        Console::CursorTop = i + 1; printf(str1);
        Console::CursorLeft = 20; printf(str2);
        Console::BackgroundColor = ++Color;
        Console::CursorLeft = 30;
        for (len = 0; len < nt->summa * 50 / sum; len++)
            printf(" ");
        if (NColor == 14) Color = ConsoleColor::Black; NColor = 0;
    }
    getch();
    return;
}