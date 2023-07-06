#ifndef WEATHER_UTILS_REQUESTS_HPP_
#define WEATHER_UTILS_REQUESTS_HPP_

#include <string>
#include <sstream>
#include <map>

#include <jsoncpp/json/json.h>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

namespace requests
{
	/**
	 * Performs a get request to an endpoint that responds with JSON
	 * 
	 * @param url The url to make the request to
	 * @returns JSON data of the response
	 */
	inline Json::Value perform_request(std::string url)
	{
		curlpp::Cleanup myCleanup;
		curlpp::Easy request;
		request.setOpt<curlpp::options::Url>(url);

		std::ostringstream response;
		request.setOpt(new curlpp::options::WriteStream(&response));

		request.perform();

		Json::Reader reader;
	    Json::Value data;
	    reader.parse(response.str(), data);

	    return data;
	}

	/**
	 * Sets a URL query parameter value
	 * 
	 * @param key Key name of the param
	 * @param value Value to set the param to
	 */
	inline std::string get_query_param_str(std::map<std::string, std::string> params)
	{
		std::ostringstream os;
		for (auto const& [key, val] : params)
		{
			os << key << "=" << val << "&";
		}

		// Delete the trailing &
		std::string values = os.str();
		values.pop_back();
		return values;
	}
}

#endif // WEATHER_UTILS_REQUESTS_HPP_