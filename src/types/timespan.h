#ifndef TIMESPAN_H
#define TIMESPAN_H

#ifdef _WIN32
	#ifdef DATETIME_EXPORTS  
		#define TIMESPAN_API __declspec(dllexport)   
	#else  
		#define TIMESPAN_API __declspec(dllimport)   
	#endif
#else
	#define TIMESPAN_API
#endif

namespace jed_utils
{
	struct dhms
	{
		int days = 0;
		int hours = 0;
		int minutes = 0;
		int seconds = 0;
	};

	dhms operator-(const dhms& mts);


	class TIMESPAN_API timespan
	{
	public:
		explicit timespan(int days, int hours = 0, int minutes = 0, int seconds = 0);
		int get_days() const;
		int get_hours() const;
		int get_minutes() const;
		int get_seconds() const;
		int get_total_hours() const;
		int get_total_minutes() const;
		int get_total_seconds() const;
		//Operators
		TIMESPAN_API friend bool operator<(const timespan &mts, const timespan &ots);
		TIMESPAN_API friend bool operator>(const timespan &mts, const timespan &ots);
		TIMESPAN_API friend bool operator<=(const timespan &mts, const timespan &ots);
		TIMESPAN_API friend bool operator>=(const timespan &mts, const timespan &ots);
		TIMESPAN_API friend bool operator==(const timespan &mts, const timespan &ots);
		TIMESPAN_API friend bool operator!=(const timespan &mts, const timespan &ots);
		TIMESPAN_API friend timespan operator-(const timespan& mts);
		TIMESPAN_API timespan& operator-=(const timespan& ots);
		TIMESPAN_API timespan& operator+=(const timespan& ots);
		TIMESPAN_API timespan& operator*=(long rhs);
		TIMESPAN_API friend timespan operator-(timespan mts, const timespan& ots);
		TIMESPAN_API friend timespan operator+(timespan mts, const timespan& ots);
		TIMESPAN_API friend timespan operator*(timespan lhs, long rhs);
	private:
		void normalise_self();
		static dhms normalise(int days, int hours, int minutes, int seconds);
		static dhms normalise_positive(unsigned seconds);
		int days;
		int hours;
		int minutes;
		int seconds;
	};
} // namespace jed_utils

#endif // TIMESPAN_H