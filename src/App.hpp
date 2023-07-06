#ifndef WEATHER_APP_HPP_
#define WEATHER_APP_HPP_

#define NOOP

#include "Weather.hpp"
#include "Forecast.hpp"
#include "Options.hpp"

#include <map>
#include <memory>
#include <string>

class App
{
public:
	const std::string version = "v1.0.0";
	const std::string BASE_URL = "https://api.weatherapi.com/v1/";
	const int HOURLY_FORECAST_DAYS = 2;

	/**
	 * Constructs a request manager
	 * 
	 * @param arc Command line argument count
	 * @param argv Command line arguments
	 */
	explicit App(int argc, char *argv[]);

	/**
	 * Runs the application based on the provided options
	 */
	void run();

	/**
	 * Displays usage information for the application
	 */
	void usage();

	/**
	 * Creates an options object given command line args and an API key
	 * 
	 * @param argc Command line argument count
	 * @param argv Command line arguments
	 * @param api_key weatherapi.com API key
	 * 
	 * @returns A pointer to the created options object
	 */
	std::shared_ptr<Options> get_options_from_args(int argc, char *argv[], std::string api_key);

	/**
	 * Gets the current weather
	 * 
	 * @returns A pointer to a weather object
	 */
	std::unique_ptr<Weather> get_current_weather();

	/**
	 * Gets an hour by hour forecast
	 * 
	 * @returns A pointer to a forecast object
	 */
	std::unique_ptr<Forecast> get_hourly_forecast();

	/**
	 * Gets a day by day forecast
	 * 
	 * @returns A pointer to a forecast object
	 */
	std::unique_ptr<Forecast> get_daily_forecast();

private:
	std::shared_ptr<Options> options;
	std::string operation;
};

#endif // WEATHER_APP_HPP_