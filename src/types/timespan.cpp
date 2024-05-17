#include "timespan.h"
#include <stdexcept>

using namespace std;

namespace jed_utils 
{
	dhms operator-(const dhms& mts)
	{
		dhms x;
		x.days = -mts.days;
		x.hours = -mts.hours;
		x.minutes = -mts.minutes;
		x.seconds = -mts.seconds;
		return x;
	}

	timespan::timespan(int days, int hours, int minutes, int seconds)
		//days(days), hours(hours), minutes(minutes), seconds(seconds)
	{
		//Check if the values submitted is valid
		if (hours < -23 || hours > 23) {
			throw std::invalid_argument("hours must be between 0 and 23");
		}
		if (minutes < -59 || minutes > 59) {
			throw std::invalid_argument("minutes must be between 0 and 59");
		}
		if (seconds < -59 || seconds > 59) {
			throw std::invalid_argument("seconds must be between 0 and 59");
		}
		this->days = days;
		this->hours = hours;
		this->minutes = minutes;
		this->seconds = seconds;
	}

	int timespan::get_days() const
	{
		return days;
	}

	int timespan::get_hours() const
	{
		return hours;
	}

	int timespan::get_minutes() const
	{
		return minutes;
	}

	int timespan::get_seconds() const
	{
		return seconds;
	}

	int timespan::get_total_hours() const
	{
		return  (days * 24) + hours;
	}

	int timespan::get_total_minutes() const
	{
		return  (days * 60 * 24) + (hours * 60) + minutes;
	}

	int timespan::get_total_seconds() const
	{
		return  (days * 60 * 60 * 24) + (hours * 60 * 60) + (minutes * 60) + seconds;
	}

	bool operator<(const timespan &mts, const timespan &ots)
	{
		if (mts.days < ots.days) {
			return true;
		}
		if (mts.days > ots.days) {
			return false;
		}
		if (mts.hours < ots.hours) {
			return true;
		}
		if (mts.hours > ots.hours) {
			return false;
		}
		if (mts.minutes < ots.minutes) {
			return true;
		}
		if (mts.minutes > ots.minutes) {
			return false;
		}
		if (mts.seconds < ots.seconds) {
			return true;
		}
		
        return false;
	}

	bool operator>(const timespan &mts, const timespan &ots)
	{
		return ots < mts;
	}

	bool operator<=(const timespan &mts, const timespan &ots)
	{
		return !(mts > ots);
	}

	bool operator>=(const timespan &mts, const timespan &ots)
	{
		return !(mts < ots);
	}

	bool operator==(const timespan &mts, const timespan &ots)
	{
		return mts.days == ots.days &&
			mts.hours == ots.hours &&
			mts.minutes == ots.minutes &&
			mts.seconds == ots.seconds;
	}

	bool operator!=(const timespan &mts, const timespan &ots)
	{
		return !(mts == ots);
	}

	timespan operator-(const timespan& mts)
	{
		return timespan{-mts.days, -mts.hours, -mts.minutes, -mts.seconds};
	}

	timespan& timespan::operator-=(const timespan& ots)
	{
		days -= ots.days;
		hours -= ots.hours;
		minutes -= ots.minutes;
		seconds -= ots.seconds;
		normalise_self();
		return *this;
	}

	timespan& timespan::operator+=(const timespan& ots)
	{
		days += ots.days;
		hours += ots.hours;
		minutes += ots.minutes;
		seconds += ots.seconds;
		normalise_self();
		return *this;
	}

	timespan& timespan::operator*=(long rhs)
	{
		days *= rhs;
		hours *= rhs;
		minutes *= rhs;
		seconds *= rhs;
		normalise_self();
		return *this;
	}

	timespan operator-(timespan mts, const timespan& ots)
	{
		mts -= ots;
		return mts;
	}
	
	timespan operator+(timespan mts, const timespan& ots)
	{
		mts += ots;
		return mts;
	}

	timespan operator*(timespan lhs, long rhs)
	{
		lhs *= rhs;
		return lhs;
	}

	void timespan::normalise_self()
	{
		dhms x = normalise(days, hours, minutes, seconds);
		days = x.days;
		hours = x.hours;
		minutes = x.minutes;
		seconds = x.seconds;
	}

	dhms timespan::normalise(int days, int hours, int minutes, int seconds)
	{
		seconds += 86400 * days + 3600 * hours + 60 * minutes;
		if (seconds >= 0)
			return normalise_positive(seconds);
		else
			return -normalise_positive(-seconds);
	}

	dhms timespan::normalise_positive(unsigned seconds)
	{
		dhms x;
		x.days = seconds / 86400;
		seconds -= x.days * 86400;
		x.hours = seconds / 3600;
		seconds -= x.hours * 3600;
		x.minutes = seconds / 60;
		seconds -= x.minutes * 60;
		x.seconds = seconds;
		return x;
	}
} // namespace jed_utils
