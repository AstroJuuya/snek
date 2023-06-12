#include "Config.h"

void Config::loadConfig()
{
}

void Config::loadFromConfig(int& value, const Setting::Option& setting)
{
	value = int(settings[setting].value);
}

void Config::loadFromConfig(float& value, const Setting::Option& setting)
{
	value = settings[setting].value;
}
