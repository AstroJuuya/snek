#pragma once

#include "Graphics.h"
#include "Location.h"
#include "Config.h"
#include <random>

class Board
{
public:
	enum class CellContents
	{
		Empty,
		Obstacle,
		Food,
		Poison
	};
public:
	Board( Graphics& gfx, Config& cfg );
	void DrawCell( const Location& loc,Color c );
	int GetGridWidth() const;
	int GetGridHeight() const;
	bool IsInsideBoard( const Location& loc ) const;
	CellContents GetContents( const Location& loc ) const;
	void ConsumeContents( const Location& loc );
	void SpawnContents( std::mt19937& rng,const class Snake& snake,CellContents contents );
	void DrawBorder();
	void DrawCells();
private:
	static constexpr Color borderColor = Colors::Blue;
	static constexpr Color obstacleColor = Colors::Gray;
	static constexpr Color poisonColor = { 64,8,64 };
	static constexpr Color foodColor = Colors::Red;
	int dimension = 20; // Tile Size // TODO: make dimension dynamic to fill the board if not set
	static constexpr int cellPadding = 1;
	int width = 30; // Board Size x
	int height = 22; // Board Size y
	static constexpr int borderWidth = 4;
	static constexpr int borderPadding = 2;
	static constexpr int x = 70;
	static constexpr int y = 50;
	CellContents* contents = nullptr;
	Graphics& gfx;
};