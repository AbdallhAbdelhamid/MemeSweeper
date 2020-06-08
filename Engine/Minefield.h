#pragma once

#include "Vei2.h"
#include "Graphics.h"
#include "SpriteCodex.h"
#include "RectI.h"
#include <random>


enum class TileState
{
	Reaveled,
	Unreavled,
	Flagged,
};

struct NearTiles
{
	int tiles_index[8] = { -1 };
	int nBomb = 0;
};

class Minefield
{

private:

	class Tile
	{
	public:

		Tile(Vei2 pos_in);
		Tile();
		Vei2 GetPos() const;
		void SetPos(const Vei2& pos_in);
		void SetRect(const Vei2& topLeft);
		void SetBomb();
		bool CheckBomb() const;
		TileState GetState() const;
		void SetState(TileState state);
		void DrawTile(Graphics& gfx);
		bool IsMouseIn(const Vei2& mousePos_in)const;
		void setNBombs();
		


	public:
		static constexpr int height = 14;
		static constexpr int width = 14;
		int nBombs = 0;
		bool drawNum = false;
		bool checked = false;


	private:

		TileState state = TileState::Unreavled ;
		bool hasBomb = false;
		Vei2 pos;
		RectI rect;

	};

	static constexpr int width = 70; 
	static constexpr int height = 70;
	
	static constexpr int nRowTile = width / SpriteCodex::tileSize ;
	static constexpr int nColTile = height / SpriteCodex::tileSize ;
	static constexpr int nTiles = nColTile * nRowTile;

	int top[nRowTile - 2];
	int bot[nRowTile - 2];
	int right[nColTile - 2];
	int left[nColTile - 2];

	Tile tiles[nTiles];



public:

	Minefield();
	void DrawTiles(Graphics& gfx);
	int GetTilePressed(const Vei2& mousePos);
	void setTile(const int& index, const TileState& state_in);
	void CheckGame();
	bool GetGameStatus()const;
	void CheckAround(const int& index);

	void SetNBombs();

public:


private:


	NearTiles GetAroundTiles(const int& tileIndex);

	static constexpr int nMines = 20;
	static constexpr int padding = 10;
	static constexpr int x_off = 200;
	static constexpr int y_off = 150;
	bool gameOver = false;
	std::random_device rd;
	std::mt19937 rng;
	std::uniform_int_distribution<int> mineDist;



};

