#ifndef _CONST_
#define _CONST_

namespace _const_
{
	const int MAX_X{ 129 };
	const int MAX_Y{ 34 };

	const int X_ORIGIN_COORDINATE{ 2 };
	const int Y_ORIGIN_COORDINATE{ 3 };

	const int LENGHTH_BOX{ 11 };
	const int WIDTH_BOX{ 4 };

	const int LENGHTH_CALENDAR{ 7 * (LENGHTH_BOX - 2) + 2 };
	const int WIDTH_CALENDAR{ 6 * (WIDTH_BOX - 1) + 1 };

	const int DEFAULT_COLOR{ 240 };
	const int BACKGROUND_COLOR{ 255 };
	const int SELECTION_COLOR{ 224 };
	const int TODAY_COLOR{ 160 };
	const int TODAY_SELECTION_COLOR{ 192 };

}

#endif
