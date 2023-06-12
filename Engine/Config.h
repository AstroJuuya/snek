#pragma once

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
	void loadFromConfig(int& value, const Setting::Option& setting) const;
	void loadFromConfig(float& value, const Setting::Option& setting) const;

private:
	Setting settings[Setting::COUNT];
};