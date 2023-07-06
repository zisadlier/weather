#ifndef WEATHER_FORECAST_HPP_
#define WEATHER_FORECAST_HPP_

#include "DayForecast.hpp"
#include "HourForecast.hpp"
#include "Options.hpp"
#include "structs.hpp"

#include <string>
#include <jsoncpp/json/json.h>

class ForecastOptions : public Options
{
public:
	/**
	 * ForecastOptions constructor
	 * 
	 * @param api_key weatherapi.com API key to use to retrieve data
	 * @param location Location for the forecast as a string
	 * @param metric Option to present information using metric data
	 * @param verbose Option to display extra information
	 * @param days Number of days to retrive information for
	 * @param hours Number of hours to retrieve information for
	 */
	ForecastOptions(std::string api_key, std::string location, bool metric, bool verbose, int days, int hours);

	std::map<std::string, std::string> get_request_args() override;

	/**
	 * Gets hours member
	 * 
	 * @returns hours
	 */
	int get_hours() const;

	/**
	 * Gets days member
	 * 
	 * @returns days
	 */
	int get_days() const;
private:
	int days;
	int hours;
};

class Forecast
{
	// Convenience aliases
	using Hours = std::vector<std::unique_ptr<HourForecast>>;
	using Days = std::vector<std::unique_ptr<DayForecast>>;

public:
	/**
	 * Constructor for Forecast
	 * 
	 * @param location_data Data for the forecast's location in JSON format
	 * @param options Option specifications for the forecast
	 */
	explicit Forecast(Json::Value &location_data, std::shared_ptr<ForecastOptions> options);

	Forecast(const Forecast&) = delete;
    Forecast& operator=(const Forecast&) = delete;
    ~Forecast() = default;

    /**
     * Populates this forecast's hour array
     * 
     * @param hours Hour array to get data from
     */
	void populate_hours(std::vector<std::shared_ptr<Json::Value>> hours);

	/**
	 * Prints this forecast's hours
	 */
	void print_hours();

	/**
     * Populates this forecast's day array
     * 
     * @param days Day array to get data from
     */
	void populate_days(Json::Value &days);

	/**
	 * Prints this forecast's days
	 */
	void print_days();
private:
	std::unique_ptr<Location> location;
	std::shared_ptr<ForecastOptions> options;
	Hours hours;
	Days days;
};

#endif // WEATHER_FORECAST_HPP_