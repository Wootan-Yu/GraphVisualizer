#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#pragma region imgui
#include "imgui.h"
#include "imgui-SFML.h"
#include "imguiThemes.h"
#pragma endregion


int main()
{
	sf::RenderWindow window(sf::VideoMode(1300, 750), "Graph Visualizer");
	window.setFramerateLimit(60);
#pragma region imgui
	ImGui::SFML::Init(window);
	//you can use whatever imgui theme you like!
	//ImGui::StyleColorsDark();				
	//imguiThemes::yellow();
	//imguiThemes::gray();
	imguiThemes::green();
	//imguiThemes::red();
	//imguiThemes::gray();
	//imguiThemes::embraceTheDarkness();

	ImGuiIO &io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io.FontGlobalScale = 2.f;
	ImGuiStyle &style = ImGui::GetStyle();
	style.Colors[ImGuiCol_WindowBg].w = 0.5f;
	//style.Colors[ImGuiCol_DockingEmptyBg].w = 0.f;
#pragma endregion

	sf::VertexArray sinLine(sf::LinesStrip, window.getSize().x);
	sf::VertexArray cosLine(sf::LinesStrip, window.getSize().x);
	sf::VertexArray tanLine(sf::LinesStrip, window.getSize().x);
	/*for (size_t i = 0; i < window.getSize().x; i++)
	{
		float x = i * 1.f;
		float y = (float)(window.getSize().y / 2) + 100.f * sin(i * 0.02f);
		line[i].position = sf::Vector2f(x, y);
		line[i].color = sf::Color::White;
	}*/

	float amplitude = 100;
	float frequency = 0.01f;

	sf::Clock clock;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			
		#pragma region imgui
			ImGui::SFML::ProcessEvent(window, event);
		#pragma endregion


			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::Resized)
			{
				// Adjust the viewport when the window is resized
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				window.setView(sf::View(visibleArea));
			}
		}

		//calculate the delta time
		sf::Time deltaTime = clock.restart();
		float deltaTimeSeconds = deltaTime.asSeconds();

		//make sure delta time stays within normal bounds, like between one FPS and zero FPS
		deltaTimeSeconds = std::min(deltaTimeSeconds, 1.f);
		deltaTimeSeconds = std::max(deltaTimeSeconds, 0.f);

	#pragma region imgui
		ImGui::SFML::Update(window, deltaTime);

		ImGui::PushStyleColor(ImGuiCol_WindowBg, {});
		ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, {});
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
		ImGui::PopStyleColor(2);
	#pragma endregion


		ImGui::Begin("Controls");
		ImGui::SliderFloat("Amplitude", &amplitude, 0.f, 150.f, "%.0f");
		ImGui::SliderFloat("Frequency", &frequency, 0.01f, 0.1f, "%.2f");
		ImGui::End();

		for (size_t i = 0; i < window.getSize().x; i++)
		{
			float x = i;
			float siny = (float)(window.getSize().y / 2) + amplitude * -sin(i * frequency);
			sinLine[i].color = sf::Color::Green;
			sinLine[i].position = sf::Vector2f(x, siny);

			float cosy = (float)(window.getSize().y / 2) + amplitude * -cos(i * frequency);
			cosLine[i].color = sf::Color::Red;
			cosLine[i].position = sf::Vector2f(x, cosy);

			float tany = (float)(window.getSize().y / 2) + amplitude * -tan(i * frequency);
			tanLine[i].color = sf::Color::Yellow;
			tanLine[i].position = sf::Vector2f(x, tany);
		}



		//game code....
		window.clear();
		
		window.draw(tanLine);
		window.draw(sinLine);
		window.draw(cosLine);
		

	#pragma region imgui
		ImGui::SFML::Render(window);
	#pragma endregion

		window.display();
	}

#pragma region imgui
	ImGui::SFML::Shutdown();
#pragma endregion

	return 0;
}