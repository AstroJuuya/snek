#pragma once

#include <fstream>
#include <string>

class Config
{
public:
	struct Setting
	{
		Setting() = default;
		Setting& operator=(const Setting& setting);
		Setting& operator=(const int value);
		Setting& operator=(const float value);
		~Setting() = default;
		enum Option
		{
			TileSize,
			BoardSizeX,
			BoardSizeY,
			SpeedupRate,
			PoisonAmount,
			FoodAmount,
			SoundVolume,
			COUNT
		};
		float value = 0;
		Option option = COUNT;
	};

public:
	Config();
	Config(const Setting defaultValues[Setting::COUNT]);
	Config& operator=(const Config& const lhs) = delete;
	~Config() = default;
	void loadConfig();
	float loadFromConfig(const Setting::Option& const setting) const;

private:
	void saveToConfig(std::ofstream& file, const Setting::Option& const option) const;
	Setting parseLine(std::ifstream& const file);
	Setting::Option getOptionFromLine(std::ifstream& const file) const;
	float getValueFromLine(std::ifstream& const file) const;
	void setToupleValuesFromLine(std::ifstream& const file);
	void cleanLine(std::string& string) const;

private:
	Setting settings[Setting::COUNT];
	static constexpr char comment_sign = '#';
	static constexpr char option_delimiter_left = '[';
	static constexpr char option_delimiter_right = ']';
	const std::string option_names[Setting::COUNT]
	{
		"TileSize",
		"BoardSizeX",
		"BoardSizeY",
		"SpeedupRate",
		"PoisonAmount",
		"FoodAmount",
		"SoundVolume"
	};
};