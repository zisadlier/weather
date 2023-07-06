#ifndef WEATHER_OPTIONS_HPP_
#define WEATHER_OPTIONS_HPP_

#include <string>
#include <map>

class Options
{
public:
	const double feels_like_epsilon_f = 1.0;
	const double feels_like_epsilon_c = 0.5;

	Options(std::string api_key, std::string location, bool metric, bool verbose)
		: api_key(std::move(api_key)), location(std::move(location)), metric(metric), verbose(verbose)
	{}

	/**
	 * Gets the metric member
	 * 
	 * @returns metric
	 */
	bool use_metric() const;

	/**
	 * Gets the verbose member
	 * 
	 * @returns verbose
	 */
	bool is_verbose() const;

	/**
	 * Gets relevant data from this object
	 * 
	 * @returns Data as a map
	 */
	virtual std::map<std::string, std::string> get_request_args();
private:
	bool metric;
	bool verbose;
	std::string api_key;
	std::string location;
};

#endif // WEATHER_OPTIONS_HPP_