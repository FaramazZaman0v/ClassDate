#include <iostream>

class DayError{};
class MonthError{};
class YearError{};

class Date
{
	private:
		int year;
		int month;
		int day;
		void NormalizeDate()
		{
			if (day == 0 ) {
				throw DayError();
			}
			if (month == 0 ) {
				throw MonthError();
			}
			if (year < 1 ) {
				throw YearError();
			}
			if (month != 12)
			{
				year += month / 12;
				month %= 12;
			}

			if (month <= 0)
			{
				month = abs(12 + month);
				year --;
			}

			int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

			if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
				daysInMonth[2] = 29;
			}

			while (day > daysInMonth[month])
			{
				day -= daysInMonth[month];

				month ++;

				if (month > 12)
				{
					year += month / 12;
					if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
						daysInMonth[2] = 29;
					}else
					{
						daysInMonth[2] = 28;
					}
					month %= 12;
				}
			}

			while (day <= 0)
			{
				month --;

				if (month < 1)
				{
					year --;
					if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
						daysInMonth[2] = 29;
					}else
					{
						daysInMonth[2] = 28;
					}
					month = 12;
				}

				day += daysInMonth[month];
			}

		}
	public:
		Date(int day, int month, int year)
		{
			this->day = day;
			this->year = year; 
			this->month = month;
			
			NormalizeDate();
		}

		Date(int day)
		{
			this->day = day;
			month = 0;
			year = 1;

			NormalizeDate();
		}

		int GetYear()const
		{
			return year;
		}

		int GetMonth()const
		{
			return month;
		}

		int GetDay()const
		{
			return day;
		}

		Date operator+ (int d) const 
		{
			int newDay = day + d;
			return Date(newDay, month, year);
		}
		
		Date operator- (int d) const
		{
			int newDay = day - d;
			return Date(newDay, month, year);
		}

		Date& operator+= (int d)
		{
			day += d;

			NormalizeDate();

			return *this;
		}
	   
};

std::ostream& operator << (std::ostream& out, const Date& d) 
{
	out << d.GetDay() << " . " << d.GetMonth() << " . " << d.GetYear();

	return out;
}

std::istream& operator >> (std::istream& in, Date& date) 
{
	std::cin.exceptions(std::istream::failbit);

	int y, m, d;
	char c;

	in >> d >> c;
	in >> m >> c;
	in >> y;

	date = Date(d, m, y);

	return in;
}

int main()
{
	try {
		Date date(5,50,6);
		std::cin >> date;
		std::cout << date << "\n";
	} 
	catch (const YearError&) {
		std::cout << "Year Error !" << "\n";
	}  
	catch (const MonthError&) {
		std::cout << "Month Error !" << "\n";
	} 
	catch (const DayError&) {
		std::cout << "Day Error!" << "\n";
	}
	catch (const std::istream::failure& ex){
		std::cerr << "Data could not be read " << ex.what() << "\n";
		return 2;
	}
	catch (...){
		std::cerr << "other failure " << "\n";
		return -1;
	}
	return 0;
}
