#pragma once
#include <iostream>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <cmath>
#include <vector>
#include "Player.h"
#include "Base.h"
#include"EnemySpawner.h"
#include"GameEnder.h"
#include <sstream>
using namespace sf;
using namespace std;
class Game
{
private:
	GameEnder gameender;

	VideoMode videoMode;
	RenderWindow* window;
	bool endGame;
	Event sfmlEvent;
	Music music;
	bool paused = false;
	
	//timer:
	Clock dt_time;
	Time acummulated_time;
	Time delta_time;
	stringstream timer_text;
	Font fonte;
	Text Timer;



	//objects

	EnemySpawner enemySpawner;

	Player player;
	Base base;



	void initVariables();
	void initWindow();


public:
	//Construtores e Destrutores
	Game();
	~Game();

	//Acessadores


	//Modificadores


	//Funções
	const bool running() const;
	void pollEvents();

	void update();
	void render();

};

