#include "declare.h"
#include "EmotionDay.h"
using namespace std;

void setConsole()
{
	string mode;
	mode = "mode con:cols=" + to_string(MAX_X + 1) + " lines=" + to_string(MAX_Y + 1);
	system(mode.c_str());
	SetConsoleTitle(TEXT("Emotion Daily 1.0"));
	system("color F0");
}

void setScreen()
{
	printColorText(X_ORIGIN_COORDINATE + LENGHTH_CALENDAR + 10, Y_ORIGIN_COORDINATE - 2, 112, 240, "Emotion Icon:");
	gotoXY(X_ORIGIN_COORDINATE + LENGHTH_CALENDAR + 10, Y_ORIGIN_COORDINATE); cout << emotionIcon(wonderful) << ": wonderful";
	gotoXY(X_ORIGIN_COORDINATE + LENGHTH_CALENDAR + 10, Y_ORIGIN_COORDINATE + 2); cout << emotionIcon(lucky) << ": lucky";
	gotoXY(X_ORIGIN_COORDINATE + LENGHTH_CALENDAR + 10, Y_ORIGIN_COORDINATE + 4); cout << emotionIcon(happy) << ": happy";
	gotoXY(X_ORIGIN_COORDINATE + LENGHTH_CALENDAR + 10, Y_ORIGIN_COORDINATE + 6); cout << emotionIcon(normal) << ": normal";
	gotoXY(X_ORIGIN_COORDINATE + LENGHTH_CALENDAR + 10, Y_ORIGIN_COORDINATE + 8); cout << emotionIcon(sad) << ": sad";
	gotoXY(X_ORIGIN_COORDINATE + LENGHTH_CALENDAR + 10, Y_ORIGIN_COORDINATE + 10); cout << emotionIcon(unlucky) << ": unlucky";
	printColorText(X_ORIGIN_COORDINATE + LENGHTH_CALENDAR + 40, Y_ORIGIN_COORDINATE - 2, 160, 160, "Today: ");
	switch (now()->tm_mon + 1)
	{
	case 1: cout << "Jan"; break;
	case 2: cout << "Feb"; break;
	case 3: cout << "Mar"; break;
	case 4: cout << "Apr"; break;
	case 5: cout << "May"; break;
	case 6: cout << "Jun"; break;
	case 7: cout << "Jul"; break;
	case 8: cout << "Aug"; break;
	case 9: cout << "Sep"; break;
	case 10: cout << "Oct"; break;
	case 11: cout << "Nov"; break;
	case 12: cout << "Dec"; break;
	}
	cout << ' ' << now()->tm_mday << ", " << now()->tm_year + 1900;
	printColorRectangle(X_ORIGIN_COORDINATE + LENGHTH_CALENDAR + 40, Y_ORIGIN_COORDINATE, 19, 6, 112, DEFAULT_COLOR);
	printColorText(X_ORIGIN_COORDINATE + LENGHTH_CALENDAR + 41, Y_ORIGIN_COORDINATE, 124, 112, "Average:");
	gotoXY(X_ORIGIN_COORDINATE + LENGHTH_CALENDAR + 41, Y_ORIGIN_COORDINATE + 2); cout << "This month:";
	gotoXY(X_ORIGIN_COORDINATE + LENGHTH_CALENDAR + 41, Y_ORIGIN_COORDINATE + 4); cout << "Last month:";
	TextColor(DEFAULT_COLOR);
}

int main()
{
	//clean Text cursor
	ShowCur(0);

	//set Console
	setConsole();
	setScreen();

	//print Calendar
	printCalendar();

	/////-------------------/////
	vector<EmotionDay> vecEmotionDay(dayOfMonth_Now());

	//open file "EmotionData.txt"
	fstream file;
	file.open("EmotionData.txt", ios::in | ios::out);

	//-----input data-----
	string timeNow = to_string(now()->tm_mon) + to_string(now()->tm_year);
	string data;
	getline(file, data);

	//check month
	if (data != timeNow)
	{
		file.seekg(0, SEEK_SET);
		file << timeNow << endl;
		for (int i = 1; i <= dayOfMonth_Now(); ++i)
			file << "-1" << endl;
	}

	//input vector
	int weekday;
	weekday = now()->tm_wday - (now()->tm_mday % 7 - 1);
	file.seekg(0, SEEK_SET);
	getline(file, data);
	for (int id = 0; id < dayOfMonth_Now(); ++id)
	{
		getline(file, data);
		string emotion;
		emotion.insert(emotion.begin(), data.begin(), data.begin() + 2);
		data.erase(0, 2);
		if (weekday == 7) weekday = 0;
		vecEmotionDay[id] = EmotionDay(Weekday(weekday++), id + 1, now()->tm_mon, now()->tm_year + 1900, Emotion(stoi(emotion)), data);
	}
	printEmotionOfMonth(vecEmotionDay);
	for (EmotionDay &item : vecEmotionDay)
	{
		item.inputXY();
		item.printCalendarBox(DEFAULT_COLOR); //print data
		item.cleanData();
	}
	//------------------

	//
	vecEmotionDay[now()->tm_mday - 1].handlingCelendarBox(vecEmotionDay);

	//-----output data-----
	file.seekg(0, SEEK_SET);
	file << timeNow << endl;
	for (EmotionDay &item : vecEmotionDay)
		file << item.outData() << endl;
	//---------------------

	//close file "EmotionData.txt"
	file.close();

	/////---------END----------/////

	return 0;
}