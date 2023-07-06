#ifndef WEATHER_UTILS_SYMBOLS_HPP_
#define WEATHER_UTILS_SYMBOLS_HPP_

#include <string>

namespace symbols
{
	const std::string DEGREE_SYMBOL = "\u00B0";

	/**
	 * Maps a weatherapi condition code to an appropriate unicode character
	 * 
	 * @param code Code from weatherapi to use
	 * @returns Unicode character that best visually represents the given code
	 */
	inline std::string get_symbol_from_code(uint code)
	{
		std::string symbol;
		switch (code)
		{
			case 1000: // Sunny
				symbol = " ☀️ "; // ☀️
				break;
			case 1003: // Partly cloudy
				symbol = " \u26C5 "; // ⛅
				break;
			case 1006: // Cloudy
			case 1009: // Overcast
				symbol = " ☁️ "; // ☁️
				break;
			case 1030: // Mist
			case 1135: // Fog
			case 1147: // Freezing fog
				symbol = " \U0001F32B "; // 🌫 
				break;
			case 1063: // Patchy rain possible
			case 1072: // Patchy freezing drizzle possible
			case 1168: // Freezing drizzle
			case 1171: // Heavy freezing drizzle
			case 1183: // Light rain
			case 1189: // Moderate rain
			case 1192: // Heavy rain at times
			case 1195: // Heavy rain
			case 1198: // Light freezing rain
			case 1201: // Moderate or heavy freezing rain
			case 1240: // Light rain shower
			case 1243: // Moderate or heavy rain shower
			case 1246: // Torrential rain shower
				symbol = " \U0001F327 "; // 🌧
				break;
			case 1066: // Patchy snow possible
			case 1114: // Blowing snow
			case 1117: // Blizzard
			case 1204: // Light sleet
			case 1207: // Moderate or heavy sleet
			case 1210: // Patchy light snow
			case 1213: // Light snow
			case 1216: // Patchy moderate snow
			case 1219: // Moderate snow
			case 1222: // Patchy heavy snow
			case 1225: // Heavy snow
			case 1237: // Ice pellets
			case 1249: // Light sleet showers
			case 1252: // Moderate or heavy sleet showers
			case 1255: // Light snow showers
			case 1258: // Moderate or heavy snow showers
			case 1261: // Light showers of ice pellets
			case 1264: // Moderate or heavy showers of ice pellets
				symbol = " \U0001F328 "; // 🌨
				break;		
			case 1087: // Thundery outbreaks possible
				symbol = " \U0001F329 "; // 🌩
				break;
			case 1150: // Patchy light drizzle
			case 1153: // Light drizzle
			case 1180: // Patchy light rain
			case 1186: // Moderate rain at times
				symbol = " \U0001F326 "; // 🌦
				break;				
			case 1273: // Patchy light rain with thunder
			case 1276: // Moderate or heavy rain with thunder
			case 1279: // Patchy light snow with thunder
			case 1282: // Moderate or heavy snow with thunder
				symbol = " \u26C8 "; // ⛈
				break;
			default:
				symbol = " \uFF1F ";
				break;
		}

		return symbol;
	}
}

#endif //WEATHER_UTILS_SYMBOLS_HPP_