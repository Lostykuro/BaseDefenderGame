#include "Base.h"

void Base::iniVariables()
{

}

//inicia a forma da base
void Base::initShape() 
{
	this->shape.setPosition(Vector2f(910.f,470.f));
	this->shape.setSize(Vector2f(50.f, 25.f));
	this->shape.setFillColor(Color(0, 0,0,0));
	this->shape.setOrigin(Vector2f(25.f, 12.5f));
	this->shape.setScale(Vector2f(9.5f, 11.f));



	this->bshape.loadFromFile("img/base.png");
	this->base_sprite.setTexture(this->bshape);
	this->base_sprite.setScale(Vector2f(0.5f, 0.5f));
	this->base_sprite.setOrigin(Vector2f(480.f, 280.f));
	this->base_sprite.setPosition(this->shape.getPosition().x, this->shape.getPosition().y);
}

void Base::liferegen()
{
	if (this->clock.getElapsedTime().asSeconds() >= 2 && vida + 1 < 101)
	{

		this->vida += 1;
		this->clock.restart();
	}
}

//construtores e destrutores

Base::Base()
{
	this->iniVariables();
	this->initShape();
}

Base::~Base()
{
}

//atualiza os atributos a cada frame
void Base::update(const RenderTarget* target)
{
	this->liferegen();
	float i = this->vida * 2.0f;
	Color cor = Color::Green;

	if (this->vida < 50) { cor = Color(255, 165, 0, 255); }
	if (this->vida < 25) { cor = Color(255, 0, 0, 255); }
	this->vidadabase.setFillColor(cor);
	this->vidadabase.setSize(Vector2f(i, 10.f));
	this->vidadabase.setPosition(Vector2f(this->shape.getPosition().x - 100, this->shape.getPosition().y - 200));

}
//desenha os atributos de Base
void Base::render(RenderTarget* target)
{



	target->draw(this->shape);
	target->draw(this->base_sprite);
	target->draw(this->vidadabase);


}

//função que recebe dano gerado por balas a cada frame e disconta na vida
void Base::receivedamage(int i)
{
	if (this->vida - i >= 0 && i == 1) {
		this->vida -= 1;
	}
}
//retornador de shape
RectangleShape Base::getshape()
{
	return this->shape;
}
//retornador de vida da base
int Base::getvida()
{
	return this->vida;
}
