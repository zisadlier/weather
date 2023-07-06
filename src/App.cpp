#include "App.hpp"
#include "utils/requests.hpp"

#include <iostream>
#include <sstream>
#include <unistd.h>
#include <cstdlib>
#include <vector>
#include <jsoncpp/json/json.h>

App::App(int argc, char *argv[])
{
	std::string api_key;

	// Read the API key from the environment
	const char *val = getenv("WEATHER_API_KEY");
	if (val != nullptr)
	{
		api_key = val;
	}
	else
	{
		throw std::runtime_error("Please set an environment variable named WEATHER_API_KEY to a valid key from weatherapi.com");
	}

	this->options = this->get_options_from_args(argc, argv, api_key);
}

void App::run()
{
	if (this->operation == "current")
	{
		std::unique_ptr<Weather> weather = this->get_current_weather();
		std::cout << *weather << std::endl;
	}
	else if (this->operation == "hourly")
	{
		std::unique_ptr<Forecast> forecast = this->get_hourly_forecast();
		forecast->print_hours();
	}
	else if (this->operation == "daily")
	{
		std::unique_ptr<Forecast> forecast = this->get_daily_forecast();
		forecast->print_days();
	}
}

void App::usage()
{
	std::ostringstream o;
	o << "Weather Tool " << this->version << std::endl;
	o << "Below are the valid command line arguments for this application, any unknown arguments will be ignored:" << std::endl;
	o << "	-m: If present, metric units will be used when displaying information" << std::endl;
	o << "	-v: If present, verbose output will be displayed (extra information)" << std::endl;
	o << "	-l=[LOCATION]: Location to get weather information for e.g. boston,ma. Defaults to auto lookup by IP" << std::endl;
	o << "	-o=[OPERATION]: Operation to perform, valid values are current, hourly, and daily. Defaults to current" << std:: endl;
	o << "	-r=[HOURS]: Number of hours to retrieve a forecast for, valid values are 1-24. Defaults to 12 and must be used with operation set to hourly" << std::endl;
	o << "	-d=[DAYS]: Number of days to retrieve a forecast for, valid values are 1-14. Defaults to 3 and must be used with operation set to daily" << std::endl;
	o << "	-h: Display this help message" << std::endl;

	std::cout << o.str();
}

std::shared_ptr<Options> App::get_options_from_args(int argc, char *argv[], std::string api_key)
{
	bool metric = false;
	bool verbose = false;
	std::string location = "auto:ip";
	std::string operation = "current";
	int hours = 12;
	int days = 3;

	int opt;
	while ((opt = getopt(argc, argv, "hmvl:o:r:d:")) != -1) 
	{
		switch (opt) 
		{
			case 'm':
				metric = true;
				break;
			case 'v':
				verbose = true;
				break;
			case 'l':
				location = optarg;
				break;
			case 'o':
				operation = optarg;
				break;
			case 'r':
				hours = std::stoi(optarg);
				if (hours < 1 || hours > 24)
				{
					throw std::runtime_error("Error (-r): Valid values for hour count are 1-24");
				}
				break;
			case 'd':
				days = std::stoi(optarg);
				if (days < 1 || days > 14)
				{
					throw std::runtime_error("Error (-d): Valid values for day count are 1-14");
				}
				break;
			case 'h':
				this->usage();
				exit(0);
			default:
				NOOP;
		}
	}

	this->operation = operation;

	// Run the specified operation
	std::shared_ptr<Options> options;
	if (operation == "current")
	{
		options = std::dynamic_pointer_cast<Options>(std::make_shared<WeatherOptions>(api_key, location, metric, verbose));
	}
	else if (operation == "hourly" || operation == "daily")
	{
		if (operation == "hourly")
		{
			days = this->HOURLY_FORECAST_DAYS;
		}
		options = std::dynamic_pointer_cast<Options>(std::make_shared<ForecastOptions>(api_key, location, metric, verbose, days, hours));
	}
	else
	{
		throw std::runtime_error("Error (-o): Invalid operation provided, must be one of: current, hourly, daily");
	}

	return options;
}

std::unique_ptr<Weather> App::get_current_weather()
{
	std::ostringstream url;
	url << this->BASE_URL << "current.json" << "?" << requests::get_query_param_str(this->options->get_request_args());

	Json::Value data = requests::perform_request(url.str());

    std::unique_ptr<Weather> weather = std::make_unique<Weather>(data, std::static_pointer_cast<WeatherOptions>(this->options)); 
    return std::move(weather);
}

std::unique_ptr<Forecast> App::get_hourly_forecast()
{
	std::shared_ptr<ForecastOptions> options = std::dynamic_pointer_cast<ForecastOptions>(this->options);

	std::ostringstream url;
	url << this->BASE_URL << "forecast.json" << "?" << requests::get_query_param_str(options->get_request_args());

	Json::Value data = requests::perform_request(url.str());

    std::unique_ptr<Forecast> forecast = std::make_unique<Forecast>(data["location"], options);

    std::vector<std::shared_ptr<Json::Value>> hours;
    for (uint i = 0; i < this->HOURLY_FORECAST_DAYS; ++i)
    {
    	for (Json::Value &hour : data["forecast"]["forecastday"][i]["hour"])
    	{
    		hours.push_back(std::make_shared<Json::Value>(hour));
    	}
    }

    forecast->populate_hours(hours);
    return std::move(forecast);
}

std::unique_ptr<Forecast> App::get_daily_forecast()
{
	std::shared_ptr<ForecastOptions> options = std::dynamic_pointer_cast<ForecastOptions>(this->options);

	std::ostringstream url;
	url << this->BASE_URL << "forecast.json" << "?" << requests::get_query_param_str(options->get_request_args());

	Json::Value data = requests::perform_request(url.str());

	std::unique_ptr<Forecast> forecast = std::make_unique<Forecast>(data["location"], options);
	forecast->populate_days(data["forecast"]["forecastday"]);
	return std::move(forecast);
}