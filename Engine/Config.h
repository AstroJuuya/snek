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
	};

public:
	Config() = delete;
	Config(const Setting defaultValues[Setting::COUNT]);
	Config& operator=(const Config& lhs) = delete;
	~Config() = default;
	void loadConfig();
	float loadFromConfig(const Setting::Option& setting) const;

private:
	void saveToConfig(std::ofstream& file, const Setting::Option& option) const;

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