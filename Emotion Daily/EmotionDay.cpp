#include <numeric>
#include <conio.h>
#include "EmotionDay.h"
using namespace std;

EmotionDay::EmotionDay()
{
}

EmotionDay::~EmotionDay()
{
}

EmotionDay::EmotionDay(const Weekday &weekDay, const int &date, const int &month, const int &year, const Emotion &emotion, const string &note)
{
	this->weekday = weekDay;
	this->date = date;
	this->month = month;
	this->year = year;
	this->emotion = emotion;
	this->note = Text(note);
}

void EmotionDay::inputXY()
{
	x = X_ORIGIN_COORDINATE + 2 + weekday * (LENGHTH_BOX - 2);

	int weekday_firstDay = now()->tm_wday - (now()->tm_mday % 7 - 1);
	if (weekday_firstDay == 7)
		weekday_firstDay = sun;
	int line = (date + weekday_firstDay - 1) / 7;
	y = Y_ORIGIN_COORDINATE + 1 + line * (WIDTH_BOX - 1);
}

void EmotionDay::printCalendarBox(const int &boxColor)
{
	printColorRectangle(x, y, LENGHTH_BOX - 4, WIDTH_BOX - 2, boxColor, boxColor);
	gotoXY(x, y); cout << date;
	gotoXY(x + 2, y + 1); cout << this_emotionIcon();

	printColorText(X_ORIGIN_COORDINATE, Y_ORIGIN_COORDINATE + WIDTH_CALENDAR + WIDTH_BOX - 2, 112, DEFAULT_COLOR, "Emotion:");
	cout << ' ' << this_emotionIcon();

	printColorText(X_ORIGIN_COORDINATE, Y_ORIGIN_COORDINATE + WIDTH_CALENDAR + WIDTH_BOX, 112, DEFAULT_COLOR, "Note:");
	note.print();
}

string EmotionDay::this_emotionIcon()
{
	return emotionIcon(emotion);
}

void EmotionDay::editEmotion(const Emotion &emotion)
{
	printColorText(X_ORIGIN_COORDINATE, Y_ORIGIN_COORDINATE + WIDTH_CALENDAR + WIDTH_BOX - 2, 112, DEFAULT_COLOR, "Emotion:");
	cout << setw(6) << emotionIcon(unlucky) << setw(6) << emotionIcon(sad) << setw(6) << emotionIcon(normal) << setw(6) << emotionIcon(happy) << setw(6) << emotionIcon(lucky) << setw(6) << emotionIcon(wonderful);
	printColorText(X_ORIGIN_COORDINATE + 9 + 6 * emotion, Y_ORIGIN_COORDINATE + WIDTH_CALENDAR + WIDTH_BOX - 2, SELECTION_COLOR, DEFAULT_COLOR, emotionIcon(emotion));

	printColorText(X_ORIGIN_COORDINATE + LENGHTH_CALENDAR + 10, Y_ORIGIN_COORDINATE + WIDTH_CALENDAR - 1, 248, DEFAULT_COLOR, "Press \"Enter\" to choose emotion and edit note");

	int flag = -1;
	while (true)
	{
		if (_kbhit())
		{
			char key = _getch();

			if (key == 13) //Enter
			{
				flag = 0;
				break;
			}
			else if (key == 77) //RIGHT
			{
				flag = 1;
				break;
			}
			else if (key == 75) //LEFT
			{
				flag = 2;
				break;
			}
		}
	}

	printColorText(X_ORIGIN_COORDINATE + 9 + 6 * emotion, Y_ORIGIN_COORDINATE + WIDTH_CALENDAR + WIDTH_BOX - 2, DEFAULT_COLOR, DEFAULT_COLOR, emotionIcon(emotion));

	switch (flag)
	{
	case 0: //Enter
		printColorRectangle(X_ORIGIN_COORDINATE + 9, Y_ORIGIN_COORDINATE + WIDTH_CALENDAR + WIDTH_BOX - 2, 6 * 6, 1, BACKGROUND_COLOR, DEFAULT_COLOR);
		printColorText(X_ORIGIN_COORDINATE + LENGHTH_CALENDAR + 10, Y_ORIGIN_COORDINATE + WIDTH_CALENDAR - 1, BACKGROUND_COLOR, DEFAULT_COLOR, "Press \"Enter\" to choose emotion and edit note");
		printColorText(X_ORIGIN_COORDINATE + LENGHTH_CALENDAR + 10, Y_ORIGIN_COORDINATE + WIDTH_CALENDAR - 1, 248, DEFAULT_COLOR, "Press \"Esc\" to end note");
		this->emotion = emotion;
		printCalendarBox(SELECTION_COLOR);
		note.edit();
		printColorText(X_ORIGIN_COORDINATE + LENGHTH_CALENDAR + 10, Y_ORIGIN_COORDINATE + WIDTH_CALENDAR - 1, BACKGROUND_COLOR, DEFAULT_COLOR, "Press \"Esc\" to end note");
		break;

	case 1: //RIGHT
		if (emotion != wonderful)
			editEmotion(Emotion(int(emotion) + 1));
		else
			editEmotion(unlucky);
		break;

	case 2: //LEFT
		if (emotion != unlucky)
			editEmotion(Emotion(int(emotion) - 1));
		else
			editEmotion(wonderful);
		break;
	}
}

