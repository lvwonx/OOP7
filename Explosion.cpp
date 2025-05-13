#define _USE_MATH_DEFINES // Needed for M_PI if used in draw/move logic (basic draw doesn't need it)
#include <cmath>
#include <cstdlib>

#include "Explosion.h"
#include "Manager.h" // Needed for manager->remove(this)
#include "Mover.h"   // Needed for dynamic_cast in interactable

// Need access to Color/SolidBrush from System::Drawing
using System::Drawing::SolidBrush;
using System::Drawing::Color;
using System::Drawing::Graphics;

Explosion::Explosion(int frameWidth, int frameHeight, int x, int y, int lifeTime)
// Explosions are centered at x,y. Set initial size (e.g., small).
// They don't move, so speed is 0.
// Color can be initialized here (e.g., Red or Yellow).
    : Mover(frameWidth, frameHeight, x, y, 5, Color::OrangeRed.ToArgb()), // Initial size and color
    _lifeTime(lifeTime > 0 ? lifeTime : 30), // Ensure positive life time
    _initialLifeTime(lifeTime > 0 ? lifeTime : 30)
{
    // Explosions don't move physically, only animate
    _dX = 0.0f;
    _dY = 0.0f;
    _paused = false; // Ensure it animates
}

void Explosion::draw(Graphics^ g) {
    // Basic explosion drawing: a growing circle that fades out
    float currentPhase = static_cast<float>(_lifeTime) / _initialLifeTime; // 1.0 at start, 0.0 at end
    float progress = 1.0f - currentPhase; // 0.0 at start, 1.0 at end

    // Calculate size based on animation progress (e.g., grows from _size up to 4x _size)
    int currentSize = static_cast<int>(_size + progress * (_size * 3.0f));

    // Calculate alpha (transparency) based on phase (e.g., starts opaque, fades to transparent)
    int alpha = static_cast<int>(currentPhase * 255); // Starts at 255, ends at 0

    // Calculate color based on progress (e.g., Red -> Orange -> Yellow -> White/Transparent)
    Color startColor = System::Drawing::Color::OrangeRed;
    Color endColor = System::Drawing::Color::Yellow; // Or White, or just fade the start color

    int r = static_cast<int>(startColor.R + progress * (endColor.R - startColor.R));
    int gr = static_cast<int>(startColor.G + progress * (endColor.G - startColor.G));
    int b = static_cast<int>(startColor.B + progress * (endColor.B - startColor.B));


    Color drawColor = Color::FromArgb(alpha, r, gr, b);

    SolidBrush^ brush = gcnew SolidBrush(drawColor);

    float diameter = 2.0f * currentSize;
    // Draw ellipse centered at the explosion's position (_x, _y)
    g->FillEllipse(brush, _x - currentSize, _y - currentSize, diameter, diameter);

    delete brush;
}

void Explosion::move() {
    // Call base move to handle pause state (although it won't change position as speed is 0)
    Mover::move();

    if (!_paused) {
        _lifeTime--; // Decrement life time

        if (_lifeTime <= 0) {
            // Animation is complete, request self-removal from the manager
            // Use the global manager pointer
            if (manager != nullptr) {
                manager->remove(this);
            }
            // Note: After calling manager->remove(this), 'this' object is deleted
            // and should not be accessed further by this object's methods.
            // The Manager's loop will handle the nullptr.
        }
    }
}

// Define interactability: Explosions should not collide with other Movers (shapes)
// or other Explosions in a way that triggers physics/interaction resolution.
bool Explosion::interactable(PopObject* otherObject) const {
    // Explosions do not participate in collision resolution with any other PopObject in this version.
    return false;
}