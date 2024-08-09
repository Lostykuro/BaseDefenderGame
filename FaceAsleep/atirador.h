#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <cstdlib>
#include <random>
#include <iostream>
using namespace std;
using namespace sf;

class atirador
{
private:
	RectangleShape shape;

	Clock z;
	double timer = 1.0;

	vector<CircleShape> bullets;
	vector<float> angles;
	vector<Vector2f>bulletVelocities;
public:
	void initshape();
	atirador(RectangleShape eshape);
	virtual ~atirador();


	void update(const RenderTarget* target);
	void render(RenderTarget* target);

	vector<CircleShape> get_bullets();
	vector<float> get_angles();
	void set_position(RectangleShape bshape);

	void atirando(float x, float y);
	int collision_player_check(RectangleShape pshape);
};

