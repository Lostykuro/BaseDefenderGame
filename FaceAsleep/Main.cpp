
#include <iostream>
#include "Game.h"

using namespace sf;

int main()
{
	//Iniciar Seed aleatoria
	srand(static_cast<unsigned>(time(0)));



	//Iniciar objeto jogo
	Game game;
	
	//Loop do Jogo
	while (game.running())
	{
		game.update();
		game.render();
	}


	// fim do jogo
	return 0;
}