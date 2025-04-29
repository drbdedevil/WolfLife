#include "Application.h"

#include "World.h"
#include "Agents/Vehicle.h"
#include "Agents/Wolf.h"

Application::Application()
{

}

Application::~Application()
{

}

void Application::run()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1280, 720, "WolfLife");
    SetTargetFPS(60);

    World* world = new World(200, 4);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        if (!world->isGameOver())
        {
            if (IsKeyPressed(KEY_ENTER))
            {
                world->gameOver();
            }

            world->doForce();
            world->update(GetFrameTime());

            world->draw();

            // handle input
            // Vector2 mousePos = GetMousePosition();
            // DrawCircle(mousePos.x, mousePos.y, 10, RED);

            DrawFPS(10, 10);
            DrawText(TextFormat("Health Points: %i", world->getWolfHealth()), 1280 - 200, 10, 24, WHITE);
            DrawText(TextFormat("Count Sheep: %i", world->getCountOfSheep()), 1280 - 210, 30, 24, WHITE);
        }
        else
        {
            if (IsKeyPressed(KEY_ENTER))
            {
                world->reset();
            }

            ClearBackground(BLACK);
            DrawTextCentered("GAME OVER", 40, RED, 1280, 720);
            DrawTextCentered(TextFormat("Health Points: %i", world->getWolfHealth()), 30, BLUE, 1280, 800);
            DrawTextCentered(TextFormat("Count Sheep: %i", world->getCountOfSheep()), 30, BLUE, 1280, 880);
        }
        

        EndDrawing();
    }

    delete world;
    CloseWindow();
}

void Application::DrawTextCentered(const std::string& text, int fontSize, const Color& color, int screenWidth, int screenHeight, int padding)
{
    const int maxWidth = screenWidth - padding * 2;
    std::vector<std::string> lines;
    std::string currentLine;
    std::string word;

    const auto exceedsMaxWidth = [&](const std::string& line, const std::string& newWord)
        { return !line.empty() && MeasureText((line + newWord).c_str(), fontSize) > maxWidth; };

    // Split by spaces to wrap words
    for (char letter : text)
    {
        if (letter == ' ')
        {
            if (exceedsMaxWidth(currentLine, word))
            {
                lines.push_back(currentLine);
                currentLine = word + " ";
                word.clear();
            }
            else
            {
                currentLine += word + " ";
                word.clear();
            }
        }
        else
        {
            word += letter;
        }
    }

    // Handle the last word and line
    if (!word.empty())
    {
        if (exceedsMaxWidth(currentLine, word))
        {
            lines.push_back(currentLine);
            lines.push_back(word);
        }
        else
        {
            lines.push_back(currentLine + word);
        }
    }
    else if (!currentLine.empty())
    {
        lines.push_back(currentLine);
    }

    const int lineSpacing = fontSize / 4;
    const int totalHeight = lines.size() * fontSize + (lines.size() - 1) * lineSpacing;
    const int startY = (screenHeight - totalHeight) / 2;

    // Draw each line
    for (size_t i = 0; i < lines.size(); i++)
    {
        const int textWidth = MeasureText(lines[i].c_str(), fontSize);
        const int posX = (screenWidth - textWidth) / 2;
        const int posY = startY + i * (fontSize + lineSpacing);
        DrawText(lines[i].c_str(), posX, posY, fontSize, color);
    }
}