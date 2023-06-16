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
	else {
		while (in.good()) {
			Setting temp = parseLine(in);
			if (temp.option == Setting::COUNT) {
				in.close();
				break;
			}
			settings[temp.option] = temp;
		}
	}
}

float Config::loadFromConfig(const Setting::Option& const setting) const
{
	return settings[setting].value;
}

void Config::saveToConfig(std::ofstream& file, const Setting::Option& option) const
{
	if( option == Setting::BoardSizeX)
	{
		file << option_delimiter_left << "BoardSize" << option_delimiter_right << '\n';
		file << settings[Setting::BoardSizeX].value << ", " << settings[Setting::BoardSizeY].value << '\n';
		return;
	}
	else if (option != Setting::BoardSizeY) {
		file << option_delimiter_left << option_names[option] << option_delimiter_right << '\n';
		file << settings[option].value << '\n';
	}
}

// TODO: Refactor, just set it directly to the config, like wdh
Config::Setting Config::parseLine(std::ifstream& const file)
{
	Setting select;
	select.option = getOptionFromLine(file);
	if (select.option == Setting::COUNT) {
		return select;
	}
	else if (select.option == Setting::BoardSizeX) {
		setToupleValuesFromLine(file);
		select.value = settings[Setting::BoardSizeX].value;
	}
	else {
		select.value = getValueFromLine(file);
	}
	return select;
}

Config::Setting::Option Config::getOptionFromLine(std::ifstream& const file) const
{
	std::string buffer;
	std::getline(file, buffer);
	if (buffer.empty()) {
		return Setting::COUNT;
	}
	cleanLine(buffer);
	Setting::Option option = Setting::COUNT;
	for (int i = 0; i < Config::Setting::COUNT; i++)
	{
		if ((i == Setting::BoardSizeX || i == Setting::BoardSizeY) && option == Setting::COUNT) {
			if (buffer.find("boardsize") != std::string::npos) {
				option = Setting::BoardSizeX;
				return option;
			}
		}
		else if (option == Setting::COUNT) {
			std::string name = option_names[i];
			for(int j = 0; j < name.length(); ++j) {
				name[j] = std::tolower(static_cast<unsigned char>(name[j]));
			}
			if (buffer.find(name) != std::string::npos) {
				option = Setting::Option(i);
				return option;
			}
		}
	}
}

float Config::getValueFromLine(std::ifstream& const file) const
{
	std::string buffer;
	std::getline(file, buffer);
	cleanLine(buffer);
	return std::stof(buffer);
}

void Config::setToupleValuesFromLine(std::ifstream& const file)
{
	std::string buffer;
	std::getline(file, buffer);
	cleanLine(buffer);
	settings[Setting::BoardSizeX].value = std::stof(buffer);
	settings[Setting::BoardSizeX].option = Setting::BoardSizeX;
	buffer.erase(0, buffer.find(',') + 1);
	settings[Setting::BoardSizeY].value = std::stof(buffer);
	settings[Setting::BoardSizeY].option = Setting::BoardSizeY;
}

void Config::cleanLine(std::string& string) const
{
	if (string[0] == comment_sign) {
		return;
	}
	for (int i = string.length() - 1; i >= 0; --i ) {
		switch (string[i]) {
		case ' ':
			string.erase(string.begin() + i);
			break;
		case option_delimiter_left:
			string.erase(string.begin() + i);
			break;
		case option_delimiter_right:
			string.erase(string.begin() + i);
			break;
		default:
			string[i] = std::tolower(static_cast<unsigned char>(string[i]));
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
