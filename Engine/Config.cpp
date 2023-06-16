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
	//else {
	//	while (in.good()) {
	//
	//	}
	//}
}

float Config::loadFromConfig(const Setting::Option& const setting) const
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

Config::Setting Config::parseLine(std::ifstream& const file)
{
	Setting select;
	select.option = getOptionFromLine(file);
	select.value = getValueFromLine(file);
	return select;
}

Config::Setting::Option Config::getOptionFromLine(std::ifstream& const file) const
{
	std::string buffer;
	std::getline(file, buffer);
	cleanLine(buffer);
	Setting::Option option = Setting::COUNT;
	for (int i = 0; i < Config::Setting::COUNT && i < Setting::COUNT; i++)
	{
		if ((i == Setting::BoardSizeX || i == Setting::BoardSizeY) && option == Setting::COUNT) {
			if (buffer.find("boardsize") != std::string::npos) {
				option = Setting::BoardSizeX;
			}
		}
		else if (option == Setting::COUNT) {
			std::string option = option_names[i];
			for each (char c in option) {
				c = std::tolower(static_cast<unsigned char>(c));
			}
			if (buffer.find(option) != std::string::npos) {
				option = Setting::Option(i);
			}
		}
	}
	return option;
}

float Config::getValueFromLine(std::ifstream& const file) const
{
	std::string buffer;
	std::getline(file, buffer);
	cleanLine(buffer);
	return std::stof(buffer);
}

float Config::getValueFromLine(std::ifstream& const file, const Setting::Option& option) const
{
	std::string buffer;
	std::getline(file, buffer);
	cleanLine(buffer);
	if (option == Setting::BoardSizeY) {
		buffer.erase(0, buffer.find(','));
		return std::stof(buffer);
	}
	return std::stof(buffer);
}

void Config::cleanLine(std::string& string) const
{
	if (string[0] == comment_sign) {
		return;
	}
	for each (char c in string) {
		switch (c) {
		case ' ':
			string.erase(c);
			break;
		case option_delimiter_left:
			string.erase(c);
			break;
		case option_delimiter_right:
			string.erase(c);
			break;
		default:
			c = std::tolower(static_cast<unsigned char>(c));
		}
	}
}

Config::Setting& Config::Setting::operator=(const Setting& const setting)
{
	value = setting.value;
	option = setting.option;
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
