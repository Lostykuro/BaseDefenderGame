#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class inimigo
{
private:
    RectangleShape forma;
    int vida;
    int dano;
public:
    inimigo();

    // funções para modificar e pegar atributos de Forma
    void setPosition(const Vector2f& position);
    void setSize(const Vector2f& size);
    void setScale(const Vector2f& factors);
    void setFillColor(const Color& color);
    void setOutlineColor(const Color& color);
    void setOutlineThickness(float thickness);
    void setOrigin(const Vector2f& origin);
    const Vector2f& getSize() const;
    const RectangleShape& getForma() const; 
    void Enemyrotate();

    // funções de vida
    int getdamage();
    void receivedamage(int damage);
    



};

