#ifndef WEATHER_WEATHER_HPP_
#define WEATHER_WEATHER_HPP_

#include "structs.hpp"
#include "Options.hpp"

#include <memory>
#include <map>
#include <jsoncpp/json/json.h>

class WeatherOptions : public Options
{
public:
	WeatherOptions(std::string api_key, std::string location, bool metric, bool verbose)
		: Options(api_key, location, metric, verbose)
	{}
};

class Weather
{
public:
	/**
	 * Weather object constructor 
	 * 
	 * @param data JSON data that the object will use to build itself
	 * @param options Option specifications
	 */
	Weather(Json::Value &data, std::shared_ptr<WeatherOptions> options);

	Weather(const Weather&) = delete;
    Weather& operator=(const Weather&) = delete;
    ~Weather() = default;

	/**
	 * Gets a simple string representation of this weather object that contains temperature and a condition symbol
	 */
	std::string get_simple_str();

	friend std::ostream& operator<<(std::ostream &o, Weather &weather);

private:
	std::unique_ptr<Location> location;
	std::shared_ptr<WeatherOptions> options;
	Temperatures temperatures;
	uint humidity;
	double wind_mph;
	double wind_kph;
	std::string wind_direction;
	uint condition_code;
	std::string condition_text;
};

#endif // WEATHER_WEATHER_HPP_