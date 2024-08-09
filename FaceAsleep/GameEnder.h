#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
class GameEnder
{
private:
	Texture GOtexture;
	Sprite GOsprite;

	RectangleShape centerscreen;



	void initshape();

public:

	GameEnder();
	virtual ~GameEnder();

	bool lifetracker(int p, int b, Time timer , RenderTarget* target);

	void update(const RenderTarget* target);
	void render(RenderTarget* target);



};

