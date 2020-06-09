#include "Minefield.h"


bool Minefield::Tile::StopPlay = false;
int Minefield::nCurFlags = 0;
int Minefield::win = false;
int Minefield::nFlaggedMines = 0;

Minefield::Minefield()
	:
	mineDist(0,nTiles),
	rng( rd() )
{
	int n = 0;
	Vei2 topleft(x_off + padding ,y_off + padding);
	for (int i = 0 ; i < nColTile ; i++)
	{
		for (int j = 0; j < nRowTile; j++)
		{
			Vei2 position = topleft + Vei2(14 * j, 14 * i);
			tiles[n].SetPos(position);
			tiles[n].SetRect(position);
			n++;
		}

	}

	for (int i = 0; i < nMines ; i++)
	{
		int x;
		do
		{
			 x = mineDist(rng);
		} while (tiles[x].CheckBomb() );
		tiles[x].SetBomb();

	}

	int x = 0;
	for (int i = 0 ; i < nRowTile - 2 ; i++ )
	{
		x++;
		top[i] = x;
	}
	x = ( (nRowTile - 1) * nColTile);
	for (int i = 0 ; i < nRowTile - 2 ; i++)
	{
		x++;
		bot[i] =   x;
	}

	x = 0;
	for (int i = 0 ; i < nColTile - 2 ; i++)
	{
		x += 4;
		left[i] = x;
	}

	x = nRowTile-1 ;
	for (int i = 0 ; i < nColTile - 2; i ++)
	{
		x += 4;
		right[i]= x;
	}
	
}


Minefield::Tile::Tile(Vei2 pos_in)
	:
	pos(pos_in),
	rect(pos,width,height)
{
}

Minefield::Tile::Tile()
	:
	pos({0,0}),
	rect(pos, width, height)
{
}


TileState Minefield::Tile::GetState() const
{
	return state;
}

void Minefield::Tile::SetState(TileState state_in)
{
	{
		if (state == TileState::Unreavled && state_in == TileState::Reaveled)
		{
			state = TileState::Reaveled;
		}

		else if (state == TileState::Unreavled && state_in == TileState::Flagged && nCurFlags < nFlags )
		{
			state = TileState::Flagged;		
			nCurFlags++;
		}

		else if (state == TileState::Flagged && state_in == TileState::Flagged)
		{
			state = TileState::Unreavled;
			nCurFlags--;
		}

		else if (state == TileState::Flagged && state_in == TileState::Reaveled && StopPlay )
		{
			state = TileState::Reaveled;
		}


	}
}

void Minefield::CheckGame()
{
	int test = 0;
	for (Tile& tile : tiles)
	{
		if (tile.CheckBomb() && tile.GetState() == TileState::Reaveled)
		{
			gameOver = true;
			Tile::StopPlay = true;
		}
	}
	if (gameOver)
	{
		for (Tile& tile : tiles)
		{
			tile.SetState(TileState::Reaveled);
		}
	}

	for (Tile& tile : tiles)
	{
		if (tile.CheckBomb() && tile.GetState() == TileState::Flagged)
		{
			nFlaggedMines++;
		}

		if (tile.GetState() == TileState::Reaveled || tile.drawNum )
		{
			test++;
		}
	}

	if (nCurFlags == nMines && test == nTiles - nMines)
	{
		win = true;
	}

}

bool Minefield::GetGameStatus() const
{
	return gameOver;
}


bool Minefield::Tile::CheckBomb() const
{
	return hasBomb;
}

