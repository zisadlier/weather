#include <string>
#include <vector>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

namespace dates
{
	/**
	 * Gets an integer hour from a date string
	 * 
	 * @param date Date string to get the hour from
	 * @returns hour as an int
	 */
	inline int get_hour_from_date(std::string date)
	{
		std::vector<std::string> toks1;
		boost::split(toks1, date, boost::is_from_range(' ', ' '));

		std::vector<std::string> toks2;
		boost::split(toks2, toks1[1], boost::is_from_range(':', ':'));

		return std::stoi(toks2[0]);
	}
}