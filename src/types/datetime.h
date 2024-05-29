#ifndef DATETIME_H
#define DATETIME_H

#include "timespan.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <stdexcept>
#include <string>
#include <chrono>

#ifdef _WIN32
	#ifdef DATETIME_EXPORTS  
		#define DATETIME_API __declspec(dllexport)   
	#else  
		#define DATETIME_API __declspec(dllimport)   
	#endif
#else
	#define DATETIME_API
#endif


namespace jed_utils
{
	enum weekday { sunday, monday, tuesday, wednesday, thursday, friday, saturday };
	enum period { undefined, AM, PM };

	class DATETIME_API datetime
	{
	public:
		datetime();
		datetime(int year, int month, int day, int hour = 0, int minute = 0, int second = 0, period day_period = period::undefined);
		datetime(std::chrono::year_month_day);
		datetime(const datetime& other); //Copy constructor
		datetime& operator=(const datetime& other); //Copy assignment
		datetime(datetime&& other) noexcept; //Move constructor
		datetime& operator=(datetime&& other) noexcept; //Move assignement
		virtual ~datetime();
		DATETIME_API friend std::ostream& operator<<(std::ostream &os, const datetime &dt);
		DATETIME_API friend bool operator<(const datetime &mdt, const datetime &odt);
		DATETIME_API friend bool operator>(const datetime &mdt, const datetime &odt);
		DATETIME_API friend bool operator<=(const datetime &mdt, const datetime &odt);
		DATETIME_API friend bool operator>=(const datetime &mdt, const datetime &odt);
		DATETIME_API friend bool operator==(const datetime& mdt, const datetime &odt);
		DATETIME_API friend bool operator!=(const datetime& mdt, const datetime &odt);
		DATETIME_API friend timespan operator-(const datetime& mdt, const datetime &odt);
		DATETIME_API datetime& operator+=(const timespan& odt);
		DATETIME_API datetime& operator-=(const timespan& odt);
		DATETIME_API friend datetime operator+(datetime mdt, const timespan& odt);
		DATETIME_API friend datetime operator-(datetime mdt, const timespan& odt);
		std::string to_string() const;
		std::string to_string(const std::string& format) const;
		std::string to_shortdate_string() const;
		int get_year() const;
		std::chrono::year get_std_year() const;
		int get_month() const;
		std::chrono::month get_std_month() const;
		std::chrono::year_month get_year_month() const;
		int get_day() const;
		int get_hour() const;
		int get_minute() const;
		int get_second() const;
		weekday get_weekday() const;
		void add_years(int nb_years);
		void add_months(int nb_months);
		void add_days(int nb_days);
		void add_hours(int nb_hours);
		void add_minutes(int nb_minutes);
		void add_seconds(int nb_seconds);
		datetime& trunkate();
		bool is_leapyear();
		static datetime parse(const std::string& format, const std::string& value);
		static bool is_leapyear(int year);
	protected:
		const int ONE_DAY = 86400; //24 hours * 60 mins * 60 secs
		const int ONE_HOUR = 3600; //60 mins * 60 secs
		const int ONE_MINUTE = 60; // 60 secs
		struct tm *timeInfo = nullptr;
		bool auto_created = true;
		bool _is_leapyear(int year) const;
		static int _parse_intvalue(const std::string &pattern, int index, size_t mask_length, const std::string &parse_str);
		void _copy_from(const tm* otm);
	};
	
	std::istream& operator>>(std::istream& is, jed_utils::datetime& datetime);
} // namespace jed_utils

#endif // DATETIME_H
