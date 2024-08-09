#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <cstdlib>
#include <random>
#include <iostream>
#include "atirador.h"
using namespace std;
using namespace sf;

class EnemySpawner
{
private:
	Clock z;
	double timer = 5.0;
	vector<RectangleShape> shapes;
	vector<CircleShape> bullets;
	vector<atirador> atiradores;

	vector<float> angles;

	RectangleShape mira;



	Vector2f playerPosition;
	const float lerpSpeed = 0.02f;
	Vector2f targetPosition;
	bool gamerun = true;


public:

	void init_variables();
	EnemySpawner();

	virtual ~EnemySpawner();


	void Enemy_creator(RenderWindow* target, RectangleShape player);
	void set_mira(float x, float y);

	void update(const RenderTarget* target);
	void render(RenderTarget* target);
	void setgamerunoff();

	void killenemy(vector<CircleShape> pbullets);
	vector<RectangleShape> getenemies();

	int damaged_per_bullet(RectangleShape pshape);

};