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
* <file with array helper functions>
*
*/

#ifndef ARRAY_HELPER
#define ARRAY_HELPER

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


// convert seconds to an array containing minutes as [0] and seconds as [1]
int *convert_to_seconds(int seconds)
{
	int minutes = seconds / SECONDS_IN_MINUTE;
	seconds %= SECONDS_IN_MINUTE;

	int *time = new int[2]{minutes, seconds};

	return time;
}

#endif