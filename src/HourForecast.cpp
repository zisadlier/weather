#include "HourForecast.hpp"
#include "utils/symbols.hpp"
#include "utils/dates.hpp"

#include <vector>

HourForecast::HourForecast(Json::Value &data, bool use_metric, bool verbose)
{
	this->use_metric = use_metric;
	this->verbose = verbose;
	this->hour = dates::get_hour_from_date(data["time"].asString());

	this->temperatures = 
	{
		data["temp_f"].asDouble(),
		data["temp_c"].asDouble(),
		data["feelslike_f"].asDouble(),
		data["feelslike_c"].asDouble()
	};

	this->rain_chance = data["chance_of_rain"].asUInt();
	this->snow_chance = data["chance_of_snow"].asUInt();
	this->humidity = data["humidity"].asUInt();

	const Json::Value &condition = data["condition"];
	this->condition_code = condition["code"].asUInt();
}

int HourForecast::get_meridiem_hour()
{
	int hour = this->hour;
	if (hour == 0)
	{
		hour = 12;
	}

	return hour > 12 ? hour % 12 : hour;
}

int HourForecast::get_hour()
{
	return this->hour;
}

std::string HourForecast::get_hour_str()
{
	std::ostringstream os;
	std::string meridiem = this->hour < 12 ? "am" : "pm";
	
	os << this->get_meridiem_hour() << meridiem;
	return os.str();
}

std::ostream& operator<<(std::ostream &o, HourForecast &hour)
{
	char unit = hour.use_metric ? 'C' : 'F';
	std::string separator = hour.get_meridiem_hour() > 9 ? ": " : ":  ";
	o << hour.get_hour_str() << separator << hour.temperatures.get_temp_str(hour.use_metric) << symbols::get_symbol_from_code(hour.condition_code);

	if (hour.verbose)
	{
		o << std::endl << "  Humidity: " << hour.humidity << "%";
		if (hour.rain_chance > hour.CHANCE_CUTOFF)
		{
			o << std::endl << "  Chance of rain: " << hour.rain_chance << "%";
		}
		if (hour.snow_chance > hour.CHANCE_CUTOFF)
		{
			o << std::endl << "  Chance of snow: " << hour.snow_chance << "%";
		}
	}

	return o;
}