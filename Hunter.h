#pragma once

#include "Mover.h"
#include "Manager.h" // For manager access

// Forward declare other types Hunter might interact with or check against
class Ball;
class Triangle;
class Rectangle;
class Star;
class Bullet; // For creating bullets

// Command definitions (as per PDF example[cite: 62], might be better in a global definitions file)
#define CMD_SHOOT 0
#define CMD_START_UP 1
#define CMD_STOP_UP 2
#define CMD_START_RIGHT 3
#define CMD_STOP_RIGHT 4
#define CMD_START_DOWN 5
#define CMD_STOP_DOWN 6
#define CMD_START_LEFT 7
#define CMD_STOP_LEFT 8
// Add CMD_AIM if mouse coordinates are passed via doCommand, or handle aiming in draw/shoot

class Hunter : public Mover {
private:
    // For movement commands
    bool _movingUp, _movingDown, _movingLeft, _movingRight;
    float _moveSpeed; // Base speed for hunter movement

    // For aiming - store last known mouse coordinates if needed for drawing weapon
    float _aimX, _aimY;

public:
    Hunter(int frameWidth, int frameHeight, int x, int y, int size = 25, int color = System::Drawing::Color::Blue.ToArgb());
    virtual ~Hunter() override {}

    virtual void draw(System::Drawing::Graphics^ g) override; // [cite: 109]
    virtual void move() override; // [cite: 110]
    virtual bool interactable(PopObject* otherObject) const override; // [cite: 52]
    virtual void doCommand(int command) override; // [cite: 60, 110] - this method will also handle aim data if passed in command.
    // Alternatively, aim data can be passed as separate parameters.
    // Let's assume for now aim data (mouse coords) are passed if command is CMD_AIM or similar,
    // or fetched globally when shooting. PDF mentions mouse coords for bullet constructor. [cite: 81]

    void setAimPosition(float x, float y); // Helper to update aim direction
};