void Minefield::Tile::DrawTile(Graphics& gfx)
{
	{
		if (!drawNum && !hasBomb || (hasBomb && state == TileState::Unreavled) || (hasBomb && state == TileState::Flagged))
		{
			switch (GetState())
			{
 
			case TileState::Reaveled:
				SpriteCodex::DrawTile0(pos, gfx);
				break;
			case TileState::Unreavled:
				SpriteCodex::DrawTileButton(pos, gfx);
				break;
			case TileState::Flagged:
				SpriteCodex::DrawTileFlag(pos, gfx);
				break;
 
			}
		}
		else if (drawNum == true && !hasBomb ||  ( (hasBomb && state == TileState::Unreavled) || (hasBomb && state == TileState::Flagged) ) )

		{
			switch (this->nBombs)
			{
			case 0:
				SpriteCodex::DrawTile0(pos, gfx);
				break;
			case 1:
				SpriteCodex::DrawTile1(pos, gfx);
				break;
			case 2:
				SpriteCodex::DrawTile2(pos, gfx);
				break;
			case 3:
				SpriteCodex::DrawTile3(pos, gfx);
				break;
			case 4:
				SpriteCodex::DrawTile4(pos, gfx);
				break;
			case 5:
				SpriteCodex::DrawTile5(pos, gfx);
				break;
			case 6:
				SpriteCodex::DrawTile6(pos, gfx);
				break;
			case 7:
				SpriteCodex::DrawTile7(pos, gfx);
				break;
			case 8:
				SpriteCodex::DrawTile8(pos, gfx);
				break;
			}

		}
		else
		{
			SpriteCodex::DrawTileBomb(pos, gfx);
		}

	}
}

bool Minefield::Tile::IsMouseIn(const Vei2& mousePos_in) const
{
	RectI rect1 = RectI(mousePos_in, 1, 1);

	return rect.IsOverlappingWith(rect1);
}

void Minefield::Tile::setNBombs()
{
}

Vei2 Minefield::Tile::GetPos() const
{
	return pos;
}

void Minefield::Tile::SetPos(const Vei2& pos_in)
{
	pos = pos_in;
}

void Minefield::Tile::SetRect(const Vei2& topLeft)
{
	rect = RectI(topLeft, width, width );
}

void Minefield::Tile::SetBomb()
{
	hasBomb = true;
}



void Minefield::DrawTiles(Graphics& gfx)
{
	
	for (Tile& t : tiles)
	{
		t.DrawTile(gfx);
	}
}

int Minefield::GetTilePressed(const Vei2& mousePos)
{
	int pressed = -1;
	for (int i = 0; i < nTiles; i++)
	{

		if (tiles[i].IsMouseIn(mousePos))
		{
			pressed = i;
			break;
		}

	}

	return pressed;
}

void Minefield::setTile(int index, const TileState& state_in)
{
	tiles[index].SetState(state_in);
}


void Minefield::CheckAround(int tileIndex)	// checks the 8 tiles for bombs , returns number of bombs;
{
	SetNBombs();
	if (tiles[tileIndex].GetState() != TileState::Flagged && !tiles[tileIndex].drawNum )
	{
		NearTiles nearTiles = GetAroundTiles(tileIndex);

		for (int i = 0; i < 8; i++)
		{


			if (nearTiles.tiles_index[i] != -1 &&
				tiles[nearTiles.tiles_index[i]].nBombs == 0 &&
				!tiles[nearTiles.tiles_index[i]].checked &&
				tiles[nearTiles.tiles_index[i]].CheckBomb() == false)
			{
				tiles[nearTiles.tiles_index[i]].SetState(TileState::Reaveled);
				tiles[nearTiles.tiles_index[i]].checked = true;
				CheckAround(nearTiles.tiles_index[i]);
			}
			else if (nearTiles.tiles_index[i] != -1 && tiles[nearTiles.tiles_index[i]].GetState() != TileState::Flagged)
			{
				tiles[nearTiles.tiles_index[i]].drawNum = true;
			}

		}

		for (int i = 0; i < nTiles; i++)
		{
			if (tiles[i].CheckBomb())
			{
				tiles[i].drawNum = false;
			}
		}
	}
}

