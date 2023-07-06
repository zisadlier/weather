# Weather Command Line Tool

![Static Badge](https://img.shields.io/badge/release-v1.0.0-blue?logoColor=red&label=release) ![Static Badge](https://img.shields.io/badge/C%2B%2B-17-green)

- [Weather Command Line Tool](#weather-command-line-tool)
  * [Features](#features)
  * [Prerequisites](#prerequisites)

## Features

- Get current weather for any location
- In addition to temperature and condition, can display extra info like humidity and wind data
- Get an hourly forecast
- Get a daily forecast
- Powered by https://www.weatherapi.com/

## Prerequisites
- GNU Make
- C++17 Compatiable Compiler
- cURLpp
- Boost
- libjsoncpp
- An API key from https://www.weatherapi.com/ (basic tier is free and allows near unlimited calls)

##Usage

**Below are the valid command line arguments for this application, any unknown arguments will be ignored:**

- -m: If present, metric units will be used when displaying information
- -v: If present, verbose output will be displayed (extra information)
- -l=[LOCATION]: Location to get weather information for e.g. boston,ma. Defaults to auto lookup by IP
- -o=[OPERATION]: Operation to perform, valid values are current, hourly, and daily. Defaults to current
- -r=[HOURS]: Number of hours to retrieve a forecast for, valid values are 1-24. Defaults to 12 and must be used with operation set to hourly
- -d=[DAYS]: Number of days to retrieve a forecast for, valid values are 1-14. Defaults to 3 and must be used with operation set to daily
- -h: Display this help message

**Before doing anything make sure you set an environment variable named WEATHER_API_KEY to an API key from https://www.weatherapi.com/ (it's free)**

All that needs to be done before running is compiling the tool
`$ make`

As an example, if we want to get verbose output for the current weather in Dallas, TX you would do
`$ ./weather -l dallas,tx -v`

To get a 6 hour forecast for your current location, you would do
`$ ./weather -o hourly -r 6`
