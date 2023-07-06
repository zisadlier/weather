#include "Forecast.hpp"
#include "utils/dates.hpp"

#include <memory>

ForecastOptions::ForecastOptions(std::string api_key, std::string location, bool metric, bool verbose, int days, int hours)
	: Options(api_key, location, metric, verbose)
{
	this->hours = hours;
	this->days = days;
}

std::map<std::string, std::string> ForecastOptions::get_request_args()
{
	std::map<std::string, std::string> request_args = Options::get_request_args();
	request_args["days"] = std::to_string(this->days);

	return request_args;
}

int ForecastOptions::get_hours() const
{
	return this->hours;
}

int ForecastOptions::get_days() const
{
	return this->days;
}

Forecast::Forecast(Json::Value &location_data, std::shared_ptr<ForecastOptions> options)
{
	this->location = std::make_unique<Location>(
		location_data["name"].asString(),
		location_data["region"].asString(),
		location_data["country"].asString(),
		location_data["localtime"].asString());
	this->options = options;

	this->hours = Hours();
	this->days = Days();
}

void Forecast::populate_hours(std::vector<std::shared_ptr<Json::Value>> hours)
{
	for (std::shared_ptr<Json::Value> hour : hours)
	{
		std::unique_ptr<HourForecast> hour_forecast = std::make_unique<HourForecast>(*hour, this->options->use_metric(), this->options->is_verbose());
		this->hours.push_back(std::move(hour_forecast));
	}
}

void Forecast::print_hours()
{
	int num_hours = this->options->get_hours();
	std::cout << num_hours << " hour forecast for " << *this->location << " at " << this->location->local_time << std::endl;

	int count = -1;
	int start_hour = dates::get_hour_from_date(this->location->local_time);
	for (auto &hour : this->hours)
	{
		if (hour->get_hour() == start_hour)
		{
			// Once we reach the current hour, start displaying information
			count = 0;
		}

		if (count >= 0)
		{
			std::cout << *hour << std::endl;
			++count;
		}

		if (count > num_hours)
		{
			break;
		}
	}
}

void Forecast::populate_days(Json::Value &days)
{
	for (auto &day : days)
	{
		std::unique_ptr<DayForecast> day_forecast = std::make_unique<DayForecast>(day, this->options->use_metric(), this->options->is_verbose());
		this->days.push_back(std::move(day_forecast));
	}
}

void Forecast::print_days()
{
	for (auto &day : this->days)
	{
		std::cout << *day << std::endl;
	}
}