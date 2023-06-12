#pragma once

class Config
{
public:
	struct Setting
	{
		Setting() = default;
		Setting& operator=(Setting& setting)
		{
			value = setting.value;
		}
		Setting& operator=(int value)
		{
			this->value = float(value);
		}
		Setting& operator=(float value)
		{
			this->value = value;
		}
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
	void loadConfig();
	void loadFromConfig(int& value, const Setting::Option& setting);
	void loadFromConfig(float& value, const Setting::Option& setting);

private:
	Setting settings[Setting::COUNT];
};