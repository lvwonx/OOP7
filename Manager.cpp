#include "Manager.h"
#include "PopObject.h"
#include "Ball.h" 
#include "Triangle.h"
#include "Rectangle.h"
#include "Star.h"
#include "Explosion.h"
#include "Mover.h" 

#include <cmath> 
#include <limits> 
#include <typeinfo> // For typeid()

using namespace System::Diagnostics;
using namespace System::Drawing;

// ... (constructor, destructor, add, remove, drawFrame, scaleSpeed, search, resolveCollision, destroyAll, move, doCommand, count methods remain the same) ...
// Ensure the previous implementations of those methods are kept. I'll only show the changed methods.

Manager::Manager(int frameWidth, int frameHeight) : frameWidth(frameWidth), frameHeight(frameHeight) {
    for (int i = 0; i < MAX_OBJECTS; i++) {
        objects[i] = nullptr;
    }
}

Manager::~Manager() {
    destroyAll();
}

void Manager::add(PopObject* object) {
    for (int i = 0; i < MAX_OBJECTS; i++) {
        if (objects[i] == nullptr) {
            objects[i] = object;
            return;
        }
    }
    delete object;
}

void Manager::remove(PopObject* objectToRemove) {
    for (int i = 0; i < MAX_OBJECTS; i++) {
        if (objects[i] == objectToRemove) {
            delete objects[i];
            objects[i] = nullptr;
            return;
        }
    }
}

void Manager::drawFrame(System::Drawing::Graphics^ graphics) {
    for (int i = 0; i < MAX_OBJECTS; i++) {
        if (objects[i] != nullptr) {
            objects[i]->draw(graphics);
        }
    }
}

void Manager::scaleSpeed(float factor) {
    for (int i = 0; i < MAX_OBJECTS; i++) {
        if (objects[i] != nullptr) {
            objects[i]->scaleSpeed(factor);
        }
    }
}

PopObject* Manager::search(int x, int y) {
    for (int i = MAX_OBJECTS - 1; i >= 0; i--) {
        if (objects[i] != nullptr) {
            if (dynamic_cast<Mover*>(objects[i]) == nullptr || dynamic_cast<Explosion*>(objects[i]) != nullptr) {
                continue;
            }
            float objX = objects[i]->getX();
            float objY = objects[i]->getY();
            int objRadius = objects[i]->getSize();
            float dx_search = (float)x - objX; // Renamed to avoid conflict
            float dy_search = (float)y - objY; // Renamed to avoid conflict
            float distSq = dx_search * dx_search + dy_search * dy_search;

            if (distSq <= (float)(objRadius * objRadius)) {
                return objects[i];
            }
        }
    }
    return nullptr;
}

void Manager::resolveCollision(PopObject* obj1, PopObject* obj2) {
    float x1 = obj1->getX(), y1 = obj1->getY();
    float x2 = obj2->getX(), y2 = obj2->getY();
    float dx1_coll = obj1->getDX(), dy1_coll = obj1->getDY(); // Renamed
    float dx2_coll = obj2->getDX(), dy2_coll = obj2->getDY(); // Renamed
    int r1 = obj1->getSize();
    int r2 = obj2->getSize();

    float deltaX_coll = x2 - x1; // Renamed
    float deltaY_coll = y2 - y1; // Renamed
    float distSq = deltaX_coll * deltaX_coll + deltaY_coll * deltaY_coll;
    float minRadiusSum = (float)r1 + r2;

    if (distSq <= 0.0001f || distSq >= minRadiusSum * minRadiusSum) { // Added small epsilon for distSq <= 0
        return;
    }

    float dist = sqrt(distSq);
    float overlap = 0.5f * (minRadiusSum - dist);

    // Ensure dist is not zero before division
    float displaceX = (dist == 0) ? 1.0f : deltaX_coll / dist; // Avoid division by zero, default to horizontal displacement
    float displaceY = (dist == 0) ? 0.0f : deltaY_coll / dist;


    obj1->setPos(x1 - overlap * displaceX, y1 - overlap * displaceY);
    obj2->setPos(x2 + overlap * displaceX, y2 + overlap * displaceY);

    float normalX = displaceX;
    float normalY = displaceY;
    float tangentX = -normalY;
    float tangentY = normalX;

    float v1n = dx1_coll * normalX + dy1_coll * normalY;
    float v1t = dx1_coll * tangentX + dy1_coll * tangentY;
    float v2n = dx2_coll * normalX + dy2_coll * normalY;
    float v2t = dx2_coll * tangentX + dy2_coll * tangentY;

    float new_v1n = v2n;
    float new_v2n = v1n;

    float new_dx1 = (new_v1n * normalX) + (v1t * tangentX);
    float new_dy1 = (new_v1n * normalY) + (v1t * tangentY);
    float new_dx2 = (new_v2n * normalX) + (v2t * tangentX);
    float new_dy2 = (new_v2n * normalY) + (v2t * tangentY);

    obj1->setSpeed(new_dx1, new_dy1);
    obj2->setSpeed(new_dx2, new_dy2);
}

