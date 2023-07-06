#include "Options.hpp"

bool Options::use_metric() const
{
	return this->metric;
}

bool Options::is_verbose() const
{
	return this->verbose;
}

std::map<std::string, std::string> Options::get_request_args()
{
	std::map<std::string, std::string> request_args;
	request_args["key"] = this->api_key;
	request_args["q"] = this->location;

	return request_args;
}