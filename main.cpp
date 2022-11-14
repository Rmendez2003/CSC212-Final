#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
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

//function to fill vector with enough rectangles to fill up the image
void FillVector(Rectangle rec, std::vector<Rectangle> &rec_vec, sf::Image Image)
{
	int xOffset = 0;
	while (xOffset < Image.getSize().x)
	{
        //assign random height for rectangle from 5 to 50 from the top of the window
		rec.height = rand() % (Image.getSize().y - 50) + 5;

        //assign x offset
		rec.x_location = xOffset;
		rec.y_location = Image.getSize().y - rec.height;

		rec_vec.push_back(rec);

		xOffset += 5;
	}
}

//Creates the start image by coloring all vectors white in their randomized locations
void StartImage(sf::Image &image, std::vector<Rectangle> rec_vec)
{

	for (int i = 0; i < rec_vec.size(); i++)
	{
		for (int x = 0; x < rec_vec[i].width; x++)
		{
			for (int y = 0; y < rec_vec[i].height; y++)
			{
				image.setPixel(rec_vec[i].x_location + x, rec_vec[i].y_location + y, rec_vec[i].colour);
			}
		}
	}
	
}



//Sorts the rectangles using the bubblesort method
void BubbleSort(std::vector<Rectangle>& rec_vec, sf::Image& image, sf::RenderWindow &window, sf::Texture texture, sf::Sprite sprite)
{
	Rectangle tempRec;
	int currX;

	for(int i =0; i < rec_vec.size(); i++)
	{
		for (int j = 0; j < rec_vec.size() -1; j++)
		{   
            //if value to the right is less than the current postion value
			if(rec_vec[j].height > rec_vec[j + 1].height)
			{
				window.clear();

				//Draw in bigger rectangle, at the x position of the smaller rectangle
				for (int x = 0; x < rec_vec[j].width; x++)
				{
					for (int y = 0; y < rec_vec[j].height; y++)
					{
						image.setPixel(rec_vec[j + 1].x_location + x, rec_vec[j].y_location + y, rec_vec[j].colour);
					}
				}
				//delete bigger rectangle by setting all of its pixels to black
				for (int x = 0; x < rec_vec[j].width; x++)
				{
					for (int y = 0; y < rec_vec[j].height; y++)
					{
						image.setPixel(rec_vec[j].x_location + x, rec_vec[j].y_location + y, sf::Color::Black);
					}
				}
				//draws smaller rectangle in postion of the older rectangle
				for (int x = 0; x < rec_vec[j + 1].width; x++)
				{
					for (int y = 0; y < rec_vec[j + 1].height; y++)
					{
						image.setPixel(rec_vec[j].x_location + x, rec_vec[j + 1].y_location + y, rec_vec[j].colour);
					}
				}

                //swaps x locations of the two rectangles
				currX = rec_vec[j].x_location;
				rec_vec[j].x_location = rec_vec[j + 1].x_location;
				rec_vec[j + 1].x_location = currX;
				
                //swaps big and small rectangles' positions in the vector
				tempRec = rec_vec[j];
				rec_vec[j] = rec_vec[j + 1];
				rec_vec[j + 1] = tempRec;

                //updates image and draws in on the window
				texture.loadFromImage(image);
				sprite.setTexture(texture);
				window.draw(sprite);
				window.display();
			}
		}
	}
}

int main()
{
    
	srand(time(NULL));

    //opens window and creates event
	int width = 1000;
	int height = 800;
	bool spaceIspressed = false;

	sf::RenderWindow window(sf::VideoMode(width, height), "Merge Sort");
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

    //fills vector with rectangles of random sizes and writes the vectors onto an image
	FillVector(rect, rectangle_vec, image);
	StartImage(image, rectangle_vec);
	texture.loadFromImage(image);
	sprite.setTexture(texture);


	while (window.isOpen())
	{
		while(window.pollEvent(ev))
		{   
            //closes window
			if (ev.type == sf::Event::Closed)
			{
				window.close();
			}
			if (ev.type == sf::Event::KeyReleased)
			{   
                //checks if spacebar has been pressed
				if(ev.key.code == sf::Keyboard::Space)
				{
					spaceIspressed = true;
				}
			}
		}

        //updates image
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		window.clear();
        
        //runs sort algorithm if spacebar has been pressed
		if(spaceIspressed)
		{
			BubbleSort(rectangle_vec, image, window, texture, sprite);
			spaceIspressed = false;
		}

        //draws updated image to display
		window.draw(sprite);
		window.display();
	}

	return 0;
}
