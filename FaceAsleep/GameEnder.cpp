#include "GameEnder.h"

void GameEnder::initshape()
{
	this->centerscreen.setSize(Vector2f(1.f, 1.f));
	this->centerscreen.setOrigin(Vector2f(0.5, 0.5));
	this->centerscreen.setPosition(Vector2f(910.f, 490.f));

}

GameEnder::GameEnder()
{
	this->initshape();
}

GameEnder::~GameEnder()
{
}

bool GameEnder::lifetracker(int p, int b,Time timer, RenderTarget* target)
{
	if (p <= 0 || b <= 0 ) {
		this->GOtexture.loadFromFile("img/gameover.png");
		this->GOsprite.setTexture(GOtexture);
		this->GOsprite.setOrigin(Vector2f(480.f, 280.f));
		this->GOsprite.setScale(Vector2f(1.f, 1.f));
		this->GOsprite.setPosition(Vector2f(this->centerscreen.getPosition().x, this->centerscreen.getPosition().y));
		target->draw(GOsprite);
		return true;
	}
	else if(timer.asSeconds() > 160) {
		this->GOtexture.loadFromFile("img/gameover0.png");
		this->GOsprite.setTexture(GOtexture);
		this->GOsprite.setOrigin(Vector2f(480.f, 280.f));
		this->GOsprite.setScale(Vector2f(1.f, 1.f));
		this->GOsprite.setPosition(Vector2f(this->centerscreen.getPosition().x, this->centerscreen.getPosition().y));
		target->draw(GOsprite);
		return true;
	}
	else
	{
		return false;
	}

}

void GameEnder::update(const RenderTarget* target)
{
	this->GOsprite.setPosition(Vector2f(this->centerscreen.getPosition().x, this->centerscreen.getPosition().y));
}

void GameEnder::render(RenderTarget* target)
{
	target->draw(GOsprite);
	
}