void __cdecl Manager::destroyAll() {
    for (int i = 0; i < MAX_OBJECTS; i++) {
        if (objects[i] != nullptr) {
            float objX = objects[i]->getX();
            float objY = objects[i]->getY();
            Mover* moverObj = dynamic_cast<Mover*>(objects[i]);
            int frameW = (moverObj != nullptr) ? moverObj->getFrameWidth() : this->frameWidth;
            int frameH = (moverObj != nullptr) ? moverObj->getFrameHeight() : this->frameHeight;

            delete objects[i];
            objects[i] = nullptr;

            Explosion* explosion = new Explosion(frameW, frameH, static_cast<int>(objX), static_cast<int>(objY));
            if (manager != nullptr) manager->add(explosion);
        }
    }
}

void Manager::move() {
    for (int i = 0; i < MAX_OBJECTS; i++) {
        if (objects[i] != nullptr) {
            objects[i]->move();
        }
    }

    for (int i = 0; i < MAX_OBJECTS; i++) {
        if (objects[i] == nullptr) continue;
        for (int j = i + 1; j < MAX_OBJECTS; j++) {
            if (objects[j] == nullptr) continue;
            if (objects[i] == nullptr || objects[j] == nullptr) continue; // Should be redundant due to outer checks

            if (!objects[i]->interactable(objects[j]) || !objects[j]->interactable(objects[i])) {
                continue;
            }

            float x1 = objects[i]->getX(), y1 = objects[i]->getY();
            float x2 = objects[j]->getX(), y2 = objects[j]->getY();
            int r1 = objects[i]->getSize();
            int r2 = objects[j]->getSize();

            float deltaX_coll_move = x1 - x2;
            float deltaY_coll_move = y1 - y2;
            float distSq = deltaX_coll_move * deltaX_coll_move + deltaY_coll_move * deltaY_coll_move;
            float minRadiusSum = (float)r1 + r2;

            if (distSq > 0.0001f && distSq <= minRadiusSum * minRadiusSum) { // Added small epsilon for distSq > 0
                if (objects[i] == nullptr || objects[j] == nullptr) {
                    continue;
                }
                resolveCollision(objects[i], objects[j]);

                PopObject* objI_before_interact = objects[i]; // Store pointers before interaction
                PopObject* objJ_before_interact = objects[j];

                if (objects[i] != nullptr) { // Check if obj[i] wasn't deleted by resolveCollision (it shouldn't)
                    objects[i]->interact(objects[j]);
                }
                // Check if objects[i] or objects[j] were removed by the first interact call
                bool objI_still_exists = false;
                bool objJ_still_exists = false;
                for (int k = 0; k < MAX_OBJECTS; ++k) {
                    if (objects[k] == objI_before_interact) objI_still_exists = true;
                    if (objects[k] == objJ_before_interact) objJ_still_exists = true;
                }

                if (objI_still_exists && objJ_still_exists) { // Check both still exist in the manager array
                    if (objects[j] != nullptr) { // And the direct pointer is still valid (though the loop implies it is)
                        objects[j]->interact(objects[i]);
                    }
                }
            }
        }
    }
}

