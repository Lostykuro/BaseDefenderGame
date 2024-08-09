#include "Game.h"
#include <string>
using namespace sf;

void Game::initVariables()
{
	this->fonte.loadFromFile("fonts/Minecraft.ttf");
	this->Timer.setFont(fonte);
	this->Timer.setCharacterSize(30);
	this->Timer.setFillColor(sf::Color::White);
	this->Timer.setPosition(Vector2f(1500, 130));
	this->acummulated_time = Time::Zero;
	this->music.openFromFile("audio/track1.ogg");
	this->music.setVolume(50);
	this->music.setLoop(true);
	this->player.Setplayerposition(910.0, 490.0);
	this->music.play();
	this->endGame = false;
	this->paused = false;
}



void Game::initWindow()
{
	this->videoMode = VideoMode(1820,980);
	this->window = new RenderWindow(this->videoMode, "Infra Green", Style::Close | Style::Titlebar);
	this->window->setFramerateLimit(60);

}

//Construtores e Destrutores
Game::Game()
{
	this->initVariables();
	this->initWindow();

}


Game::~Game()
{
	delete this->window;

}

//Funções

const bool Game::running() const
{
	return this->window->isOpen();
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->sfmlEvent)) 
	{
		switch (this->sfmlEvent.type)
		{
		case Event::Closed:
			this->enemySpawner.setgamerunoff();
			this->window->close();

			break;
		case Event::KeyPressed:
			// fecha o jogo
			if (this->sfmlEvent.key.code == Keyboard::Escape)
				this->window->close();
			//pausa o jogo
			if (this->sfmlEvent.key.code == Keyboard::P) {
				if (this->paused == false) {
					this->acummulated_time += this->dt_time.getElapsedTime();
					this->paused = true;
				}
				else if (this->paused == true) {
					this->dt_time.restart();
					this->paused = false;
				}

			}
			break;
		}
	}
}

void Game::update()
{
	this->pollEvents(); // checa por eventos globais de teclas;

	if (this->paused == false) {
		this->delta_time = this->acummulated_time + dt_time.getElapsedTime();//atualiza o delta time
		this->timer_text.str("");//limpa a string do timer
		this->timer_text.clear();
		this->timer_text << "Tempo:" << delta_time.asSeconds(); //atualiza a string do timer
		this->Timer.setString(this->timer_text.str());
		paused = this->gameender.lifetracker(this->player.getvida(), this->base.getvida(), delta_time, this->window); // pausa o jogo caso tenha sido finalizado
		this->gameender.update(this->window); 
		this->enemySpawner.set_mira(this->player.getplayershape().getPosition().x, this->player.getplayershape().getPosition().y); //coloca a mira dos inimigos na posição do jogador a cada frame
		this->player.update(this->window); 
		this->player.mouseUpdater(this->window);//atualiza os comandos do mouse dentro da tela a cada frame
		this->base.update(this->window);
		this->player.menosplayerVida(this->enemySpawner.damaged_per_bullet(this->player.getplayershape()));//diminui a vida do player sempre que enconstar em uma bala
		this->base.receivedamage(this->enemySpawner.damaged_per_bullet(this->base.getshape()));//diminui a vida da base sempre que encostar em uma bala
		this->enemySpawner.update(this->window);
		this->enemySpawner.Enemy_creator(this->window, this->player.getplayershape());//criador de inimigos que seguem uma mira que esta na posição do jogador
		this->player.killbullets(this->enemySpawner.getenemies()); // executa funções relacionadas a colisão de atributos da classe Player / sim, o nome esta errado
		this->enemySpawner.killenemy(this->player.getbullets());// mata inimigos sempre que entram em contato com as balas do player a cada frame
	}

}

void Game::render()
{
	this->window->clear();
	
	//Desenha as coisas 
	this->base.render(this->window);
	this->player.render(this->window);
	this->enemySpawner.render(this->window);
	this->gameender.render(this->window);
	this->window->draw(this->Timer); // desenha o timer
	this->window->display();




}


