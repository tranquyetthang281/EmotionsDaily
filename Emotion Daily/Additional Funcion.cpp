#include "declare.h"
using namespace std;

void printBox(const int &x, const int &y)
{
	gotoXY(x, y); cout << char(218);
	gotoXY(x + LENGHTH_BOX - 1, y); cout << char(191);
	gotoXY(x, y + WIDTH_BOX - 1); cout << char(192);
	gotoXY(x + LENGHTH_BOX - 1, y + WIDTH_BOX - 1); cout << char(217);

	for (int i = 1; i < LENGHTH_BOX - 1; ++i)
	{
		gotoXY(x + i, y); cout << char(196);
		gotoXY(x + i, y + WIDTH_BOX - 1); cout << char(196);
	}
	for (int i = 1; i < WIDTH_BOX - 1; ++i)
	{
		gotoXY(x, y + i); cout << char(179);
		gotoXY(x + LENGHTH_BOX - 1, y + i); cout << char(179);
	}
}

void printTable(const int &X_ORIGIN_COORDINATE, const int &Y_ORIGIN_COORDINATE, const int &_ROWS, const int &_COLUMS, const int &LENGHTH_BOX, const int &WIDTH_BOX)
{
	const int LENGHTH_TABLE{ _ROWS * (LENGHTH_BOX - 1) + 1 };
	const int WIDTH_TABLE{ _COLUMS * (WIDTH_BOX - 1) + 1 };

	for (int y = Y_ORIGIN_COORDINATE; y <= WIDTH_TABLE - 1; y = y + WIDTH_BOX - 1)
		for (int x = X_ORIGIN_COORDINATE; x <= LENGHTH_TABLE - 1; ++x)
		{
			gotoXY(x, y); cout << char(196);
		}
	for (int x = X_ORIGIN_COORDINATE; x <= LENGHTH_TABLE - 1; x = x + LENGHTH_BOX - 1)
		for (int y = Y_ORIGIN_COORDINATE; y <= WIDTH_TABLE - 1; ++y)
		{
			gotoXY(x, y); cout << char(179);
		}

	gotoXY(X_ORIGIN_COORDINATE, Y_ORIGIN_COORDINATE); cout << char(218);
	gotoXY(X_ORIGIN_COORDINATE + LENGHTH_TABLE - 1, Y_ORIGIN_COORDINATE); cout << char(191);
	gotoXY(X_ORIGIN_COORDINATE, Y_ORIGIN_COORDINATE + WIDTH_TABLE - 1); cout << char(192);
	gotoXY(X_ORIGIN_COORDINATE + LENGHTH_TABLE - 1, Y_ORIGIN_COORDINATE + WIDTH_TABLE - 1); cout << char(217);

	for (int x = X_ORIGIN_COORDINATE + LENGHTH_BOX - 1; x < X_ORIGIN_COORDINATE + LENGHTH_TABLE - 1; x = x + LENGHTH_BOX - 1)
	{
		gotoXY(x, Y_ORIGIN_COORDINATE); cout << char(194);
		gotoXY(x, Y_ORIGIN_COORDINATE + WIDTH_TABLE - 1); cout << char(193);
	}
	for (int y = Y_ORIGIN_COORDINATE + WIDTH_BOX - 1; y < Y_ORIGIN_COORDINATE + WIDTH_TABLE - 1; y = y + WIDTH_BOX - 1)
	{
		gotoXY(X_ORIGIN_COORDINATE, y); cout << char(195);
		gotoXY(X_ORIGIN_COORDINATE + LENGHTH_TABLE - 1, y); cout << char(180);
	}

	for (int y = Y_ORIGIN_COORDINATE + WIDTH_BOX - 1; y < Y_ORIGIN_COORDINATE + WIDTH_TABLE - 1; y = y + WIDTH_BOX - 1)
		for (int x = X_ORIGIN_COORDINATE + LENGHTH_BOX - 1; x < X_ORIGIN_COORDINATE + LENGHTH_TABLE - 1; x = x + LENGHTH_BOX - 1)
		{
			gotoXY(x, y); cout << char(197);
		}
}

void printCalendar()
{

	printColorRectangle(X_ORIGIN_COORDINATE, Y_ORIGIN_COORDINATE - 2, LENGHTH_CALENDAR, 1, 119, 240);

	printColorText(X_ORIGIN_COORDINATE + LENGHTH_BOX / 2 - 1, Y_ORIGIN_COORDINATE - 2, 124, 112, "Sun");
	int set = LENGHTH_BOX - 2;
	cout << setw(set) << "Mon" << setw(set) << "Tue" << setw(set) << "Wed" << setw(set) << "Thu" << setw(set) << "Fri" << setw(set) << "Sat";
	TextColor(240);

	const char ch = 176;
	TextColor(247);
	//for (int x = X_ORIGIN_COORDINATE; x <= X_ORIGIN_COORDINATE + LENGHTH_CALENDAR - 1; x = x + LENGHTH_BOX - 2)
	//{
	//	gotoXY(x, Y_ORIGIN_COORDINATE - 2); cout << ch;
	//	gotoXY(x + 1, Y_ORIGIN_COORDINATE - 2); cout << ch;
	//}
	for (int y = Y_ORIGIN_COORDINATE; y <= Y_ORIGIN_COORDINATE + WIDTH_CALENDAR - 1; y = y + WIDTH_BOX - 1)
		for (int x = X_ORIGIN_COORDINATE; x <= X_ORIGIN_COORDINATE + LENGHTH_CALENDAR - 2; ++x)
		{
			gotoXY(x, y); cout << ch;
		}
	for (int x = X_ORIGIN_COORDINATE; x <= X_ORIGIN_COORDINATE + LENGHTH_CALENDAR - 2; x = x + LENGHTH_BOX - 2)
		for (int y = Y_ORIGIN_COORDINATE; y <= Y_ORIGIN_COORDINATE + WIDTH_CALENDAR - 1; ++y)
		{
			gotoXY(x, y); cout << ch;
			gotoXY(x + 1, y); cout << ch;
		}
	TextColor(240);
}

tm* now()
{
	time_t Time = time(NULL);
	return localtime(&Time);
}

int dayOfMonth(const int &month, const int &year)
{
	switch (month)
	{
	case 4:
	case 6:
	case 9:
	case 11:
		return 30;
	case 2:
		if ((year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0)))
			return 29;
		return 28;
	default:
		return 31;
	}
}

int dayOfMonth_Now()
{
	return dayOfMonth(now()->tm_mon + 1, now()->tm_year + 1900);
}