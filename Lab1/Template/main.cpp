#include <SFML/Graphics.hpp>
#include "TransformNode.h"

int main(int argc, char* argv) 
{
  sf::RenderWindow window(sf::VideoMode(600, 600), "Purple");
  
  /*Make the shapes*/
  sf::RectangleShape bodyRect(sf::Vector2<float>(8.0f, 50.0f));
  sf::RectangleShape neckRect(sf::Vector2<float>(3.0f, -8.0f));
  sf::CircleShape headCirc(6.5f);

  sf::RectangleShape lowerArmRightRect(sf::Vector2<float>(20.0f, 5.0f));
  sf::RectangleShape upperArmRightRect(sf::Vector2<float>(20.0f, 5.0f));

  sf::RectangleShape lowerArmLeftRect(sf::Vector2<float>(20.0f, 5.0f)); 
  sf::RectangleShape upperArmLeftRect(sf::Vector2<float>(20.0f, 5.0f));

  /*Colour the shapes*/
  bodyRect.setFillColor(sf::Color::Yellow);
  neckRect.setFillColor(sf::Color::Cyan);
  headCirc.setFillColor(sf::Color::White);

  lowerArmRightRect.setFillColor(sf::Color::Blue);
  upperArmRightRect.setFillColor(sf::Color::Red);

  lowerArmLeftRect.setFillColor(sf::Color::Green);
  upperArmLeftRect.setFillColor(sf::Color::Magenta);

  bool keyHeld = false;

  bool growing = true;
  float scaleFactor = 1.001;

  float growthFactor = 1.001f;
  float shrinkFactor = 0.999f;

  /*Setting positions and origins*/
  bodyRect.setOrigin(bodyRect.getLocalBounds().width / 2, bodyRect.getLocalBounds().height);
  bodyRect.setPosition(300, 500);
  bodyRect.setScale(4, 4);
  headCirc.setScale(1.0f, 1.2f);

  /*Vectors*/
  sf::Vector2<float> armRightPosition((bodyRect.getLocalBounds().width), 2.5f);
  sf::Vector2<float> armRightOrigin(0.0f, 2.5f);

  sf::Vector2<float> armLeftPosition(0.0f, 2.5f);
  sf::Vector2<float> armLeftOrigin((upperArmLeftRect.getLocalBounds().width), 2.5f);

  sf::Vector2<float> neckPosition(bodyRect.getLocalBounds().width / 2, 0.0f);
  sf::Vector2<float> neckOrigin(neckRect.getLocalBounds().width / 2, 0.0f);

  sf::Vector2<float> headPosition(neckRect.getLocalBounds().width - headCirc.getLocalBounds().width / 2, -(neckRect.getLocalBounds().height/2 + headCirc.getLocalBounds().height / 2));
  sf::Vector2<float> headOrigin(neckRect.getLocalBounds().width / 2, neckRect.getLocalBounds().height);

  /*Origins*/
  upperArmRightRect.setOrigin(armRightOrigin);
  lowerArmRightRect.setOrigin(armRightOrigin);

  upperArmLeftRect.setOrigin(armLeftOrigin);
  lowerArmLeftRect.setOrigin(armLeftOrigin);

  neckRect.setOrigin(neckOrigin);
  headCirc.setOrigin(headOrigin);

  /*Positions*/
  lowerArmRightRect.setPosition(upperArmRightRect.getLocalBounds().width, 2.5f);
  upperArmRightRect.setPosition(armRightPosition);

  lowerArmLeftRect.setPosition(0.0f, 2.5f);
  upperArmLeftRect.setPosition(armLeftPosition);

  neckRect.setPosition(neckPosition);
  headCirc.setPosition(headPosition);

  /*TransformNode*/
  TransformNode body(&bodyRect);
  TransformNode neck(&neckRect);
  TransformNode head(&headCirc);

  TransformNode upperArmRight(&upperArmRightRect);
  TransformNode lowerArmRight(&lowerArmRightRect);

  TransformNode upperArmLeft(&upperArmLeftRect);
  TransformNode lowerArmLeft(&lowerArmLeftRect);

  /*Add them*/
  upperArmRight.AddChild(&lowerArmRight);
  body.AddChild(&upperArmRight);

  upperArmLeft.AddChild(&lowerArmLeft);
  body.AddChild(&upperArmLeft);

  neck.AddChild(&head);
  body.AddChild(&neck);


  sf::Clock deltaTime;
  while (window.isOpen())
  {
    float elaspedTime = deltaTime.restart().asSeconds();

	sf::Transform transform = bodyRect.getTransform();

    /*triangle.scale(scaleFactor, scaleFactor);
    float currentScale = triangle.getScale().x;
    if (currentScale >= 4.0f) {
      scaleFactor = shrinkFactor;
    }
    else if (currentScale <= 1.0f)
    {
      scaleFactor = growthFactor;
    }*/

    sf::Event sfEvent;
    while (window.pollEvent(sfEvent))
    {
      if (sfEvent.type == sf::Event::Closed)
      {
        window.close();
      }
      else if (sfEvent.type == sf::Event::KeyReleased)
      {
        keyHeld = false;
      }
      else if (sfEvent.type == sf::Event::KeyPressed)
      {
        keyHeld = true;
      }
    }

	if (keyHeld)
	{

		/*Rotate*/
		float angleAmount = 90.0f;
		float totRot = angleAmount * elaspedTime;

		lowerArmRightRect.rotate(totRot);
		upperArmRightRect.rotate(totRot);

		lowerArmLeftRect.rotate(-totRot);
		upperArmLeftRect.rotate(-totRot);

		float rot = bodyRect.getRotation();
		neckRect.rotate(totRot);

		bodyRect.rotate(totRot);
	}


    window.clear(); // draw fullscreen graphic

    /*sf::Transform hierarchy = sf::Transform::Identity;

    window.draw(triangle);
    hierarchy = hierarchy * triangle.getTransform();

    window.draw(lowerArmRightRect, hierarchy); // DRAWING with the triangle's transform.
    hierarchy = hierarchy * lowerArmRightRect.getTransform();

    window.draw(upperArmRightRect, hierarchy); // DRAWING*/

    body.Draw(&window);

    window.display();
  }

  return 0;
}