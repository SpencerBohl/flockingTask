#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2 CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
    Vector2 cohesionForce;
    Vector2 centerOfMass;
    Vector2 totalPosition;

    // todo: add your code here to make a force towards the center of mass
    // hint: iterate over the neighborhood
    for (int i = 0; i < neighborhood.size(); i++)
    {
        Vector2 temp = neighborhood[i]->getPosition();
        totalPosition += temp;
    }
    centerOfMass = (totalPosition / neighborhood.size());

    return cohesionForce;
}