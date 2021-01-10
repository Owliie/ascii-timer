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

void print_number_line(int number)
{
	for (int i = 0; i < TIMER_DIGIT_WIDTH; i++)
	{
		cout << number;
	}
}

void print_number_box(int number)
{
	// cout << number << setfill(' ') << setw(TIMER_DIGIT_WIDTH-1) << number;
	cout << number;

	for (int i = 0; i < TIMER_DIGIT_WIDTH-2; i++)
	{
		cout << " ";
	}
	

	cout << number;
}

void print_number_right(int number)
{
	// cout << setfill(' ') << setw(TIMER_DIGIT_WIDTH) << number;
	for (int i = 0; i < TIMER_DIGIT_WIDTH-1; i++)
	{
		cout << " ";
	}
	cout << number;
}

void print_number_left(int number)
{
	// cout << number << setfill(' ') << setw(TIMER_DIGIT_WIDTH);
	cout << number;
	for (int i = 0; i < TIMER_DIGIT_WIDTH-1; i++)
	{
		cout << " ";
	}
}

void print_number_by_line(int number, int line)
{
	if (number == 1)
	{
		cout << 1;
		return;
	}

	switch (line)
	{
	case 0:
		switch (number)
		{
		case 4:
			print_number_box(number);
			break;

		default:
			print_number_line(number);
			break;
		}
		break;
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
			print_number_box(number);
			break;

		case 6:
		case 5:
			print_number_left(number);
			break;

		default:
			print_number_right(number);
			break;
		}
		break;
	case 5:
		switch (number)
		{
		case 0:
			print_number_box(number);
			break;
		case 7:
			print_number_right(number);
			break;
		default:
			print_number_line(number);
			break;
		}
		break;
	case 6:
	case 7:
	case 8:
	case 9:
		switch (number)
		{
		case 6:
		case 8:
		case 0:
			print_number_box(number);
			break;
		case 2:
			print_number_left(number);
			break;

		default:
			print_number_right(number);
			break;
		}
		break;
	case 10:
		switch (number)
		{
		case 4:
		case 7:
			print_number_right(number);
			break;

		default:
			print_number_line(number);
			break;
		}
		break;

	default:
		break;
	}

	cout << " ";
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

void seed_digits(int* time, int* digits, int count){
	int minutes = time[0];
	int seconds = time[1];

	if(minutes < 10){
		digits[0] = 0;
		digits[1] = minutes;
	} else{
		int* temp = new int[count-2];
		for (int i = 0; i < count-2; i++)
		{
			int digit = minutes % 10;
			minutes/=10;
			temp[i] = digit;
		}

		// reverse digits
		for (int i = count - 3, j = 0; i >= 0; i--, j++)
		{
			digits[j] = temp[i];
		}
	}

	int tens = seconds%10;
	seconds/=10;
	int hundreds = seconds;

	digits[count-2] = hundreds;
	digits[count-1] = tens;	
}

void print_digit_by_digit(int *time)
{
	int count = 4;
	if(time[0] > 100){
		count = count_digits(time[0]) + 2;
	}

	int *digits = new int[count];

	seed_digits(time, digits, count);

	// for (int i = 0; i < count; i++)
	// {
	// 	cout << *(digits+i) << " ";
	// }
	// cout << endl;

	for (int line = 0; line <= TIMER_DIGIT_HEIGHT; line++)
	{
		for (int i = 0; i < count; i++)
		{
			print_number_by_line(*(digits + i), line);
		}
		cout << endl;
	}
	
	delete[](digits);
}

void start_timer(int *time)
{
	int minutes = time[0];
	int seconds = time[1];

	while (true)
	{
		system("clear");

		print_digit_by_digit(time);

		sleep(1);

		if (minutes == MIN_SECONDS && seconds == MIN_SECONDS)
		{
			break;
		}

		seconds--;

		if (seconds < MIN_SECONDS)
		{
			minutes--;
			seconds = SECONDS_IN_MINUTE - 1;
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

	cout << setfill(' ') << setw(WINDOW_WIDTH) << std::center;
	cout << endl;
	print_digit_by_digit(time);

	delete[](time);
	return 0;
}
