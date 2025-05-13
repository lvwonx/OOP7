#pragma once

#include "Mover.h"
#include "Manager.h" // For manager->add/remove

// Forward declarations
class Tree;
class Animal;
class Hunter;
class Explosion;

// Define command constants (as suggested in PDF for general use, though Bullet doesn't use them directly)
// These might be better in a global header or within the MainForm's scope if they are UI commands.
// For now, placing them here if Bullet needs to know about game states or commands indirectly.
// However, Bullet primarily reacts to interactions.

class Bullet : public Mover {
private:
    int _ricochetsLeft; // [cite: 78]

public:
    Bullet(int frameWidth, int frameHeight, float startX, float startY, float targetX, float targetY, float hunterWeaponLength, float bulletSpeedModule, int maxRicochets = 2); // [cite: 81, 107]
    virtual ~Bullet() override {}

    virtual void draw(System::Drawing::Graphics^ g) override;
    virtual void move() override; // Handles ricochets and self-destruction [cite: 77, 79, 80]
    virtual void interact(PopObject* otherObject) override; // Handles collisions [cite: 54, 106]
    // interactable will use Mover's default, as bullets should interact with most things (except other bullets if desired, or explosions)
};