#define _USE_MATH_DEFINES
#include <cmath> 
#include <cstdlib>
#include <ctime>
#include <cstdint>
#include "Mover.h"
#include "Explosion.h" 

Mover::Mover(int frameWidth, int frameHeight, int x, int y, int size, int color) :
    _frameWidth(frameWidth), _frameHeight(frameHeight),
    _x(static_cast<float>(x)), _y(static_cast<float>(y)),
    _size(size > 0 ? size : 20),
    _color(color),
    _paused(false)
{
    srand(static_cast<unsigned int>(time(nullptr)) ^ static_cast<unsigned int>(reinterpret_cast<uintptr_t>(this)));
    do {
        _dX = static_cast<float>(rand() % 21 - 10) / 5.0f;
        _dY = static_cast<float>(rand() % 21 - 10) / 5.0f;
    } while (fabs(_dX) < 0.1f && fabs(_dY) < 0.1f);
}

void Mover::setPos(float x, float y) {
    _x = x;
    _y = y;
}

void Mover::setSpeed(float dX, float dY) {
    _dX = dX;
    _dY = dY;
}

float Mover::getCurrentSpeedMagnitude() const {
    return std::sqrt(_dX * _dX + _dY * _dY);
}

void Mover::scaleSpeed(float factor) {
    _dX *= factor;
    _dY *= factor;
}

void Mover::checkWallCollision() {
    float floatSize = static_cast<float>(_size);
    float restitution = 0.9f;
    float epsilon = 0.01f;

    if (_x - floatSize < 0.0f) {
        _x = floatSize + epsilon;
        _dX = -_dX * restitution;
    }
    else if (_x + floatSize > _frameWidth) {
        _x = static_cast<float>(_frameWidth) - floatSize - epsilon;
        _dX = -_dX * restitution;
    }

    if (_y - floatSize < 0.0f) {
        _y = floatSize + epsilon;
        _dY = -_dY * restitution;
    }
    else if (_y + floatSize > _frameHeight) {
        _y = static_cast<float>(_frameHeight) - floatSize - epsilon;
        _dY = -_dY * restitution;
    }
}

void Mover::move() {
    if (_paused) return;
    _x += _dX;
    _y += _dY;
    checkWallCollision();
}

bool Mover::interactable(PopObject* otherObject) const {
    return dynamic_cast<Mover*>(otherObject) != nullptr && dynamic_cast<Explosion*>(otherObject) == nullptr;
}

void Mover::interact(PopObject* popObject) {
    
}


void Mover::doCommand(int command) {
    
}

void Mover::followTo(int targetX, int targetY) {
    float dirX = static_cast<float>(targetX) - _x;
    float dirY = static_cast<float>(targetY) - _y;
    float distance = std::sqrt(dirX * dirX + dirY * dirY);

    if (distance < 0.1f) {
        return;
    }
    float normalizedDirX = dirX / distance;
    float normalizedDirY = dirY / distance;
    float currentSpeed = getCurrentSpeedMagnitude();
    _dX = normalizedDirX * currentSpeed;
    _dY = normalizedDirY * currentSpeed;
}

void Mover::followAway(int targetX, int targetY) {
    float dirX = static_cast<float>(targetX) - _x;
    float dirY = static_cast<float>(targetY) - _y;
    float distance = std::sqrt(dirX * dirX + dirY * dirY);

    if (distance < 0.1f) {
        float currentSpeed = getCurrentSpeedMagnitude();
        if (currentSpeed > 0.1f) {
            _dX = -_dX;
            _dY = -_dY;
        }
        return;
    }
    float normalizedDirX = -dirX / distance;
    float normalizedDirY = -dirY / distance;
    float currentSpeed = getCurrentSpeedMagnitude();
    _dX = normalizedDirX * currentSpeed;
    _dY = normalizedDirY * currentSpeed;
}