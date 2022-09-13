#include "SeparationRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"

Vector2 SeparationRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
    //Try to avoid boids too close
    Vector2 separatingForce = Vector2::zero();
    Vector2 totalPosition = Vector2::zero();
    Vector2 centerOfMass = Vector2::zero();

    float desiredDistance = desiredMinimalDistance;

    // todo: implement a force that if neighbor(s) enter the radius, moves the boid away from it/them
    //If the neighborhood is not empty check positions
    if (!neighborhood.empty()) 
    {
        //Get position of current boid for later and start counting the close flockmates
        Vector2 position = boid->transform.position;
        int countCloseFlockmates = 0;
        //Iterate through the neighborhood
        for (int i = 0; i < neighborhood.size(); i++)
        {
            //Store current neighbor position in a temp vector
            Vector2 temp = neighborhood[i]->getPosition();
            //Get the distance from the neighbor and check the magnitude
            //If it is closer than our desired distance count it as a close flockmate and add temp to the total position
            if (Vector2::getDistance(position,temp) <= desiredMinimalDistance)
            {
               countCloseFlockmates++;
               totalPosition += temp;
            }
        }
        //If we have close flockmates calculate the Center of Mass and the seperating force
        if (countCloseFlockmates != 0)
        {
            centerOfMass = (totalPosition / countCloseFlockmates);
            separatingForce = centerOfMass - position;
            separatingForce = Vector2::normalized(separatingForce);
            separatingForce *= -1.0f;
        }
    }//If the neighborhood is empty make sure that the separating force is zero
    else if (neighborhood.empty())
    {
        separatingForce = Vector2::zero();
    }
 
    return separatingForce;
}

bool SeparationRule::drawImguiRuleExtra() {
    ImGui::SetCurrentContext(world->engine->imGuiContext);
    bool valusHasChanged = false;

    if (ImGui::DragFloat("Desired Separation", &desiredMinimalDistance, 0.05f)) {
        valusHasChanged = true;
    }

    return valusHasChanged;
}
