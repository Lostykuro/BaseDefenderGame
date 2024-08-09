#include "EnemySpawner.h"


void EnemySpawner::init_variables()
{
}

EnemySpawner::EnemySpawner()
{

}

EnemySpawner::~EnemySpawner()
{
}

void EnemySpawner::Enemy_creator(RenderWindow* target, RectangleShape player)
{

	// criação do inimigo
	if (gamerun==true ) 
	{
		if( this->z.getElapsedTime().asSeconds() > this->timer){
		this->shapes.push_back(RectangleShape());
		float sizerandoness = rand() % 50;
		this->shapes.back().setSize(Vector2f(20.f + sizerandoness,20.f + sizerandoness));
		this->shapes.back().setOrigin(10, 10);
		this->shapes.back().setFillColor(Color(255 , rand() % 100, rand() % 100, 255));
		this->atiradores.push_back(atirador(this->shapes.back())); // cria um atirador para o inimigo
		int placerandoness =( rand() % 4 ) + 1;

		if (placerandoness==1){ this->shapes.back().setPosition(rand() % 1820, 0); }
		if (placerandoness == 2) { this->shapes.back().setPosition(rand() % 1820, 980); }
		if (placerandoness == 3) { this->shapes.back().setPosition(0, rand() % 980); }
		if (placerandoness == 4) { this->shapes.back().setPosition(1820, rand() % 980); }

		if (this->timer > 0.5f) { //diminuoção do timer de criação de inimigo
			this->timer -= 0.10f;
		}

		}

		if (this->z.getElapsedTime().asSeconds() > this->timer){


			this->angles.push_back(atan2(this->mira.getPosition().y - shapes.back().getPosition().y, this->mira.getPosition().x - shapes.back().getPosition().x));
			this->z.restart();
		}

			this->playerPosition = this->mira.getPosition();
			this->targetPosition = Vector2f(static_cast<float>(this->mira.getPosition().x), static_cast<float>(this->mira.getPosition().y));
		
	}

}


void EnemySpawner::set_mira(float x, float y)
{
	this->mira.setPosition(x, y);

	for (int i = 0; i < this->atiradores.size(); i++) {
		this->atiradores[i].atirando(x,y);

	}
}

void EnemySpawner::update(const RenderTarget* target)
{
	// faz os atiradores ficarem presos aos seus respectivos inimigos
	for (int i = 0; i< this->atiradores.size(); i++) { 
		this->atiradores[i].set_position(this->shapes[i]);

	}
}

void EnemySpawner::render(RenderTarget* target)
{
	for (int i = 0; i < this->atiradores.size(); i++) {
		this->atiradores[i].render(target);

	}

	for (int i = 0; i < shapes.size(); i++) {
		Vector2f currentPosition = shapes[i].getPosition();
		shapes[i].setPosition(currentPosition + lerpSpeed * (targetPosition - currentPosition));
		target->draw(this->shapes[i]);
		this->shapes[i].move(4 * cos(angles[i]), 4 * sin(angles[i]));

	}

}

void EnemySpawner::setgamerunoff()
{
	this->gamerun = false;
}


// mata inimigo ao entrar em contato com a bala
void EnemySpawner::killenemy(vector<CircleShape> pbullets)
{
	FloatRect enemyBounds;
	FloatRect bulletBounds;


	for (int j = 0; j < pbullets.size(); j++) {
		bulletBounds = pbullets[j].getGlobalBounds();
		for (int i = 0; i < this->shapes.size(); i++) {
			enemyBounds = shapes[i].getGlobalBounds();
			if (bulletBounds.intersects(enemyBounds)) {

				this->shapes.erase(shapes.begin() + i);
				this->atiradores.erase(atiradores.begin() + i);
				
			}
		}
	}


}


//retorna o vetor de inimigos
vector<RectangleShape> EnemySpawner::getenemies( )
{
	return this->shapes;
}

int EnemySpawner::damaged_per_bullet(sf::RectangleShape pshape) // checar a colisão das balas com o player um bool
{
	for (int j = 0; j < atiradores.size(); j++) {
		if (this->atiradores[j].collision_player_check(pshape) == 1) {
			return 1;
		}
	}
	return 0;
}


