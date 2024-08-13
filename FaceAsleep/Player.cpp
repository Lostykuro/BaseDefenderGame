#include "Player.h"
#include <iostream>
#include <math.h>
using namespace sf;
using namespace std;

//inicializa as variaveis de player
void Player::iniVariables()
{
	this->targetPosition = Vector2f(875.f, 460.f);
	this->movementSpeed = 10.f;
	this->mousex = 0.f;
	this->mousey = 0.f;
}
//inicializa o formato e sprite de player
void Player::initShape()
{
	this->pshape.loadFromFile("img/player.png");
	this->player_sprite.setTexture(pshape);

	this->shape.setFillColor(Color(100,100,100,0));
	this->shape.setSize(Vector2f(68.f, 68.f));
	this->shape.setOutlineColor(Color(0,0,0,0));
	this->shape.setOutlineThickness(10.f);

	this->shape.setPosition(Vector2f(640.f, 360.f));
}

//construtor de player
Player::Player(float x, float y)
{
	this->shape.setPosition(x, y);

	this->iniVariables();
	this->initShape();
}

//destrutor de player
Player::~Player()
{

}

//movimentação antiga (discontinuada) WASD // funciona ainda como um dash tough :p
void Player::updateInput()
{

	//Input Teclado
	//
	//Esquerda
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		this->shape.move(-this->movementSpeed, 0.f);
	}
	//Direita
	else if (Keyboard::isKeyPressed(Keyboard::D))
	{
		this->shape.move(this->movementSpeed, 0.f);
	}
	//Cima
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		this->shape.move(0.f, -this->movementSpeed);
	}
	//Baixo
	else if (Keyboard::isKeyPressed(Keyboard::S))
	{
		this->shape.move(0.f, this->movementSpeed);
	}

}

