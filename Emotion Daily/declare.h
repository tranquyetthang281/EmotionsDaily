#pragma once
#ifndef _DECLARE_
#define _DECLARE_

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>
#include "console.h"
#include "const.h"
using namespace _const_;

/////----------Function----------/////

//Additional funcion
void printCalendar();
tm* now();
int dayOfMonth(const int &month, const int &year);
int dayOfMonth_Now();

//main
void setConsole();
void setScreen();


#endif