#include "atirador.h"
using namespace std;
using namespace sf;


//inicializa o formato do atirador
void atirador::initshape()
{
	this->shape.setSize(Vector2f(20.f, 20.f));
	this->shape.setOrigin(Vector2f(10.f, 10.f));
	this->shape.setFillColor(Color::Yellow);
}

atirador::atirador(RectangleShape eshape)
{
	this->shape.setPosition(Vector2f(eshape.getPosition().x, eshape.getPosition().y));
}

atirador::~atirador()
{
}

void atirador::update(const RenderTarget* target)
{
}
//desenha as balas na tela
void atirador::render(RenderTarget* target)
{
	for (int i = 0; i < bullets.size(); i++) {
		target->draw(this->bullets[i]);
		// Atualizar a posição do projétil
		this->bullets[i].move(bulletVelocities[i]);


	}
}
//retornadores
vector<CircleShape> atirador::get_bullets()
{
	return this->bullets;
}

vector<float> atirador::get_angles()
{
	return this->angles;
}
//modificadores
void atirador::set_position(RectangleShape bshape)
{
	this->shape.setPosition(Vector2f(bshape.getPosition().x, bshape.getPosition().y));
}
//função de atirar na posição do player a cada frame
void atirador::atirando(float x, float y)
{
	if (this->z.getElapsedTime().asSeconds() > this->timer) {
		this->bullets.push_back(CircleShape());
		this->bullets.back().setRadius(10);
		this->bullets.back().setOrigin(10, 10);
		this->bullets.back().setFillColor(Color::Red);
		this->bullets.back().setPosition(this->shape.getPosition().x + 34, this->shape.getPosition().y + 34);

		this->angles.push_back(atan2(y - shape.getPosition().y, x - shape.getPosition().x));

		float angle = atan2(y - shape.getPosition().y, x - shape.getPosition().x);// variavel temporaria de angulo
		this->bulletVelocities.push_back(Vector2f(16 * cos(angle), 16 * sin(angle)));
	
	
		this->z.restart();
	}
}
//função para deletar a bala apos colisão e retornar um valor de dano por frame
int atirador::collision_player_check(sf::RectangleShape pshape)
{
	sf::FloatRect playerBounds = pshape.getGlobalBounds();
	bool collisionDetected = false;

	for (int i = 0; i < bullets.size(); /* sem incremento aqui */)
	{
		sf::FloatRect bulletBounds = this->bullets[i].getGlobalBounds();
		if (bulletBounds.intersects(playerBounds)) {
			this->bullets.erase(bullets.begin() + i);
			this->angles.erase(angles.begin() + i);
			this->bulletVelocities.erase(bulletVelocities.begin() + i);
			collisionDetected = true;
		}
		else {
			++i;
		}
	}

	return collisionDetected ? 1 : 0;
}


