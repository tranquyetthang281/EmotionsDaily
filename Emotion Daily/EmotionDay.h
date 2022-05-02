#pragma once

#include "declare.h"
#include "Text.h"

//extern
enum Emotion { null = -1, unlucky, sad, normal, happy, lucky, wonderful };
enum Weekday { sun, mon, tue, wed, thu, fri, sat };

class EmotionDay
{
private:
	Weekday weekday;
	int date;
	int month;
	int year;
	Emotion emotion;
	Text note;
	int x;
	int y;
public:
	EmotionDay(const Weekday &weekDay, const int &date, const int &month, const int &year, const Emotion &emotion, const std::string &note);

	void inputXY();
	void printCalendarBox(const int &boxColor);
	std::string this_emotionIcon();
	void editEmotion(const Emotion &emotion);
	void handlingCelendarBox(std::vector<EmotionDay> &vecEmotionDay);
	void cleanData();
	std::string outData();

	friend Emotion EmotionOFMonth(const std::vector<EmotionDay> &vecEmotionDay);

	EmotionDay();
	~EmotionDay();
};

//
std::string emotionIcon(const Emotion &emotion);
void printEmotionOfMonth(const std::vector<EmotionDay> &vecEmotionDay);