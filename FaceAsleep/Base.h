#pragma once
#include "Player.h"

using namespace sf;

class Base
{
private:
	Texture bshape;
	Sprite base_sprite;
	Clock clock;

	int vida= 100;

	RectangleShape shape;
	RectangleShape vidadabase;

	void iniVariables();
	void initShape();



public:
	
	Base();
	virtual ~Base();
	void update(const RenderTarget* target);
	void liferegen();
	void render(RenderTarget* target);
	void receivedamage(int i);
	RectangleShape getshape();
	int getvida();
};

