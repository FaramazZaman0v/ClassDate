#include <iostream>

class Date
{
	private:
		int year;
		int month;
		int day;
		void NormalizeDate()
		{
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
	Date date(1000);
	std::cin >> date;
	std::cout << date << std::endl;
	return 0;
}