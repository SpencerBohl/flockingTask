#include "AlignmentRule.h"
#include "../gameobjects/Boid.h"

Vector2 AlignmentRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
    Vector2 averageVelocity = Vector2::zero();
    Vector2 totalVelocity = Vector2::zero();

    // todo: add your code here to align each boid in a neighborhood
    // hint: iterate over the neighborhood
    if (!neighborhood.empty())
    {
        for (int i = 0; i < neighborhood.size(); i++)
        {
            Vector2 temp = neighborhood[i]->getVelocity();
            totalVelocity += temp;
        }
        averageVelocity = (totalVelocity / neighborhood.size());
    }

    return Vector2::normalized(averageVelocity);
}