void EmotionDay::handlingCelendarBox(vector<EmotionDay> &vecEmotionDay)
{
	printCalendarBox((now()->tm_mday == date) ? TODAY_SELECTION_COLOR : SELECTION_COLOR);
	printColorText(X_ORIGIN_COORDINATE + LENGHTH_CALENDAR + 10, Y_ORIGIN_COORDINATE + WIDTH_CALENDAR - 1, 248, DEFAULT_COLOR, "Press \"Enter\" to edit emotion");
	printColorText(X_ORIGIN_COORDINATE + LENGHTH_CALENDAR + 10, Y_ORIGIN_COORDINATE + WIDTH_CALENDAR + 1, 248, DEFAULT_COLOR, "or \"Esc\" to save and exit");

	int flag = -1;
	while (true)
	{
		if (_kbhit())
		{
			char key = _getch();

			if (key == 13) //Enter
			{
				flag = 0;
				break;
			}
			else if (key == 72) //UP
			{
				flag = 1;
				break;
			}
			else if (key == 80) //DOWN
			{
				flag = 2;
				break;
			}
			else if (key == 77) //RIGHT
			{
				flag = 3;
				break;
			}
			else if (key == 75) //LEFT
			{
				flag = 4;
				break;
			}
			else if (key == 27) //Esc
			{
				flag = 5;
				break;
			}
		}
	}

	switch (flag)
	{
	case 0: //Enter
		printColorText(X_ORIGIN_COORDINATE + LENGHTH_CALENDAR + 10, Y_ORIGIN_COORDINATE + WIDTH_CALENDAR - 1, BACKGROUND_COLOR, DEFAULT_COLOR, "Press \"Enter\" to edit emotion");
		printColorText(X_ORIGIN_COORDINATE + LENGHTH_CALENDAR + 10, Y_ORIGIN_COORDINATE + WIDTH_CALENDAR + 1, BACKGROUND_COLOR, DEFAULT_COLOR, "or \"Esc\" to save and exit");
		editEmotion(emotion == -1 ? unlucky : emotion);
		printEmotionOfMonth(vecEmotionDay);
		handlingCelendarBox(vecEmotionDay);
		break;

	case 1: //UP
		printCalendarBox((now()->tm_mday == date) ? TODAY_COLOR : DEFAULT_COLOR);
		cleanData();
		if (date > 7)
			vecEmotionDay[date - 8].handlingCelendarBox(vecEmotionDay);
		else
			if (date + 7 * 4 > dayOfMonth_Now())
				vecEmotionDay[date + 7 * 3 - 1].handlingCelendarBox(vecEmotionDay);
			else
				vecEmotionDay[date + 7 * 4 - 1].handlingCelendarBox(vecEmotionDay);
		break;

	case 2:	//DOWN
		printCalendarBox((now()->tm_mday == date) ? TODAY_COLOR : DEFAULT_COLOR);
		cleanData();
		if (date <= dayOfMonth_Now() - 7)
			vecEmotionDay[date + 6].handlingCelendarBox(vecEmotionDay);
		else
			if (date - 7 * 4 <= 0)
				vecEmotionDay[date - 7 * 3 - 1].handlingCelendarBox(vecEmotionDay);
			else
				vecEmotionDay[date - 7 * 4 - 1].handlingCelendarBox(vecEmotionDay);
		break;

	case 3: //RIGHT
		printCalendarBox((now()->tm_mday == date) ? TODAY_COLOR : DEFAULT_COLOR);
		cleanData();
		if (date != dayOfMonth_Now())
			vecEmotionDay[date].handlingCelendarBox(vecEmotionDay);
		else
			vecEmotionDay[0].handlingCelendarBox(vecEmotionDay);
		break;

	case 4: //LEFT
		printCalendarBox((now()->tm_mday == date) ? TODAY_COLOR : DEFAULT_COLOR);
		cleanData();
		if (date != 1)
			vecEmotionDay[date - 2].handlingCelendarBox(vecEmotionDay);
		else
			vecEmotionDay[dayOfMonth_Now() - 1].handlingCelendarBox(vecEmotionDay);
		break;
	case 5: //Esc
		printCalendarBox((now()->tm_mday == date) ? TODAY_COLOR : DEFAULT_COLOR);
		printEmotionOfMonth(vecEmotionDay);
		cleanData();
		break;
	}
}

