#ifndef WEATHER_HOUR_FORECAST_HPP_
#define WEATHER_HOUR_FORECAST_HPP_

#include "structs.hpp"

#include <string>
#include <jsoncpp/json/json.h>

class HourForecast
{
public:
	const int CHANCE_CUTOFF = 20;

	/**
	 * HourForecast constructor
	 * 
	 * @param data JSON data to populate information from
	 * @param use_metric Whether or not to present information using metric units
	 * @param verbose Whether or not to present extra data
	 */
	explicit HourForecast(Json::Value &data, bool use_metric, bool verbose);

	/**
	 * Gets the hour in a 12 hour format (1-11)
	 * 
	 * @returns Hour as an integer
	 */
	int get_meridiem_hour();

	/**
	 * Gets the raw hour (0-23)
	 * 
	 * 
	 * @returns Hour as int
	 */
	int get_hour();

	/**
	 * Gets a human readable string for the hour 
	 * 
	 * @returns Hour string
	 */
	std::string get_hour_str();

	friend std::ostream& operator<<(std::ostream &o, HourForecast &hour);

private:
	bool use_metric;
	bool verbose;
	int hour;
	Temperatures temperatures;
	uint condition_code;
	uint rain_chance;
	uint snow_chance;
	uint humidity;
};

#endif // WEATHER_HOUR_FORECAST_HPP_