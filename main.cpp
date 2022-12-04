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

void printArray(std::vector<Rectangle> vect){
    for(int i = 0; i < vect.size(); i++){
        std::cout << vect[i].height << ", ";
    }
    std::cout << std::endl;
}



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

		xOffset += 4;
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

//function to swap the position of two vectors
void swapPos(int bigIdx, int smallIdx, std::vector<Rectangle>& rec_vec, sf::Image& image, sf::RenderWindow &window, sf::Texture texture, sf::Sprite sprite){
	window.clear();

	//Draw in bigger rectangle, at the x position of the smaller rectangle
	for (int x = 0; x < rec_vec[bigIdx].width; x++)
	{
		for (int y = 0; y < rec_vec[bigIdx].height; y++)
		{
			image.setPixel(rec_vec[smallIdx].x_location + x, rec_vec[bigIdx].y_location + y, rec_vec[bigIdx].colour);
		}
	}
	//delete bigger rectangle by setting all of its pixels to black
	for (int x = 0; x < rec_vec[bigIdx].width; x++)
	{
		for (int y = 0; y < rec_vec[bigIdx].height; y++)
		{
			image.setPixel(rec_vec[bigIdx].x_location + x, rec_vec[bigIdx].y_location + y, sf::Color::Black);
		}
	}

	//draws smaller rectangle in postion of the older rectangle
	for (int x = 0; x < rec_vec[smallIdx].width; x++)
	{
		for (int y = 0; y < rec_vec[smallIdx].height; y++)
		{
			image.setPixel(rec_vec[bigIdx].x_location + x, rec_vec[smallIdx].y_location + y, rec_vec[bigIdx].colour);
		}
	}
	Rectangle tempRec;
	int currX;

	//swaps x locations of the two rectangles
	currX = rec_vec[bigIdx].x_location;
	rec_vec[bigIdx].x_location = rec_vec[smallIdx].x_location;
	rec_vec[smallIdx].x_location = currX;
	
	//swaps big and small rectangles' positions in the vector
	tempRec = rec_vec[bigIdx];
	rec_vec[bigIdx] = rec_vec[smallIdx];
	rec_vec[smallIdx] = tempRec;

	//updates image and draws in on the window
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	window.draw(sprite);
	window.display();
}

//function to draw the current orientation of the vector on screen
void DrawVec(std::vector<Rectangle>& printVector, sf::Image& image, sf::RenderWindow &window, sf::Texture texture, sf::Sprite sprite, int width, int height){
	window.clear();

	for (int i = 0; i < printVector.size(); i++)
	{	
		//fills in the current vector in white
		for (int x = 0; x < printVector[i].width; x++)
		{
			for (int y = 0; y < printVector[i].height; y++)
			{
				image.setPixel(printVector[i].x_location + x, printVector[i].y_location + y, sf::Color::White);
			}
		}
	}

	//updates image and draws in on the window
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	window.draw(sprite);
	window.display();
}

//Sorts the rectangles using the quick sort method
void QuickSort(std::vector<Rectangle>& rec_vec, int start, int end, sf::Image& image, sf::RenderWindow &window, sf::Texture texture, sf::Sprite sprite)
{

    // base case
    if (start >= end)
        return;

    // partitioning the array
    int p = partition(rec_vec, start, end, image, window, texture, sprite);

    // Sorting the left part
    QuickSort(rec_vec, start, p - 1, image, window, texture, sprite);

    // Sorting the right part
    QuickSort(rec_vec, p + 1, end, image, window, texture, sprite);
}

//Sorts the rectangles using the merge sort method
void MergeSort(std::vector<Rectangle>& rec_vec, sf::Image& image, sf::RenderWindow &window, sf::Texture texture, sf::Sprite sprite, int width, int height){
    if(rec_vec.size() < 2){
        return;
    }
	//get mid point and segment vector into left and right vector
    int mid = rec_vec.size()/2;

    std::vector<Rectangle> left;
    for(int i = 0; i < mid; i++){
        left.push_back(rec_vec[i]);
    }


    std::vector<Rectangle> right;
    for(int i = mid; i < rec_vec.size(); i++){
        right.push_back(rec_vec[i]);
    }


	//recursively call function on segmented vectors
    MergeSort(left, image, window, texture, sprite, width, height);
    MergeSort(right, image, window, texture, sprite, width, height);

    //combine vectors
    int leftIdx = 0, rightIdx = 0, currIdx = 0;
    while(leftIdx < left.size() && rightIdx < right.size()){
		if(left[leftIdx].height < right[rightIdx].height){
			Blackout(left, image, leftIdx);
			//change the original vector at the current index with the left vector at the left index
			left[leftIdx].x_location = rec_vec[currIdx].x_location;
			rec_vec[currIdx] = left[leftIdx];
            currIdx++;
            leftIdx++;
        }else{
			Blackout(right, image, rightIdx);
			//change the original vector at the current index with the right vector at the right index
			right[rightIdx].x_location = rec_vec[currIdx].x_location;
			rec_vec[currIdx] = right[rightIdx];
            currIdx++;
            rightIdx++;
        }
    }
	

    //only one will run to fill in the segmented vector that was not exhausted 
    while(leftIdx < left.size()){
		Blackout(left, image, leftIdx);
		left[leftIdx].x_location = rec_vec[currIdx].x_location;
		rec_vec[currIdx] = left[leftIdx];
        currIdx++;
        leftIdx++;
    }
    while(rightIdx < right.size()){
		Blackout(right, image, rightIdx);
		right[rightIdx].x_location = rec_vec[currIdx].x_location;
		rec_vec[currIdx] = right[rightIdx];
        currIdx++;
        rightIdx++;
    }

	//drawn multiple times to visulaize easier
	DrawVec(rec_vec, image, window, texture, sprite, width, height);
}

