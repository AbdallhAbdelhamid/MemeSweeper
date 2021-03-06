/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
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
#include "MainWindow.h"
#include "Game.h"


Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	
	if(!minefield.GetGameStatus() )
	{

	if (wnd.mouse.LeftIsPressed() || wnd.mouse.RightIsPressed())
	{
		const Vei2 mousePos(wnd.mouse.GetPosX(), wnd.mouse.GetPosY());
		tilePressed = minefield.GetTilePressed(mousePos);

		if (tilePressed != -1 && lMouseReleased && wnd.mouse.LeftIsPressed())
		{
			minefield.setTile(tilePressed, TileState::Reaveled);
			minefield.CheckAround(tilePressed);
			lMouseReleased = false;
		}
		if (tilePressed != -1  && rMouseReleased&& wnd.mouse.RightIsPressed())
		{			
			minefield.setTile(tilePressed, TileState::Flagged);
			rMouseReleased = false;
		}

	}

	if (!wnd.mouse.RightIsPressed())
	{
		rMouseReleased = true;
	}

	if (!wnd.mouse.LeftIsPressed())
	{
		lMouseReleased = true;
	}

	minefield.CheckGame();
	

}

}

void Game::ComposeFrame()
{
	if (!Minefield::win)
	{
		minefield.DrawTiles(gfx);
	}
}