void Manager::doCommand(int command) {
    for (int i = 0; i < MAX_OBJECTS; i++) {
        if (objects[i] != nullptr) {
            objects[i]->doCommand(command);
        }
    }
}

int Manager::countBalls() {
    int count = 0;
    for (int i = 0; i < MAX_OBJECTS; i++) {
        if (objects[i] != nullptr && dynamic_cast<Ball*>(objects[i]) != nullptr) {
            count++;
        }
    }
    return count;
}

int Manager::countRectangles() {
    int count = 0;
    for (int i = 0; i < MAX_OBJECTS; i++) {
        if (objects[i] != nullptr && dynamic_cast<::Rectangle*>(objects[i]) != nullptr) {
            count++;
        }
    }
    return count;
}

int Manager::countTriangles() {
    int count = 0;
    for (int i = 0; i < MAX_OBJECTS; i++) {
        if (objects[i] != nullptr && dynamic_cast<Triangle*>(objects[i]) != nullptr) {
            count++;
        }
    }
    return count;
}

int Manager::countStars() {
    int count = 0;
    for (int i = 0; i < MAX_OBJECTS; i++) {
        if (objects[i] != nullptr && dynamic_cast<Star*>(objects[i]) != nullptr) {
            count++;
        }
    }
    return count;
}


float Manager::getDistance(PopObject* obj1, PopObject* obj2) const {
    if (obj1 == nullptr || obj2 == nullptr) return std::numeric_limits<float>::max();
    float dx = obj1->getX() - obj2->getX();
    float dy = obj1->getY() - obj2->getY();
    return std::sqrt(dx * dx + dy * dy);
}

PopObject* Manager::nearest(PopObject* popObject) {
    if (popObject == nullptr) return nullptr;
    PopObject* nearestObj = nullptr;
    float minDist = std::numeric_limits<float>::max();

    for (int i = 0; i < MAX_OBJECTS; i++) {
        PopObject* currentObj = objects[i];
        if (currentObj != nullptr && currentObj != popObject) {
            if (dynamic_cast<Explosion*>(currentObj) != nullptr) continue;

            float dist = getDistance(popObject, currentObj);
            if (dist < minDist) {
                minDist = dist;
                nearestObj = currentObj;
            }
        }
    }
    return nearestObj;
}

PopObject* Manager::nearestFriend(PopObject* popObject) {
    if (popObject == nullptr) return nullptr;
    PopObject* nearestObj = nullptr;
    float minDist = std::numeric_limits<float>::max();
    // Corrected: Use typeid for native C++ exact type comparison
    // const std::type_info& popObjectTypeInfo = typeid(*popObject); // Get type_info of the passed object

    for (int i = 0; i < MAX_OBJECTS; i++) {
        PopObject* currentObj = objects[i];
        // Corrected: Use typeid for comparison
        if (currentObj != nullptr && currentObj != popObject && typeid(*currentObj) == typeid(*popObject)) {
            if (dynamic_cast<Explosion*>(currentObj) != nullptr) continue; // Should be redundant if typeid matches a non-Explosion

            float dist = getDistance(popObject, currentObj);
            if (dist < minDist) {
                minDist = dist;
                nearestObj = currentObj;
            }
        }
    }
    return nearestObj;
}

PopObject* Manager::nearestAlien(PopObject* popObject) {
    if (popObject == nullptr) return nullptr;
    PopObject* nearestObj = nullptr;
    float minDist = std::numeric_limits<float>::max();
    // Corrected: Use typeid for native C++ exact type comparison
    // const std::type_info& popObjectTypeInfo = typeid(*popObject);

    for (int i = 0; i < MAX_OBJECTS; i++) {
        PopObject* currentObj = objects[i];
        // Corrected: Use typeid for comparison
        if (currentObj != nullptr && currentObj != popObject && typeid(*currentObj) != typeid(*popObject)) {
            if (dynamic_cast<Explosion*>(currentObj) != nullptr) continue;

            float dist = getDistance(popObject, currentObj);
            if (dist < minDist) {
                minDist = dist;
                nearestObj = currentObj;
            }
        }
    }
    return nearestObj;
}