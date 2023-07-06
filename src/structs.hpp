#ifndef WEATHER_STRUCTS_HPP_
#define WEATHER_STRUCTS_HPP_

#include "utils/symbols.hpp"

#include <iostream>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <string>
#include <sstream>

struct Location
{
	/**
	 * Constructor for location
	 * 
	 * @param name Town/city of the location
	 * @param region Region/state/province of the location
	 * @param country Country of the location
	 * @param local_time Local time string for the location
	 */
	Location(std::string name, std::string region, std::string country, std::string local_time)
		: name(std::move(name)), region(std::move(region)), local_time(std::move(local_time))
	{
		if (this->name.empty() || std::all_of(this->name.begin(), this->name.end(), [](char c){ return std::isspace(c); }))
		{
			throw std::runtime_error("Error (-l): Invalid location provided");
		}

		// Shortening of the USA text for readability
		if (country.find("United States of America") != std::string::npos) 
		{
			this->country = "United States";
		}
		else
		{
			this->country = std::move(country);
		}
	}

	/**
	 * Gets the integer hour (0-23) from the local_time member
	 * 
	 * @returns Hour as an integer
	 */
	int get_hour();

	friend std::ostream& operator<<(std::ostream &o, Location &loc)
	{
		 o << loc.name << ", ";
		 if (!loc.region.empty())
		 {
		 	o << loc.region << ", ";
		 }

		 return o << loc.country;
	}

	std::string name;
	std::string region;
	std::string country;
	std::string local_time;
};

struct Temperatures
{
	double temp_f;
	double temp_c;
	double feels_like_f;
	double feels_like_c;

	/**
     * Gets the actual tempertature as a decimal number
     * 
     * @param use_celcius If this is true will return temperature in celcius, farenheight otherwise
     * @returns Temperature in the specified units
     */
	double get_temp(bool use_celcius)
	{
		return use_celcius ? this->temp_c : this->temp_f;
	}

	/**
	 * Gets the temperature in the specified units and in a readable format
	 * 
	 * @param use_celcius Whether or not to get the temperature in celcius
	 * @returns Readable string representation of the temperature
	 */
	std::string get_temp_str(bool use_celcius)
	{
		std::ostringstream os;
		char unit = use_celcius ? 'C' : 'F';
		os << std::fixed << std::setprecision(1) << this->get_temp(use_celcius) << symbols::DEGREE_SYMBOL << unit;

		return os.str();
	}

	/**
     * Gets the real feel temperature as a decimal number
     * 
     * @param use_celcius If this is true will return temperature in celcius, farenheight otherwise
     * @returns Real feel temperature in the specified units
     */
	double get_feels_like(bool use_celcius)
	{
		return use_celcius ? this->feels_like_c : this->feels_like_f;
	}
};

struct ForecastTemperatures
{
	double min_f;
	double min_c;
	double max_f;
	double max_c;
	double avg_f;
	double avg_c;

	/**
     * Gets the minimum forecasted tempertature as a decimal number
     * 
     * @param use_celcius If this is true will return temperature in celcius, farenheight otherwise
     * @returns Temperature in the specified units
     */
	double get_min(bool use_celcius)
	{
		return use_celcius ? this->min_c : this->min_f;
	}

	/**
     * Gets the maximum forecasted tempertature as a decimal number
     * 
     * @param use_celcius If this is true will return temperature in celcius, farenheight otherwise
     * @returns Temperature in the specified units
     */
	double get_max(bool use_celcius)
	{
		return use_celcius ? this->max_c : this->max_f;
	}

	/**
     * Gets the average forecasted tempertature as a decimal number
     * 
     * @param use_celcius If this is true will return temperature in celcius, farenheight otherwise
     * @returns Temperature in the specified units
     */
	double get_avg(bool use_celcius)
	{
		return use_celcius ? this->avg_c : this->avg_f;
	}
};

#endif // WEATHER_STRUCTS_HPP_