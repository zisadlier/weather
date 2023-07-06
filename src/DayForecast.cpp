#include "DayForecast.hpp"
#include "utils/symbols.hpp"

DayForecast::DayForecast(Json::Value &data, bool use_metric, bool verbose)
{
	this->use_metric = use_metric;
	this->verbose = verbose;

	this->date = data["date"].asString();

	const Json::Value &main_data = data["day"];
	this->temperatures = 
	{
		main_data["mintemp_f"].asDouble(),
		main_data["mintemp_c"].asDouble(),
		main_data["maxtemp_f"].asDouble(),
		main_data["maxtemp_c"].asDouble(),
		main_data["avgtemp_f"].asDouble(),
		main_data["avgtemp_c"].asDouble()
	};

	this->rain_chance = main_data["daily_chance_of_rain"].asUInt();
	this->snow_chance = main_data["daily_chance_of_snow"].asUInt();
	this->precip_in = main_data["totalprecip_in"].asDouble();
	this->precip_mm = main_data["totalprecip_mm"].asDouble();
	this->average_humidity = main_data["avghumidity"].asUInt();

	const Json::Value &condition = main_data["condition"];
	this->condition_code = condition["code"].asUInt();
	this->condition_text = condition["text"].asString();

	const Json::Value &astro = data["astro"];
	this->sunrise = astro["sunrise"].asString();
	this->sunset = astro["sunset"].asString();
}

std::ostream& operator<<(std::ostream &o, DayForecast &day)
{
	o << "Forecast for " << day.date << symbols::get_symbol_from_code(day.condition_code) << std::endl;
	o << "  " << day.condition_text << std::endl;

	char unit = day.use_metric ? 'C' : 'F';
	double min_temp = day.temperatures.get_min(day.use_metric);
	double max_temp = day.temperatures.get_max(day.use_metric);
	double avg_temp = day.temperatures.get_avg(day.use_metric);

	if (day.rain_chance > day.CHANCE_CUTOFF)
	{
		o << "  Chance of rain: " << day.rain_chance << "%" << std::endl;
	}
	if (day.snow_chance > day.CHANCE_CUTOFF)
	{
		o << "  Chance of snow: " << day.snow_chance << "%" << std::endl;
	}

	o << "  Temperatures will range between " << min_temp << symbols::DEGREE_SYMBOL << unit << " and " << max_temp
		<< symbols::DEGREE_SYMBOL << unit << " with an average of " << avg_temp << symbols::DEGREE_SYMBOL << unit
		<< std::endl;

	if (day.verbose)
	{
		double precip = day.use_metric ? day.precip_mm : day.precip_in;
		if (precip > 0)
		{
			std::string precip_unit = day.use_metric ? "mm" : "in";
			o << "  Total precipitation: " << precip << precip_unit << std::endl;
		}

		o << "  Average humidity: " << day.average_humidity << "%" << std::endl;
		o << "  Sunrise: " << day.sunrise << std::endl;
		o << "  Sunset: " << day.sunset;
	}

	return o;
}