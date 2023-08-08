#pragma once
#include "Singleton.h"
class Framework : public Singleton<Framework>
{
	friend Singleton<Framework>;
protected:
	Framework() = default;
	virtual ~Framework() override = default;

	sf::RenderWindow window;
	sf::Clock clock;

	int screenWidth = 256;
	int screenHeight = 224;
	std::string title = "Kirby!";

	float gravity = 9.8f;
	float dotPerMeter = 20.0f;
	
	float timeScale = 1.0f;

	sf::Cursor cursor;

	bool isGameExitButton = false;
	
public:
	Framework(int width, int height, const std::string& title);

	virtual void Init(int width, int height, const std::string& title);
	virtual void Release();

	virtual void UpdateComponent(float deltaTime);

	virtual void Update(float deltaTime);
	virtual void Draw();
	virtual void OnGUI();

	virtual void Run();

	void SetCursor(const sf::Uint8* pixels, sf::Vector2u size, sf::Vector2u hotspot);

	sf::Vector2f GetWindowSize();
	sf::RenderWindow& GetWindow();
	void ExitButton(bool exit);

	float GetGravity();
	float GetDPM();

	void SetTimeScale(const float& timeScale) { this->timeScale = timeScale; };
#ifdef _DEBUG
	enum class DebugMode 
	{
		None = 0,
		Collider = 1,
	};
protected:
	DebugMode debugMode = DebugMode::Collider;
public:
	void SetDebugging(DebugMode debugMode) { this->debugMode = debugMode; };
	bool IsDebugging(DebugMode debugMode) { return (int)this->debugMode & (int)debugMode; };
#endif
};

#define FRAMEWORK (Framework::GetInstance()) 