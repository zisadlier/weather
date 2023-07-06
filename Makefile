COMPILER = g++
LIBS = -lcurlpp -lcurl -ljsoncpp -lboost_system
SOURCES = src/main.cpp src/App.cpp src/Weather.cpp src/Forecast.cpp src/DayForecast.cpp src/HourForecast.cpp src/Options.cpp

build:
	$(COMPILER) $(SOURCES) $(LIBS) -o weather