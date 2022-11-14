#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <ctime>

//defines rectangle to hold coordinate information along with height and width 
struct Rectangle
{
	int height = 0;
	int width = 3;

	int x_location = 0;
	int y_location = 0;

	sf::Color colour = sf::Color::White;
};

int main()
{
	srand(time(NULL));

    //opens window and creates event
	int width = 1000;
	int height = 800;
	bool spaceIspressed = false;

	sf::RenderWindow window(sf::VideoMode(width, height), "Bubble Sort");
	sf::Event ev;

    //creates an image to be diplayed on the window
	sf::Image image;
	image.create(width, height);

    //makes background of image black
	for (int i = 0; i < width; i++)
	{
		for(int j = 0; j < height; j++)
		{
			image.setPixel(i, j, sf::Color::Black);
		}
	}


	sf::Texture texture;
	texture.loadFromImage(image);
	sf::Sprite sprite;
	sprite.setTexture(texture);

    //vector to hold all rectangles
	Rectangle rect;
	std::vector<Rectangle> rectangle_vec;

	return 0;
}
