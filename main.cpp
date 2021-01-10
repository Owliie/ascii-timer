#include <iostream>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <iomanip>
#include <ctype.h>

#define NC "\e[0m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define CYN "\e[0;36m"

using namespace std;

const int MIN_SECONDS = 0;
const int MAX_SECONDS = 9999;
const int SECONDS_IN_MINUTE = 60;
const int TIMER_DIGIT_HEIGHT = 11;
const int TIMER_DIGIT_WIDTH = 10;
const int WINDOW_WIDTH = 80;
const string BLACK_BLOCK_ASCII_CODE = "\u2593";
const char BEEP_CHAR = '\7';

// convert seconds to an array containing minutes as [0] and seconds as [1]
int *convert_to_seconds(int seconds)
{
	int minutes = seconds / SECONDS_IN_MINUTE;
	seconds %= SECONDS_IN_MINUTE;

	int *time = new int[2]{minutes, seconds};

	return time;
}

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

// produce beep sound
void beep_sound()
{
	cout << BEEP_CHAR;
}

// get the count of the digits of which a number is constituted
int count_digits(int n)
{
	int count = 0;
	while (n != 0)
	{
		n = n / 10;
		++count;
	}

	return count;
}

// create an array containing each digit separately
void seed_digits(int *time, int *digits, int count)
{
	int minutes = time[0];
	int seconds = time[1];

	if (minutes < 10)
	{
		digits[0] = 0;
		digits[1] = minutes;
	}
	else
	{
		int *temp = new int[count - 2];
		for (int i = 0; i < count - 2; i++)
		{
			int digit = minutes % 10;
			minutes /= 10;
			temp[i] = digit;
		}

		// reverse digits
		for (int i = count - 3, j = 0; i >= 0; i--, j++)
		{
			digits[j] = temp[i];
		}

		delete[](temp);
	}

	int tens = seconds % 10;
	seconds /= 10;
	int hundreds = seconds;

	digits[count - 2] = hundreds;
	digits[count - 1] = tens;
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

void start_timer(int *time)
{
	int *minutes = &time[0];
	int *seconds = &time[1];

	while (true)
	{
		// clear console so that prints wouldn't stack
		system("clear");

		print_digit_per_line(time);

		// wait 1s before update
		sleep(1);

		if (*minutes == MIN_SECONDS && *seconds == MIN_SECONDS)
		{
			break;
		}

		(*seconds)--;

		if (*seconds < MIN_SECONDS)
		{
			(*minutes)--;
			(*seconds) = SECONDS_IN_MINUTE - 1;
		}
	}

	beep_sound();
}

int main(int argc, char const *argv[])
{
	int seconds = -1;
	string input;

	do
	{
		cout << CYN << "Enter seconds: ";
		cin >> input;

		try
		{
			seconds = stoi(input);
		}catch (const invalid_argument & e) {
            cout << RED << "Invalid seconds format!" << endl << endl;
			continue;
        }

		if (seconds < 0 || seconds > 9999)
		{
			cout << RED << "Invalid seconds format!" << endl
				 << endl;
		}
	} while (seconds < 0 || seconds > 9999);

	cout << seconds << endl;

	int *time = convert_to_seconds(seconds);

	start_timer(time);

	delete[](time);
	return 0;
}
