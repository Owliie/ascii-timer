/**
*  
* Solution to course project # 4
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2020/2021
*
* @author Aneta Tsvetkova
* @idnumber 62634
* @compiler GCC
*
* <file with print helper functions>
*
*/

#ifndef PRINT_DIGITS_HELPERS
#define PRINT_DIGITS_HELPERS

using namespace std;
 
// return a string containing a line of numbers -> 000000000
string get_number_line(int number)
{
	string temp = "";
	for (int i = 0; i < TIMER_DIGIT_WIDTH; i++)
	{
		temp += to_string(number);
	}

	return temp;
}

// return a string containing equally spaced numbers -> 0........0
string get_number_box(int number)
{
	string temp = to_string(number);

	for (int i = 0; i < TIMER_DIGIT_WIDTH - 2; i++)
	{
		temp += " ";
	}

	temp += to_string(number);
	return temp;
}

// return a string containing a right aligned number -> ........0
string get_number_right(int number)
{
	string temp = "";
	for (int i = 0; i < TIMER_DIGIT_WIDTH - 1; i++)
	{
		temp += " ";
	}
	temp += to_string(number);
	return temp;
}

// return a string containing a left aligned number -> 0........
string get_number_left(int number)
{
	string temp = to_string(number);
	for (int i = 0; i < TIMER_DIGIT_WIDTH - 1; i++)
	{
		temp += " ";
	}
	return temp;
}

// determine how to construct string based on the line index
string get_number_by_line(int number, int line)
{
	if (number == 1 && line >= 0 && line < TIMER_DIGIT_HEIGHT)
	{
		return to_string(1);
	}

	switch (line)
	{
	case 0:
		switch (number)
		{
		case 4:
			return get_number_box(number);

		default:
			return get_number_line(number);
		}
	case 1:
	case 2:
	case 3:
	case 4:
		switch (number)
		{
		case 0:
		case 4:
		case 8:
		case 9:
			return get_number_box(number);

		case 6:
		case 5:
			return get_number_left(number);

		default:
			return get_number_right(number);
		}
	case 5:
		switch (number)
		{
		case 0:
			return get_number_box(number);
		case 7:
			return get_number_right(number);
		default:
			return get_number_line(number);
		}
	case 6:
	case 7:
	case 8:
	case 9:
		switch (number)
		{
		case 6:
		case 8:
		case 0:
			return get_number_box(number);
		case 2:
			return get_number_left(number);

		default:
			return get_number_right(number);
		}
	case 10:
		switch (number)
		{
		case 4:
		case 7:
			return get_number_right(number);

		default:
			return get_number_line(number);
		}
	default:
		return "";
	}

	return "";
}

// calculate left padding and print centered string which contains all number structures per line
void print_centered_line(string line, int length)
{
	int padding = (WINDOW_WIDTH - length) / 2;
	cout << GRN << string(padding, ' ') << line << endl;
}

void print_digit_per_line(int *time)
{
	int count = 4;
	if (time[0] > 100)
	{
		count = count_digits(time[0]) + 2;
	}

	int *digits = new int[count];

	seed_digits(time, digits, count);

	for (int line_index = 0; line_index <= TIMER_DIGIT_HEIGHT; line_index++)
	{
		string line = "";
		for (int i = 0; i < count; i++)
		{
			line.append(get_number_by_line(*(digits + i), line_index));
			line += " ";

			// check whether to add black tile delimiters or not
			if (i == count - 3)
			{
				if (line_index == 4 || line_index == 7)
				{
					line += BLACK_BLOCK_ASCII_CODE;
				}
				else
				{
					// used to add extra space so that the number wouldn't be adjacent to the tile
					line += " ";
				}

				// used to add extra space so that the number wouldn't be adjacent to the tile
				line += " ";
			}
			else
			{
				line += " ";
			}
		}

		int line_length = line.length();
		if (line_index == 4 || line_index == 7)
		{
			// black tile character uses more than 1 char in the string so remove length to prevent line destruction
			line_length -= 2;
		}
		print_centered_line(line, line_length);
	}

	delete[](digits);
}

#endif