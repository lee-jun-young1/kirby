#include "stdafx.h"
#include "InputManager.h"
#include "Framework.h"
#include "SceneManager.h"
#include "Scene.h"
#include "TextGameObj.h"
#include <sstream>
#include <DataTableManager.h>
#include <ResourceManager.h>

Framework::Framework(int width, int height, const std::string& title)
    :screenWidth(width), screenHeight(height), title(title)
{
}

void Framework::Init(int width, int height, const std::string& title)
{
    window.create(sf::VideoMode(width, height), title);
    window.setSize({ (unsigned int)width * 3, (unsigned int)height * 3});

    DATATABLE_MANAGER.LoadAll();
    Resources.Init();
    SCENE_MANAGER.Init();
}

void Framework::Release()
{
    SCENE_MANAGER.Release();
    DATATABLE_MANAGER.ReleaseAll();
    //cursor->Release();
}

void Framework::UpdateComponent(float deltaTime)
{
    SCENE_MANAGER.UpdateComponent(deltaTime);
    //cursor->Update(deltaTime);
}

void Framework::Update(float deltaTime)
{
    SCENE_MANAGER.Update(deltaTime);
    //cursor->Update(deltaTime);
}

void Framework::Draw()
{
    SCENE_MANAGER.Draw(window);
    //cursor->Draw(window);
}

void Framework::OnGUI()
{
    SCENE_MANAGER.OnGUI(window);
    //cursor->Draw(window);
}


void Framework::Run()
{
    Init(screenWidth, screenHeight, title);

    clock.restart();


    //Cursor
    //sf::Image cursorImg;
    //cursorImg.loadFromFile("graphics/crosshair.png");
    //if (cursor.loadFromPixels(cursorImg.getPixelsPtr(), cursorImg.getSize(), { cursorImg.getSize().x / 2, cursorImg.getSize().y / 2 }))
    //{
    //    window.setMouseCursor(cursor);
    //}


    //FPS Viewer
    TextGameObj fpsViewer("fonts/NanumGothic.ttf", 20, "fpsViewer");
    sf::Font systemFont;
    systemFont.loadFromFile("fonts/NanumGothic.ttf");
    fpsViewer.SetFont(systemFont);
    fpsViewer.SetCharacterSize(10);
    fpsViewer.SetOrigin(Origins::TL);
    fpsViewer.SetPosition(0.0f, 0.0f);
    fpsViewer.SetActive(false);
    fpsViewer.SetFillColor(sf::Color::Green);

    float fpsTime = 0.0f;
    int fpsMin = INT_MAX;
    int fpsMax = INT_MIN;
    int fps = 0;
    float allFpsTime = 0.0f;
    int allFps = 0;

    sf::Vector2i prevWindowPosition;

    while (window.isOpen())
    {
        sf::Time deltaTime = clock.restart();
        float dt = deltaTime.asSeconds();
        if (prevWindowPosition != window.getPosition())
        {
            dt = 0.0f;
        }

        //씬 이동시 등, 과도한 DeltaTime 방지, 물리로 인한 버그 발생
        if (dt > 0.3f)
        {
            continue;
        }


        Input.Update(dt);
        prevWindowPosition = window.getPosition();

        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                SCENE_MANAGER.GetCurrentScene()->Exit();
                window.close();
                break;
            case sf::Event::GainedFocus:
                //window.setMouseCursor(cursor);
                break;
            }

            Input.UpdateEvent(event);
        }

        if (window.isOpen())
        {
            //SystemEvent
#ifdef _DEBUG
            if (Input.GetKeyDown(sf::Keyboard::F1))
            {
                SetDebugging(debugMode == Framework::DebugMode::Collider ? Framework::DebugMode::None : Framework::DebugMode::Collider);
            }
#endif
            if (Input.GetKeyDown(sf::Keyboard::Tilde))
            {
                fpsViewer.SetActive(!fpsViewer.IsActive());
            }
            if (Input.GetKeyDown(sf::Keyboard::F2))
            {
                fpsTime = 0.0f;
                fpsMin = INT_MAX;
                fpsMax = INT_MIN;
                fps = 0;
                allFpsTime = 0.0f;
                allFps = 0;
            }
            if (fpsViewer.IsActive())
            {
                fps++;
                allFps++;
                fpsTime += dt;
                allFpsTime += dt;
                if (fpsTime > 1.0f)
                {
                    fpsMin = min(fps, fpsMin);
                    fpsMax = max(fps, fpsMax);
                    stringstream ss;
                    ss << "Collect Time : " << allFpsTime << "s" << endl;
                    ss << "FPS : " << fps << endl;
                    ss << "AVG : " << allFps / allFpsTime << endl;
                    ss << "MIN : " << fpsMin << endl;
                    ss << "MAX : " << fpsMax << endl;
                    fpsViewer.SetString(ss.str());

                    fps = 0;
                    fpsTime = 0.0f;
                }
            }

            UpdateComponent(dt * timeScale);
            Update(dt * timeScale);

            window.clear();

            Draw();
            OnGUI();
            if (fpsViewer.IsActive())
            {
                fpsViewer.Draw(window);
            }

            window.display();

            if (isGameExitButton == true)
            {
                return;
            }
        }
    }

    Release();
}

void Framework::SetCursor(const Uint8* pixels, Vector2u size, Vector2u hotspot)
{
    if (cursor.loadFromPixels(pixels, size, hotspot))
    {
        window.setMouseCursor(cursor);
    }
}

sf::Vector2f Framework::GetWindowSize()
{
    return Vector2f(screenWidth, screenHeight);
}

sf::RenderWindow& Framework::GetWindow()
{
    return window;
}

void Framework::ExitButton(bool exit)
{
    isGameExitButton = true;
}

float Framework::GetGravity()
{
    return gravity;
}

float Framework::GetDPM()
{
    return dotPerMeter;
}