//Sorts the rectangles using the insertionsort method  (Selection sort appears extremly fast since only a max of N swaps need to occur unlike in insertion sort and in bubble sort)
void SelectionSort(std::vector<Rectangle>& rec_vec, sf::Image& image, sf::RenderWindow &window, sf::Texture texture, sf::Sprite sprite)
{
    int i, j, min_idx;
 
    //go through each element of the subarray
    for (int i = 0; i < rec_vec.size()-1; i++)
    {
		
		//find minimum element
        min_idx = i;
        for(j = i+1; j < rec_vec.size(); j++){

			//slow down rate due to swapping
			for (int x = 0; x < rec_vec[j].width; x++)
			{
				for (int y = 0; y < rec_vec[j].height; y++)
				{
					image.setPixel(rec_vec[j].x_location + x, rec_vec[j].y_location + y, sf::Color::White);
				}
			}
			//updates image and draws in on the window
			texture.loadFromImage(image);
			sprite.setTexture(texture);
			window.draw(sprite);
			window.display();

			if (rec_vec[j].height < rec_vec[min_idx].height){
				min_idx = j;
			}
		}
		
        //swap minimum element with current boundary
        if(min_idx != i){
			swapPos(i, min_idx, rec_vec, image, window, texture, sprite);
		}
    }
}

//Sorts the rectangles using the insertionsort method
void InsertionSort(std::vector<Rectangle>& rec_vec, sf::Image& image, sf::RenderWindow &window, sf::Texture texture, sf::Sprite sprite)
{
    Rectangle tempRec;
	int j;
	
	//for loop through each element
    for (int i = 1; i < rec_vec.size(); i++)
    {
        tempRec = rec_vec[i];
        j = i - 1;

        while (j >= 0 && rec_vec[j].height > tempRec.height)
        {
            //rec_vec[j + 1] = rec_vec[j];
			swapPos(j, j+1, rec_vec, image, window, texture, sprite);
            j--;
        }
    }
}


//Sorts the rectangles using the bubblesort method
void BubbleSort(std::vector<Rectangle>& rec_vec, sf::Image& image, sf::RenderWindow &window, sf::Texture texture, sf::Sprite sprite)
{
	for(int i = 0; i < rec_vec.size(); i++)
	{
		for (int j = 0; j < rec_vec.size() -1; j++)
		{   
            //if value to the right is less than the current postion value
			if(rec_vec[j].height > rec_vec[j + 1].height)
			{
				swapPos(j, j+1, rec_vec, image, window, texture, sprite);
			}
		}
	}
}

int main()
{
	srand(time(NULL));

    //opens window and creates events for each sort algorithm
	int width = 1000;
	int height = 800;
	bool bPress = false;
	bool mPress = false;
	bool iPress = false;
	bool sPress = false;
	bool qPress = false;

	sf::RenderWindow window(sf::VideoMode(width, height), "Sort");
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
	// check for mergesort
	//std::vector<Rectangle> temp = rectangle_vec;
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
                //checks if letter has been pressed
				if(ev.key.code == sf::Keyboard::B){
					bPress = true;
					//std::cout << "True" << std::endl;
				}
				if(ev.key.code == sf::Keyboard::M){
					mPress = true;
					//std::cout << "True" << std::endl;
				}
				if(ev.key.code == sf::Keyboard::I){
					iPress = true;
					//std::cout << "True" << std::endl;
				}
				if(ev.key.code == sf::Keyboard::S){
					sPress = true;
					//std::cout << "True" << std::endl;
				}
				if(ev.key.code == sf::Keyboard::Q){
					qPress = true;
					//std::cout << "True" << std::endl;
				}
			}
			// 	// if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){
			// 	// 	shape.move(0.0f, -0.1f);
			// 	// }
			// 	// if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
			// 	// 	shape.move(0.0f, 0.1f);
			// 	// }
			// }
		}
		

        //updates image
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		window.clear();
        //runs sort algorithm if valid letter has been pressed
		if(bPress)
		{
			BubbleSort(rectangle_vec, image, window, texture, sprite);
			bPress = false;
		}
		if(mPress)
		{
			MergeSort(rectangle_vec, image, window, texture, sprite, width, height);
			StartImage(image, rectangle_vec);
			texture.loadFromImage(image);
			sprite.setTexture(texture);

			mPress = false;
		}
		if(iPress)
		{
			InsertionSort(rectangle_vec, image, window, texture, sprite);
			iPress = false;
		}
		if(sPress)
		{
			SelectionSort(rectangle_vec, image, window, texture, sprite);
			sPress = false;
		}
        //draws updated image to display
		window.draw(sprite);
		window.display();
	}

	return 0;
}
