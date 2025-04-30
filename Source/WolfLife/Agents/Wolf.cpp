#include "Wolf.h"

#include "Sheep.h"
#include "raylib.h"
#include "rlgl.h"

#include "../ResourceManager.h"
#include "../TextureObject.h"

#include "../Components/Collision.h"

Wolf::Wolf(int x, int y, int8_t health) : Vehicle(x, y)
{
    size = 2.5f;

    m_collision.reset(new Collision(this, 5.f));

	m_health = health;
}

void Wolf::update(float DeltaSeconds)
{
    Vehicle::update(DeltaSeconds);
}

void Wolf::draw()
{
    float angle = atan2f(velocity.y, velocity.x) * RAD2DEG + 90.0f;

    if (ResourceManager::getInstance().getWolfTexture()->isLoad())
    {
        TextureObject* textureObject = ResourceManager::getInstance().getWolfTexture();
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

    // DrawLineEx(Vector2(position.x, position.y), GetMousePosition(), 2.f, WHITE);

    angle = atan2f(velocity.y, velocity.x);

    rlPushMatrix();
    rlTranslatef(position.x, position.y, 0.0f);
    rlRotatef(angle * RAD2DEG, 0.0f, 0.0f, 1.0f);

    DrawTriangle(
        { size * 2, 0 },
        { -size * 2, -size },
        { -size * 2, size },
        GREEN
    );

    rlPopMatrix();
}

int8_t Wolf::getHealth() const
{
    return m_health;
}

void Wolf::eatSheep(Sheep* sheep)
{
    sheep->die();
}

void Wolf::setVisibility(bool Value)
{
    bIsVisible = Value;
}

bool Wolf::isVisible() const
{
    return bIsVisible;
}

void Wolf::tear()
{
    --m_health;
    if (m_health <= 0)
    {
        m_health = 0;
        bIsAlive = false;
    }
}

void Wolf::updateTextureFrame(float DeltaSeconds)
{
    updateTextureFrameInner(DeltaSeconds, ResourceManager::getInstance().getWolfTexture(), 0.f, 0.35f);
}
