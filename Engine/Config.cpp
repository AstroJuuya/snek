#include "Config.h"

Config::Config(const Setting defaultValues[Setting::COUNT])
{
	for (int i = 0; i < Setting::COUNT; i++)
	{
		settings[i] = defaultValues[i];
	}
}

void Config::loadConfig()
{
	std::ifstream in("config.cfg");
	if (!in.is_open()) {
		std::ofstream newCfg("config.cfg");
		for (int i = 0; i < Setting::COUNT; i++)
		{
			saveToConfig(newCfg, Setting::Option(i));
		}
	}
}

float Config::loadFromConfig(const Setting::Option& setting) const
{
	return settings[setting].value;
}

void Config::saveToConfig(std::ofstream& file, const Setting::Option& option) const
{
	file << option_delimiter_left << option_names[option] << option_delimiter_right << '\n';
	if( option == Setting::BoardSizeX || option == Setting::BoardSizeY )
	{
		file << settings[Setting::BoardSizeX].value << ', ' << settings[Setting::BoardSizeY].value << '\n';
		return;
	}
	file << settings[option].value << '\n';
}

Config::Setting& Config::Setting::operator=(const Setting& setting)
{
	value = setting.value;
	return *this;
}

Config::Setting& Config::Setting::operator=(const int value)
{
	this->value = float(value);
	return *this;
}

Config::Setting& Config::Setting::operator=(const float value)
{
	this->value = value;
	return *this;
}
