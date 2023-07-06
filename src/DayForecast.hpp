#ifndef WEATHER_DAY_FORECAST_HPP_
#define WEATHER_DAY_FORECAST_HPP_

#include "structs.hpp"

#include <vector>
#include <string>
#include <memory>
#include <jsoncpp/json/json.h>

class DayForecast
{
public:
	const int CHANCE_CUTOFF = 25;

	/**
	 * DayForecast constructor
	 * 
	 * @param data JSON data to populate information from
	 * @param use_metric Whether or not to present information using metric units
	 * @param verbose Whether or not to present extra data
	 */
	explicit DayForecast(Json::Value &data, bool use_metric, bool verbose);

	friend std::ostream& operator<<(std::ostream &o, DayForecast &day);
private:
	// Config
	bool use_metric;
	bool verbose;

	// Weather data
	std::string date;
	ForecastTemperatures temperatures;
	uint rain_chance;
	uint snow_chance;
	double precip_in;
	double precip_mm;
	uint average_humidity;
	uint condition_code;
	std::string condition_text;

	// Astro data
	std::string sunrise;
	std::string sunset;
};

#endif // WEATHER_DAY_FORECAST_HPP_