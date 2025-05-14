#define _USE_MATH_DEFINES
#include <cmath> 
#include <cstdlib>
#include "Rotator.h"

Rotator::Rotator(int frameWidth, int frameHeight, int x, int y, int size, int color)
    : Mover(frameWidth, frameHeight, x, y, size, color)
{
    const float PI_F = static_cast<float>(M_PI);
    _alpha = static_cast<float>(rand()) / RAND_MAX * 2.0f * PI_F;
    
    float speed;
    do {
        speed = (static_cast<float>(rand()) / RAND_MAX * 0.45f + 0.05f);
    } while (speed < 0.01f); 
    int direction = (rand() % 2 == 0) ? 1 : -1;
    _dAlpha = speed * direction;
}

void Rotator::move() {
    Mover::move();

    if (!_paused) {
        _alpha += _dAlpha;
        const float TWO_PI_F = 2.0f * static_cast<float>(M_PI);

        
        while (_alpha >= TWO_PI_F) {
            _alpha -= TWO_PI_F;
        }
        while (_alpha < 0.0f) {
            _alpha += TWO_PI_F;
        }
    }
}