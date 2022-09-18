#include "BoundedAreaRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"

Vector2 BoundedAreaRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
    //Return a force proportional to the proximity of the boids with the bounds, and opposed to it
    Vector2 force = Vector2::zero(); //zero

    // todo: add here your code code here do make the boid follow the bounded box rule
    // hint: use this->world->engine->window->size() and desiredDistance
    Vector2 size = this->world->engine->window->size();
    float distance = desiredDistance;

    //Find the boundry lines of the box
    float minX = distance;
    float maxX = size.x - distance;
    float minY = distance;
    float maxY = size.y - distance;

    //Get the position of the boid
    Vector2 position = boid->getPosition();
    Vector2 tempForce = Vector2::zero();

    if (position.x <= minX)
    {
        tempForce = Vector2(Vector2::getDistance(position, Vector2(minX, position.y)), 0);
        force += tempForce;
    }
    else if (position.x >= maxX)
    {
        tempForce = Vector2(Vector2::getDistance(position, Vector2(maxX, position.y)), 0);
        force += (tempForce * -1);
    }
    if (position.y <= minY)
    {
        tempForce = Vector2(0,Vector2::getDistance(position, Vector2(position.x, minY)));
        force += tempForce;
    }
    else if (position.y >= maxY)
    {
        tempForce = Vector2(0, Vector2::getDistance(position, Vector2(position.x, maxY)));
        force += (tempForce * -1);
    }
    force = Vector2::normalized(force);
    return force;
}

bool BoundedAreaRule::drawImguiRuleExtra() {
    ImGui::SetCurrentContext(world->engine->imGuiContext);
    auto size = this->world->engine->window->size();
    auto widthWindows = size.x;
    auto heightWindows = size.y;
    bool valueHasChanged = false;

    //We cap the max separation as the third of the min of the width.height
    auto minHeightWidth = std::min(widthWindows, heightWindows);

    if (ImGui::SliderInt("Desired Distance From Borders",
                         &desiredDistance,
                         0.0f,
                         (int)(minHeightWidth/3),
                         "%i")) {
        valueHasChanged = true;
    }

    return valueHasChanged;
}

void BoundedAreaRule::draw(const Boid& boid, SDL_Renderer* renderer) const {
    FlockingRule::draw(boid, renderer);
    auto size = this->world->engine->window->size();
    auto dist = (float)desiredDistance;

    // Draw a rectangle on the map
    Polygon::DrawLine(renderer, Vector2(dist,dist), Vector2(size.x - dist,dist), Vector3::Gray()); // TOP
    Polygon::DrawLine(renderer, Vector2(size.x - dist,dist), Vector2(size.x - dist,size.y - dist), Vector3::Gray()); // RIGHT
    Polygon::DrawLine(renderer, Vector2(size.x - dist,size.y - dist), Vector2(dist,size.y - dist), Vector3::Gray()); // Bottom
    Polygon::DrawLine(renderer, Vector2(dist,size.y - dist), Vector2(dist,dist), Vector3::Gray()); // LEFT
}