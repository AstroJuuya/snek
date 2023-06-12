#include "Config.h"

void Config::loadConfig()
{
}

void Config::loadFromConfig(int& value, const Setting::Option& setting) const
{
	value = int(settings[setting].value);
}

void Config::loadFromConfig(float& value, const Setting::Option& setting) const
{
	value = settings[setting].value;
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
