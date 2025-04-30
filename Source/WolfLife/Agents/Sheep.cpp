#include "Sheep.h"

#include "raylib.h"
#include "rlgl.h"
#include <algorithm>

#include "../ResourceManager.h"
#include "../TextureObject.h"

#include "Wolf.h"
#include "../Components/Eyeshot.h"
#include "../Components/Collision.h"

Sheep::Sheep(int x, int y) : AIVehicle(x, y)
{
    size = 1.5f;

    m_startPos = Vector2(x, y);

    m_collision.reset(new Collision(this, 2.f));
    m_eyeshot.reset(new Eyeshot(this, 50.f, 10.f, 100.f));

    velocity = Vector2f(randomFloat(-10, 10), randomFloat(-10, 10));

    maxSpeed = 0.5f;
    maxForce = 4.2f;
}

void Sheep::update(float DeltaSeconds)
{
    AIVehicle::update(DeltaSeconds);
}

void Sheep::draw()
{
    float angle = atan2f(velocity.y, velocity.x) * RAD2DEG + 90.0f;

    if (ResourceManager::getInstance().getSheepTexture()->isLoad())
    {
        TextureObject* textureObject = ResourceManager::getInstance().getSheepTexture();
        Texture2D texture = *textureObject->getTexture();
        int frameWidth = textureObject->getFrameWidth();
        int frameHeight = textureObject->getFrameHeight();

        Rectangle sourceRec = {
            frameWidth * textureObject->getCurrentFrame(),
            0,
            (float)frameWidth,
            (float)frameHeight
        };

        // Указываем размер и позицию в центре объекта
        Rectangle destRec = {
            position.x,
            position.y,
            frameWidth * size,
            frameHeight * size
        };

        // Центр вращения — центр текстуры
        Vector2 origin = {
            frameWidth * size / 2.0f,
            frameHeight * size / 2.0f
        };

        // Теперь нарисуем
        DrawTexturePro(texture, sourceRec, destRec, origin, angle, WHITE);

        return;
    }

    DrawLineEx(Vector2(position.x, position.y), Vector2(position.x + velocity.x * 50.f, position.y + velocity.y * 50.f), 2.f, WHITE);

    angle = atan2f(velocity.y, velocity.x);

    rlPushMatrix();
    rlTranslatef(position.x, position.y, 0.0f);
    rlRotatef(angle * RAD2DEG, 0.0f, 0.0f, 1.0f);

    // m_eyeshot->draw();

    DrawCircle(0, 0, size, GRAY);
    
    rlPopMatrix();
}

void Sheep::execute()
{
    if (m_sheepBehavior == ESB_Pasture)
    {
        bound();
    }
    else if (m_sheepBehavior == ESB_ReturnToPasture)
    {
        arrive({ m_startPos.x, m_startPos.y });

        if (CheckCollisionPointCircle({ position.x, position.y }, m_startPos, 20.f))
        {
            sheepShouldPasture();
        }
    }
    else if (m_sheepBehavior == ESB_RunningAway)
    {
        fleeingBoundIntelligent({ m_wolf->position.x, m_wolf->position.y });
    }
}

void Sheep::setWolf(std::shared_ptr<Wolf>& wolf)
{
    m_wolf = wolf.get();
}

void Sheep::setSheepBehavior(ESheepBehavior newBehavior)
{
    m_sheepBehavior = newBehavior;
}

void Sheep::sheepShouldPasture()
{
    m_sheepBehavior = ESB_Pasture;

    maxSpeed = 0.5f;
    maxForce = 4.2f;
}

void Sheep::sheepShouldReturnToPasture()
{
    m_sheepBehavior = ESB_ReturnToPasture;

    maxSpeed = 2.2f;
    maxForce = 2.2f;
}

void Sheep::sheepShouldRunningAway()
{
    m_sheepBehavior = ESB_RunningAway;

    maxSpeed = 1.2f;
    maxForce = 10.2f;
}

void Sheep::updateTextureFrame(float DeltaSeconds)
{
    updateTextureFrameInner(DeltaSeconds, ResourceManager::getInstance().getSheepTexture(), 0.f, 0.3f);
}