void EmotionDay::cleanData()
{
	printColorRectangle(X_ORIGIN_COORDINATE + 9, Y_ORIGIN_COORDINATE + WIDTH_CALENDAR + WIDTH_BOX - 2, 5, 1, BACKGROUND_COLOR, DEFAULT_COLOR);
	note.clean();
}

string EmotionDay::outData()
{
	if (emotion != -1)
		return "0" + to_string(emotion) + note.str();
	return "-1";
}

Emotion EmotionOFMonth(const vector<EmotionDay> &vecEmotionDay)
{
	int days = vecEmotionDay.size();
	int sum = 0;
	for (const EmotionDay &item : vecEmotionDay)
	{
		if (item.emotion != -1)
			sum += item.emotion;
		else
			--days;
	}
	if (days == 0)
		return null;

	int emotionOfMonth = 0;
	for (int i = 1; i <= 5; ++i)
		if ((2 * sum >= (2 * i - 1)*days) && (2 * sum < (2 * i + 1)*days))
		{
			emotionOfMonth += i;
			break;
		}
	return Emotion(emotionOfMonth);
}

//
string emotionIcon(const Emotion &emotion)
{
	string icon;
	switch (emotion)
	{
	case unlucky:
		icon = { '(' ,char(247), '_' ,char(247), ')' };
		return icon;
	case sad:
		icon = { '(' ,char(240), '_' ,char(240), ')' };
		return icon;
	case normal:
		icon = { '(' ,char(248), '_' ,char(248), ')' };
		return icon;
	case happy:
		icon = { '(' ,char(167), '.' ,char(167), ')' };
		return icon;
	case lucky:
		icon = { '(' ,char(62), '.' ,char(60), ')' };
		return icon;
	case wonderful:
		icon = { '(' ,char(94), 'o' ,char(94), ')' };
		return icon;
	default:
		return "";
	}
}

void printEmotionOfMonth(const vector<EmotionDay> &vecEmotionDay)
{
	printColorText(X_ORIGIN_COORDINATE + LENGHTH_CALENDAR + 53, Y_ORIGIN_COORDINATE + 2, 112, DEFAULT_COLOR, emotionIcon(EmotionOFMonth(vecEmotionDay)));
}