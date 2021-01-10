#include <iostream>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <iomanip>

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
const int WINDOW_HEIGHT = 25;

int *convertToMinutes(int seconds)
{
	int minutes = seconds / SECONDS_IN_MINUTE;
	seconds %= SECONDS_IN_MINUTE;

	int *time = new int[2]{minutes, seconds};

	return time;
}

string get_number_line(int number)
{
	string temp = "";
	for (int i = 0; i < TIMER_DIGIT_WIDTH; i++)
	{
		temp += to_string(number);
	}

	return temp;
}

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

string get_number_left(int number)
{
	string temp = to_string(number);
	for (int i = 0; i < TIMER_DIGIT_WIDTH - 1; i++)
	{
		temp += " ";
	}
	return temp;
}

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

void beep_sound()
{
	cout << '\7';
}

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

		delete [](temp);
	}

	int tens = seconds % 10;
	seconds /= 10;
	int hundreds = seconds;

	digits[count - 2] = hundreds;
	digits[count - 1] = tens;
}

void print_centered_line(string line, int length)
{
	int padding = (WINDOW_WIDTH - length) / 2;
	cout << GRN << string(padding, ' ') << line << endl;
}

void print_digit_by_digit(int *time)
{
	int count = 4;
	if (time[0] > 100)
	{
		count = count_digits(time[0]) + 2;
	}

	int *digits = new int[count];

	seed_digits(time, digits, count);
	int line_length = 0;

	cout << time[1] << endl;

	for (int line_index = 0; line_index <= TIMER_DIGIT_HEIGHT; line_index++)
	{
		string line = "";
		for (int i = 0; i < count; i++)
		{
			line.append(get_number_by_line(*(digits + i), line_index));
			line += " ";
		}
		if (line_length < line.length())
		{
			line_length = line.length();
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
		system("clear");

		print_digit_by_digit(time);

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
	int seconds = 0;

	do
	{
		cout << CYN << "Enter seconds: ";
		cin >> seconds;

		if (seconds < 0 || seconds > 9999)
		{
			cout << RED << "Invalid seconds format!" << endl
				 << endl;
		}
	} while (seconds < 0 || seconds > 9999);

	int *time = convertToMinutes(seconds);

	start_timer(time);

	delete[](time);
	return 0;
}
