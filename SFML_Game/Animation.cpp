#include "Animation.h"

Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
{
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.0f;
	currentImage.x = 0;

	uvRect.width = int(texture->getSize().x / float(imageCount.x));
	uvRect.height = int(texture->getSize().y / float(imageCount.y));
}

Animation::~Animation()
{

}

void Animation::Update(int row, float deltaTime, bool faceTop, bool faceLeft, bool statusWalk, bool checkGameStart)
{
	currentImage.y = row;
	totalTime += deltaTime;
	if (checkGameStart == true)
	{
		if (statusWalk)
		{
			if (totalTime >= switchTime)
			{
				totalTime -= switchTime;
				currentImage.x++;

				if (currentImage.x >= imageCount.x)
				{
					currentImage.x = 0;
				}
				
			}


			uvRect.top = currentImage.y * uvRect.height;

			if (faceTop)
			{
				if (currentImage.x == 1)
				{
					currentImage.x += 1;
				}
				uvRect.left = currentImage.x * abs(uvRect.width);
				uvRect.width = abs(uvRect.width);
			}
			else if (faceLeft)
			{
				currentImage.y = 2;
				if (currentImage.x == 1)
				{
					currentImage.x += 1;
				}
				
				uvRect.top = currentImage.y * uvRect.height;

				//faceTop == true
				uvRect.left = currentImage.x * abs(uvRect.width);
				uvRect.width = abs(uvRect.width);
			}
			else
			{
				if (currentImage.x == 1)
				{
					currentImage.x += 1;
				}
				uvRect.left = (currentImage.x + 1) * abs(uvRect.width);
				uvRect.width = -abs(uvRect.width);
			}
		}
		
		else
		{
			if (faceTop)
			{
				currentImage.x = 1;
				currentImage.y = 1;
				uvRect.top = currentImage.y * uvRect.height;

				//faceTop == true
				uvRect.left = currentImage.x * abs(uvRect.width);
				uvRect.width = abs(uvRect.width);

			}
			

			else if (faceLeft)
			{
				currentImage.x = 1;
				currentImage.y = 2;
				uvRect.top = currentImage.y * uvRect.height;

				//faceTop == true
				uvRect.left = currentImage.x * abs(uvRect.width);
				uvRect.width = abs(uvRect.width);
			}
			
			else 
			{
				currentImage.x = 1;
				if (currentImage.y == 0)
					currentImage.y = 0;
				else
					currentImage.y = 2;
				
				uvRect.top = currentImage.y * uvRect.height;

				//faceTop == false
				uvRect.left = (currentImage.x + 1) * abs(uvRect.width);
				uvRect.width = -abs(uvRect.width);

			}
		}
		
		
	}
	else
	{
		currentImage.x = 1;
		currentImage.y = 0;
		uvRect.top = currentImage.y * uvRect.height;

		if (faceTop)
		{
			uvRect.left = currentImage.x * abs(uvRect.width);
			uvRect.width = abs(uvRect.width);
		}
		else
		{
			uvRect.left = (currentImage.x + 1) * abs(uvRect.width);
			uvRect.width = -abs(uvRect.width);
		}
	}
}