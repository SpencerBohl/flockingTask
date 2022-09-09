#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2 CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
    Vector2 cohesionForce;
    Vector2 centerOfMass = Vector2::zero();
    Vector2 totalPosition = Vector2::zero();

    // todo: add your code here to make a force towards the center of mass
    // hint: iterate over the neighborhood
    if (!neighborhood.empty())
    {
        for (int i = 0; i < neighborhood.size(); i++)
        {
            Vector2 temp = neighborhood[i]->getPosition();
            totalPosition += temp;
        }
        centerOfMass = (totalPosition / neighborhood.size());
        cohesionForce = centerOfMass - boid->getPosition();
        cohesionForce = Vector2::normalized(cohesionForce);
    }
    else if (neighborhood.empty())
    {
        cohesionForce = Vector2::zero();
    }
    
    return cohesionForce;
}