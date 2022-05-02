#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <fstream>
#include"console.h"
using namespace std;

#include "declare.h"

const int x_origin_coordinate = X_ORIGIN_COORDINATE;
const int y_origin_coordinate = Y_ORIGIN_COORDINATE + WIDTH_CALENDAR + WIDTH_BOX + 2;
const int lenght = MAX_X - X_ORIGIN_COORDINATE;
const int width = MAX_Y - Y_ORIGIN_COORDINATE - WIDTH_CALENDAR - WIDTH_BOX - 2;

class Text
{
private:
	vector<Text> text;
	char ch;
	int x;
	int y;
public:
	Text(string str)
	{
		for (const char &item : str)
		{
			text.resize(text.size() + 1);
			text[text.size() - 1].ch = item;
		}

		int _x = x_origin_coordinate;
		int _y = y_origin_coordinate;

		for (Text &item : text)
		{
			if (item.ch != '|')
			{
				item.x = _x++;
				item.y = _y;
			}
			else
			{
				x = x_origin_coordinate;
				++_y;
			}
		}
	}

	string str()
	{
		string str;
		for (const Text &item : text)
		{
			str.push_back(item.ch);
		}

		return str;
	}
	void edit()
	{
		int xCursor;
		int yCursor;
		char chCursor = '_';

		if (text.empty())
		{
			xCursor = x_origin_coordinate;
			yCursor = y_origin_coordinate;
		}
		else
		{
			print();
			if (text[text.size() - 1].ch != '|')
			{
				xCursor = text[text.size() - 1].x + 1;
				yCursor = text[text.size() - 1].y;
			}
			else
			{
				xCursor = x_origin_coordinate;
				yCursor = text[text.size() - 2].y + 1;
			}
		
		}
		gotoXY(xCursor, yCursor); cout << chCursor;

		while (true)
		{
			if (_kbhit())
			{
				char key = _getch();

				if (key == 13)
				{
					text.resize(text.size() + 1);
					text[text.size() - 1].ch = '|';
					gotoXY(xCursor, yCursor); cout << ' ';
					xCursor = x_origin_coordinate;
					++yCursor;
				}
				else if (key == 8)
				{
					if (!text.empty())
					{
						if (xCursor != x_origin_coordinate)
						{
							gotoXY(xCursor, yCursor); cout << ' ';
							xCursor = text[text.size() - 1].x;
							yCursor = text[text.size() - 1].y;
						}
						else
						{
							gotoXY(xCursor, yCursor); cout << ' ';
							xCursor = text[text.size() - 2].x + 1;
							yCursor = text[text.size() - 2].y;
						}
						text.pop_back();
					}
				}
				else if (key == 27)
				{
					gotoXY(xCursor, yCursor); cout << ' ';
					break;
				}
				else
				{
					text.resize(text.size() + 1);
					text[text.size() - 1].ch = key;
					text[text.size() - 1].x = xCursor;
					text[text.size() - 1].y = yCursor;
					gotoXY(xCursor, yCursor); cout << key;
					++xCursor;

					if ((xCursor > lenght - 20) && key == 32)
					{
						text.resize(text.size() + 1);
						text[text.size() - 1].ch = '|';
						gotoXY(xCursor, yCursor); cout << ' ';
						xCursor = x_origin_coordinate;
						++yCursor;
					}
				}

				gotoXY(xCursor, yCursor); cout << chCursor;
			}
		}
	}
	void print()
	{
		for (const Text &item : text)
		{
			if (item.ch != '|')
			{
				gotoXY(item.x, item.y);
				cout << item.ch;
			}
			else
			{
				gotoXY(x_origin_coordinate, whereY() + 1);
			}
		}
	}
	void clean()
	{
		for (const Text &item : text)
		{
			if (item.ch != '|')
			{
				gotoXY(item.x, item.y);
				cout << ' ';
			}
			else
			{
				gotoXY(x_origin_coordinate, whereY() + 1);
			}
		}
	}
	void save(const string &link_file)
	{
		ofstream file;
		file.open(link_file, ios::out);

		for (const Text &item : text)
			file << item.ch;

		file.close();
	}

	Text() {};
	~Text() {};
};