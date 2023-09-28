#include "Player.h"

Player::Player(Vector2 position,
               Vector2 direction,
               int lives,
               float max_velocity,
               float min_velocity) : position(position), direction(direction), lives(lives), max_velocity(max_velocity), min_velocity(min_velocity)
{
}

Player::~Player()
{
    this->free();
}


void Player::render(SDL_Renderer* gRenderer)
{
    // Render red filled quad
    SDL_Rect fillRect = {(int)position.x, (int)position.y, 640 / 8, 480 / 8};
    SDL_SetRenderDrawColor(gRenderer,  0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(gRenderer, &fillRect);
}


void Player::free()
{
    // need to be implemented
}

void Player::move(Vector2& new_direction)
{

    if(new_direction != this->direction && new_direction != Vector2())
    {
        this->direction = new_direction;

    }


    Vector2 new_position = Vector2(position.x + (direction.x * max_velocity), position.y + (direction.y * max_velocity));
    this->position = new_position;






}
