#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
	RenderWindow mainScreen(VideoMode(1280, 720), "World of Tanks reloaded");
	Event Event;
	while (mainScreen.isOpen())
	{
		while (mainScreen.pollEvent(Event))
			if (Event.type == Event::EventType::Closed)
				mainScreen.close();
		mainScreen.clear();
		mainScreen.display();
	}
}