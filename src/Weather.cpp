#include "Weather.hpp"
#include "utils/symbols.hpp"

#include <sstream>

Weather::Weather(Json::Value &data, std::shared_ptr<WeatherOptions> options)
{
	this->options = options;

	const Json::Value &location = data["location"];
	this->location = std::make_unique<Location>(
		location["name"].asString(),
		location["region"].asString(),
		location["country"].asString(),
		location["localtime"].asString());

	const Json::Value &current = data["current"];
	this->temperatures = 
	{
		current["temp_f"].asDouble(),
		current["temp_c"].asDouble(),
		current["feelslike_f"].asDouble(),
		current["feelslike_c"].asDouble()
	};

	this->humidity = current["humidity"].asUInt();
	this->wind_mph = current["wind_mph"].asDouble();
	this->wind_kph = current["wind_kph"].asDouble();
	this->wind_direction = current["wind_dir"].asString();

	const Json::Value &condition = current["condition"];
	this->condition_code = condition["code"].asUInt();
	this->condition_text = condition["text"].asString();
}

std::string Weather::get_simple_str() 
{
	bool use_metric = this->options->use_metric();

	std::ostringstream os;
	os << this->temperatures.get_temp_str(use_metric);

	double feels_like = this->temperatures.get_feels_like(use_metric);
	double epsilon = use_metric ? this->options->feels_like_epsilon_c : this->options->feels_like_epsilon_f;

	// Only include real feel if there is a sufficient difference
	if (std::abs(feels_like - this->temperatures.get_temp(use_metric)) > epsilon)
	{
		os << " (Feels like " << feels_like << ")";
	}

	os << symbols::get_symbol_from_code(this->condition_code);
	return os.str();
}

std::ostream& operator<<(std::ostream &o, Weather &weather)
{
	o << *weather.location << ": " << weather.get_simple_str();
	if (weather.options->is_verbose())
	{
		bool use_metric = weather.options->use_metric();

		// Add misc. data
		o << std::endl << weather.condition_text << std::endl;
		o << "Local time: " << weather.location->local_time << std::endl;
		o << "Humidity: " << weather.humidity << "%" << std::endl;

		// Add wind data
		double wind_speed = use_metric ? weather.wind_kph : weather.wind_mph;
		std::string wind_units = use_metric ? " kph " : " mph ";
		o << "Wind: " << wind_speed << wind_units  << weather.wind_direction;
	}
	return o;
}