/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Board.h"
#include "Snake.h"
#include <random>
#include "SoundEffect.h"
#include "FrameTimer.h"
#include "Config.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	Board brd;
	Snake snek;
	Location delta_loc = {1,0};
	std::mt19937 rng;
	FrameTimer ft;
	SoundEffect sfxEat = SoundEffect( { L"Sounds\\Eat.wav" } );
	SoundEffect sfxSlither = SoundEffect( { L"Sounds\\Slither0.wav",L"Sounds\\Slither1.wav",L"Sounds\\Slither2.wav" } );
	Sound sndMusic = Sound( L"Sounds\\Music_Loop.wav",Sound::LoopType::AutoFullSound );
	Sound sndTitle = Sound( L"Sounds\\Title.wav" );
	SoundEffect sndFart = SoundEffect( { L"Sounds\\Fart.wav" } );
	static constexpr float snekMovePeriodMin = 0.040f;
	static constexpr float snekMovePeriodSpeedup = 0.15f; // SPEEDHACK
	static constexpr int nPoison = 240; // Poison Amount
	static constexpr int nFood = 12; // Food Amount
	float snekMovePeriod = 0.4f;
	float snekMoveCounter = 0.0f;
	static constexpr float snekSpeedupFactor = 0.93f; // Speedup Rate on Poison eat
	bool gameIsOver = false;
	bool gameIsStarted = false;
	float soundVolume = 0.2f; // Sound Volume
	Config::Setting defaultValues[Config::Setting::COUNT]{
		defaultValues[Config::Setting::TileSize] = 20,
		defaultValues[Config::Setting::BoardSizeX] = 30,
		defaultValues[Config::Setting::BoardSizeY] = 22,
		defaultValues[Config::Setting::SpeedupRate] = 0.93f,
		defaultValues[Config::Setting::PoisonAmount] = 240,
		defaultValues[Config::Setting::FoodAmount] = 12,
		defaultValues[Config::Setting::SoundVolume] = 0.2f
	};
	Config config = defaultValues;
	/********************************/

/* TODOLIST
The homework is to modify Poison Snek so that various game settings can be configured by the user by editing a text file.
The settings file should be parseable regardless of the order of the settings in the file.
The following settings are recommended:

WIP	+ Read configuratons from File
		+ [Tile Size] -> constrain max tile size
		+ [Board Size] -> constrain max board size
		+ [Speedup Rate]
		+ [Poison Amount] -> constrain max poison amount
		+ [Food Amount] -> constrain max food amount
		+ [Sound Volume] !!! -> constrain max volumes up to 2.0f

WIP		+ handle malformed/missing input files
DONE		+ create defaults
			+ handle multiple calls in the config (ignore any after the first)
			+ ignore case and whitespace
			+ constrain and validate values to be sensical

			+ display config warning at the head of the config (#W, #E)
				+ max amount of lines being the amount of config options
				+ always override #W and #E lines in the beginning and  prepend to / delete lines from  the config if  more / less  are needed
				+ for both Warns and Errs
				+ can only be Warns or Errs
				+ one for the declaration and one for the value(s)
				+ ignore comments supersceded by # afterwards

	+ Make game restartable (return to menu)

For this homework, you are not required to handle malformed input files, though you can attempt to handle those as a bonus challenge if you like. 
*/
};