//guarda  e lida com os atributos de player envolvendo o mouse
void Player::mouseUpdater(RenderWindow* target)
{
	if (Keyboard::isKeyPressed(Keyboard::Q) && this->c.getElapsedTime().asSeconds() > 0.3 && this->ammo > 0) // if da bala
	{
		this->bullets.push_back(CircleShape());
		this->bullets.back().setRadius(5);
		this->bullets.back().setOrigin(5, 5);
		this->bullets.back().setPosition(this->shape.getPosition().x + 34, this->shape.getPosition().y + 34);

		this->angles.push_back(atan2(Mouse::getPosition(*target).y - shape.getPosition().y, Mouse::getPosition(*target).x - shape.getPosition().x));
		
		float angle = atan2(Mouse::getPosition(*target).y - shape.getPosition().y, Mouse::getPosition(*target).x - shape.getPosition().x);// variavel temporaria de angulo
		this->bulletVelocities.push_back(Vector2f(16 * cos(angle), 16 * sin(angle))); //armazena a velocidade individual de cada bala
		
		this->c.restart();
		this->ammo -= 1;
	}
	//input mouse
	if (Mouse::isButtonPressed(Mouse::Right)) {
		// Obtém as coordenadas do mouse

		this->mousePosition = Mouse::getPosition(*target);
		this->targetPosition = Vector2f(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
	}

}

// colisão com a borda da janela
void Player::updateWindowBoundsCollision(const RenderTarget* target)
{
	sf::FloatRect playerBounds = this->shape.getGlobalBounds();
	//Left
	if (playerBounds.left < 0.f)
		this->shape.setPosition(10.f, playerBounds.top);
	//Top
	if (playerBounds.top < 0.f)
		this->shape.setPosition(playerBounds.left, 10.f);
	//Right
	if (playerBounds.left + playerBounds.width > target->getSize().x)
		this->shape.setPosition(target->getSize().x - playerBounds.width, playerBounds.top);
	//Down
	if (playerBounds.top + playerBounds.height > target->getSize().y)
		this->shape.setPosition(playerBounds.left, target->getSize().y - playerBounds.height);
	//Left-Top
	if (playerBounds.left < 0.f && playerBounds.top < 10.f)
		this->shape.setPosition(10.f, 10.f);
	//Left-Down
	if (playerBounds.left < 0.f && playerBounds.top + playerBounds.height > target->getSize().y)
		this->shape.setPosition(10.f, target->getSize().y - playerBounds.height);
	//Right-Top
	if (playerBounds.left + playerBounds.width > target->getSize().x && playerBounds.top < 0.f)
		this->shape.setPosition(target->getSize().x - playerBounds.width, 10.f);
	//Right-Down
	if (playerBounds.left + playerBounds.width > target->getSize().x && playerBounds.top + playerBounds.height > target->getSize().y)
		this->shape.setPosition(target->getSize().x - playerBounds.width, target->getSize().y - playerBounds.height);
}

//atualiza os atributos de player a cada frame
void Player::update(const RenderTarget* target)
{
	this->vidaplayer(target);
	this->ammoplayer();
	this->updateInput();

	this->player_sprite.setPosition(this->shape.getPosition().x -31, this->shape.getPosition().y -23 );

	//Colisão com a borda da janela
	this->updateWindowBoundsCollision(target);
}

// desenha os atributos de player na tela
void Player::render(RenderTarget* target)
{
	//desenha vidas
	for (int i = 0; i < this->vidas.size(); i++) {
		target->draw(this->vidas[i]);


	}

	//desenha munições
	for (int i = 0; i < this->ammos.size(); i++) {
		target->draw(this->ammos[i]);


	}
	//suaviza o movimento de player
	Vector2f currentPosition = shape.getPosition();
	shape.setPosition(currentPosition + lerpSpeed * (targetPosition - currentPosition));

	//bullets:
	for (int i = 0; i < bullets.size() ; i++) {
		target->draw(this->bullets[i]);
        // Atualizar a posição do projétil
        this->bullets[i].move(bulletVelocities[i]);

        // Reduzir a velocidade do projétil
        bulletVelocities[i] *= 0.98f;

	}

	//player collision box
	target->draw(this->shape);

	target->draw(this->player_sprite);

	target->draw(this->vidadoplayer);

	target->draw(this->municaodoplayer);
}

//modificador da posição do player
void Player::Setplayerposition(float x, float y ) {
	this->shape.setPosition(x, y);

}

//retornador de shape
RectangleShape Player::getplayershape() {

	return this->shape;

}

//retornador de bullets
vector<CircleShape> Player::getbullets(){
	return this->bullets;
}

//função que lida com collisões relacionadas ao objeto player
void Player::killbullets(vector<RectangleShape> shapes) {

	//variaveis de colisão dos obejetos
	FloatRect shapesBounds; 
	FloatRect bulletBounds;
	FloatRect vidasBounds;
	FloatRect ammosBounds;
	FloatRect playerBounds = this->shape.getGlobalBounds();



	// apaga as balas do player de vez se tiver mais de 25 balas no mapa
	if (this->bullets.size() >= 25) {
		for (int i = 0; i < this->bullets.size()-1; i++)
		{
			this->bullets[i].setFillColor(Color::Red);
			this->bullets.erase(bullets.begin()+i);
			this->bulletVelocities.erase(bulletVelocities.begin() + i);
			this->angles.erase(angles.begin() + i);
		}
	}

	// apaga as balas do player gradualmente
	for (int i = 0; i < this->bullets.size(); i++) 
	{
		if (this->t.getElapsedTime().asSeconds() > 1 && this->bulletVelocities[i].x < 0.0003 && this->bulletVelocities[i].y < 0.0003 && bullets.size()>=2) {

			this->bullets.erase(bullets.begin());
			this->bulletVelocities.erase(bulletVelocities.begin());
			this->angles.erase(angles.begin());

			this->t.restart();
		}

	}
	//spawna as vidas e munições
	for (int j = 0; j < shapes.size(); j++) {
		shapesBounds = shapes[j].getGlobalBounds();
		for (int i = 0; i < this->bullets.size(); i++) {
			bulletBounds = bullets[i].getGlobalBounds();
			if (shapesBounds.intersects(bulletBounds)) {
				if (((rand() % 3) + 1) == 3) {
					this->vidas.push_back(CircleShape());
					this->vidas.back().setRadius(20);
					this->vidas.back().setOrigin(20, 20);
					this->vidas.back().setFillColor(Color::Green);
					this->vidas.back().setPosition(shapes[j].getPosition().x, shapes[j].getPosition().y);
					this->Timercoletaveis.restart();

				}

				if (((rand() % 4) + 1) == 1) {
					this->ammos.push_back(RectangleShape());
					this->ammos.back().setSize(Vector2f(100, 50));
					this->ammos.back().setOrigin(50, 35);
					this->ammos.back().setFillColor(Color::Blue);
					this->ammos.back().setOutlineColor(Color::White);
					this->ammos.back().setOutlineThickness(5.f);
					this->ammos.back().setPosition(shapes[j].getPosition().x, shapes[j].getPosition().y);
					this->Timercoletaveis.restart();

				}

			}
		}
	}  
	// checa a colisão do player com a vida
	for (int j = 0; j < vidas.size(); j++) {
		vidasBounds = this->vidas[j].getGlobalBounds();

		if (vidasBounds.intersects(playerBounds)) {
			this->vidas.erase(vidas.begin() + j);
			if (this->Vida + 20 > 100){
				this->Vida = 100;
			}
			else { this->Vida += 20; }

		}
		
	}
	
	//checa a colisão do player com a caixa de munições
	for (int j = 0; j < ammos.size(); j++) {
		ammosBounds = this->ammos[j].getGlobalBounds();

		if (ammosBounds.intersects(playerBounds)) {
			this->ammos.erase(ammos.begin() + j);
			if (this->ammo + ((rand() % 29) + 1) > 50) {
				this->ammo = 50;
			}
			else { this->ammo += 20; }

		}

	}

	//checa a colisão do player com o inimigo
	for (int j = 0; j < shapes.size(); j++) {
		shapesBounds = shapes[j].getGlobalBounds();
		if (shapesBounds.intersects(playerBounds)) {
			if (Cooldown.getElapsedTime().asSeconds() > 1 ) {
				if (this->Vida - 10 >= 0) {
					this->Vida -= 10;
					Cooldown.restart();
				}
				else { this->Vida = 0; }
			}

		}
	}

	//apaga coletaveis depois de um tempo
	if (Timercoletaveis.getElapsedTime().asSeconds() > 5 ) {
		if (ammos.size() > 0) {
			this->ammos.erase(ammos.begin());
			this->Timercoletaveis.restart();
		}
		if (vidas.size() > 0) {
			this->vidas.erase(vidas.begin());
			this->Timercoletaveis.restart();
		}


	}
}

//desenha a vida do player
void Player::vidaplayer(const RenderTarget* target) 
{
	float i = this->Vida * 1.0f;
	Color cor = Color::Green;

	if (this->Vida < 50) { cor = Color(255, 165, 0, 255); }
	if (this->Vida < 25) { cor = Color(255, 0, 0, 255); }
	this->vidadoplayer.setFillColor(cor);
	this->vidadoplayer.setSize(Vector2f(i, 10.f));
	this->vidadoplayer.setPosition(Vector2f(this->shape.getPosition().x-16, this->shape.getPosition().y -30));



}

void Player::ammoplayer()
{
	float i = this->ammo * 2.f;
	Color cor = Color::Cyan;
	if (this->ammo < 25) { cor = Color(0, 0, 255, 255); }
	this->municaodoplayer.setFillColor(cor);
	this->municaodoplayer.setSize (Vector2f(10.f, i));
	this->municaodoplayer.setRotation(180.f);
	this->municaodoplayer.setPosition(Vector2f(this->shape.getPosition().x + 100, this->shape.getPosition().y + 90));

}


int Player::getvida() 
{
	return this->Vida;
}

// da dano no player quando acertado por um bala atravez de um função de enemy spawner em game.cpp
void Player::menosplayerVida(int i)
{
	if (this->Vida - i >= 0 && i ==1) {
		this->Vida -= 2;
	}
}