void Minefield::SetNBombs()
{
	for (int i = 0 ; i< nTiles ; i++)
	{
		NearTiles nearTiles = GetAroundTiles(i);
		
		tiles[i].nBombs = nearTiles.nBomb;
	}

}

 NearTiles Minefield::GetAroundTiles(int tileIndex)// returns a struct of nearby 8 tiles
{
	 NearTiles nearTiles;

	 nearTiles.tiles_index[0] = -1 ;
	 nearTiles.tiles_index[1] = -1;
	 nearTiles.tiles_index[2] = -1 ;
								
	 nearTiles.tiles_index[3] = -1;
	 nearTiles.tiles_index[4] = -1;
								 
	 nearTiles.tiles_index[5] = -1 ;
	 nearTiles.tiles_index[6] = -1;
	 nearTiles.tiles_index[7] = -1 ;

	 if (tileIndex == 0)
	 {

		 nearTiles.tiles_index[4] = tileIndex + 1;

		 nearTiles.tiles_index[6] = tileIndex + nRowTile;
		 nearTiles.tiles_index[7] = tileIndex + nRowTile + 1;
	 }

	 else if (tileIndex == nRowTile-1)
	 {
		 nearTiles.tiles_index[3] = tileIndex - 1;

		 nearTiles.tiles_index[5] = tileIndex + nRowTile - 1;
		 nearTiles.tiles_index[6] = tileIndex + nRowTile;
	 }

	 else if (tileIndex == nTiles-nRowTile)
	 {
		 nearTiles.tiles_index[1] = tileIndex - nRowTile;
		 nearTiles.tiles_index[2] = tileIndex - nRowTile + 1;
		 nearTiles.tiles_index[4] = tileIndex + 1;
	 }


	 else if (tileIndex == nTiles-1)
	 {
		 nearTiles.tiles_index[0] = tileIndex - nRowTile - 1;
		 nearTiles.tiles_index[1] = tileIndex - nRowTile;
		 nearTiles.tiles_index[3] = tileIndex - 1;
	 }

	 else if (Belongs(tileIndex,top))
	 {
		 nearTiles.tiles_index[3] = tileIndex - 1;
		 nearTiles.tiles_index[4] = tileIndex + 1;

		 nearTiles.tiles_index[5] = tileIndex + nRowTile - 1;
		 nearTiles.tiles_index[6] = tileIndex + nRowTile;
		 nearTiles.tiles_index[7] = tileIndex + nRowTile + 1;
	 }

	 else if (Belongs(tileIndex, bot))

	 {
		 nearTiles.tiles_index[0] = tileIndex - nRowTile - 1;
		 nearTiles.tiles_index[1] = tileIndex - nRowTile;
		 nearTiles.tiles_index[2] = tileIndex - nRowTile + 1;

		 nearTiles.tiles_index[3] = tileIndex - 1;
		 nearTiles.tiles_index[4] = tileIndex + 1;
	 }

	 else if (Belongs(tileIndex, left))

	 {
		 nearTiles.tiles_index[4] = tileIndex + 1;

		 nearTiles.tiles_index[1] = tileIndex - nRowTile;
		 nearTiles.tiles_index[2] = tileIndex - nRowTile + 1;

		 nearTiles.tiles_index[6] = tileIndex + nRowTile;
		 nearTiles.tiles_index[7] = tileIndex + nRowTile + 1;
	 }

	 else if (Belongs(tileIndex, right))

	 {
		 nearTiles.tiles_index[0] = tileIndex - nRowTile - 1;
		 nearTiles.tiles_index[1] = tileIndex - nRowTile;

		 nearTiles.tiles_index[3] = tileIndex - 1;

		 nearTiles.tiles_index[5] = tileIndex + nRowTile - 1;
		 nearTiles.tiles_index[6] = tileIndex + nRowTile;
	 }

	 else
	 {
		 nearTiles.tiles_index[0] = tileIndex - nRowTile - 1;
		 nearTiles.tiles_index[1] = tileIndex - nRowTile;
		 nearTiles.tiles_index[2] = tileIndex - nRowTile + 1;

		 nearTiles.tiles_index[3] = tileIndex - 1;
		 nearTiles.tiles_index[4] = tileIndex + 1;

		 nearTiles.tiles_index[5] = tileIndex + nRowTile - 1;
		 nearTiles.tiles_index[6] = tileIndex + nRowTile;
		 nearTiles.tiles_index[7] = tileIndex + nRowTile + 1;
	 }


	 for (int i = 0; i < 8; i++)
	 {
		 if ( nearTiles.tiles_index[i]!= -1 && tiles[ nearTiles.tiles_index[i] ].CheckBomb() )
		 {
			 nearTiles.nBomb++;
		 }
	 }
	 return nearTiles;
}

bool Minefield::Belongs(int index_in ,const std::array<int, nRowTile - 2>& array )const
{
	for (int index : array)
	{
		if (index == index_in)
		{
			return true;
		}
	}
	return false;
}