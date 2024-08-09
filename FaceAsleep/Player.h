#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <cstdlib>
using namespace std;
using namespace sf;

class Player
{
private:
//clocks
	Clock c;
	Clock t;
	Clock z;
	Clock Cooldown;
	Clock Timercoletaveis;


//dropaveis
	vector<CircleShape> vidas;
	vector<RectangleShape> ammos;

//bullets:
	vector<CircleShape> bullets;
	vector<float> angles;

//mouse data:
	Vector2i mousePosition;
	const float lerpSpeed = 0.10f;
	Vector2f targetPosition;
	vector<Vector2f> bulletVelocities;

//sprite:
	RectangleShape vidadoplayer;
	RectangleShape municaodoplayer;
	Texture pshape;
	Sprite player_sprite;
	
//hitbox:
	RectangleShape shape; 
	Event event;
	

//variaveis de player
	float movementSpeed;
	int Vida = 100;
	int ammo = 50;
	float mousex;
	float mousey;

//metodos privados
	void iniVariables();
	void initShape();

public:
//metodos publicos
	Player(float x = 0.f, float y = 0.f);
	virtual ~Player();
	void mouseUpdater(RenderWindow* target);
	void updateInput();
	void updateWindowBoundsCollision(const RenderTarget* target);
	void update(const RenderTarget* target);
	void render(RenderTarget* target);

	void Setplayerposition(float x, float y);
	RectangleShape getplayershape();
	vector<CircleShape> getbullets();
	void killbullets(vector<RectangleShape> shapes);

	void vidaplayer(const RenderTarget* target);
	void ammoplayer();

	int getvida();
	void menosplayerVida(int i);

};