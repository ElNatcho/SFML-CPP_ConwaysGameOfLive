#include<SFML\Graphics.hpp>
#include<iostream>
#include<memory>
#include"CellMgr.hpp"

int main()
{
	//Vars//////////////////////////////////////////////////////////////////
	int *height = new int; ///Height of the window bzw matrix
	int	*width  = new int; ///Width of the window bzw matrix
	int *faktor = new int; ///Faktor of the scale

	float *delay = new float;

	bool *bRun = new bool;

	std::cout << ">Enter matrix width : ";
	std::cin >> *width;
	std::cout << ">Enter matrix height: ";
	std::cin >> *height;
	std::cout << ">Enter scale faktor : ";
	std::cin >> *faktor;

	//Objekts///////////////////////////////////////////////////////////////
	sf::RenderWindow *pWindow = new sf::RenderWindow(sf::VideoMode((*width * *faktor), (*height * *faktor)), "ConwaysGameOfLive"); ///Window																																   //sf::RenderWindow *pWindow = new sf::RenderWindow(sf::VideoMode(500, 500), "LEEEEEL");
	sf::Event *pEvent = new sf::Event(); ///Event
	sf::FloatRect *pFloatRect = new sf::FloatRect(0, 0, *faktor, *faktor);

	*delay = 1.f;
	*bRun  = true;

	CellMgr *cellMgr = new CellMgr(width, height, faktor); ///Cell Manager
	cellMgr->setDelay(delay);

	//Start the window Loop/////////////////////////////////////////////////
	while (pWindow->isOpen()) { ///Check if the window is open
		while (pWindow->pollEvent(*pEvent)) { ///Check if there any events
			if (pEvent->type == sf::Event::Closed) { ///Check if the close event is called
				pWindow->close(); ///Close the window
			}
			if (pEvent->type == sf::Event::MouseButtonPressed) {
				if (pEvent->mouseButton.button == 0) {
					for (int y = 0; y < *height; y++) {
						for (int x = 0; x < *width; x++) {
							pFloatRect->left = x * *faktor;
							pFloatRect->top  = y * *faktor;
							if (pFloatRect->contains(sf::Mouse::getPosition(*pWindow).x,
													 sf::Mouse::getPosition(*pWindow).y)) {
								std::cout << ">Set pixel at x = " << x << " y = " << y << std::endl;
								cellMgr->setPixel(&sf::Vector2i(x, y));
							}
						}
					}
				}
			}
			if (pEvent->type == sf::Event::KeyReleased) {
				switch (pEvent->key.code)
				{
				case sf::Keyboard::Up:
					std::cout << ">Delay_time + 0.05f" << std::endl;
					*delay += 0.05f;
					cellMgr->setDelay(delay);
					break;

				case sf::Keyboard::Down:
					std::cout << ">Delay_time - 0.05f" << std::endl;
					*delay -= 0.05f;
					cellMgr->setDelay(delay);
					break;

				case sf::Keyboard::Space:
					if (*bRun) {
						std::cout << ">Game stopped" << std::endl;
						*bRun = false;
					}else {
						std::cout << ">Game continue" << std::endl;
						*bRun = true;
					}
					break;

				case sf::Keyboard::Escape:
					pWindow->close();
					break;

				case sf::Keyboard::C:
					cellMgr->Clear();
					break;

				default:
					break;
				}
			}
		}
		pWindow->clear(); ///Clear the window

		if (*bRun) {
			cellMgr->Update(); ///Update the cell matrix
		}
		pWindow->draw(*cellMgr->returnCellMatrix()); ///Draw the cell matrix

		pWindow->display(); ///Display the sprites
	}

	delete pWindow;
	delete pEvent;
	delete cellMgr;

	return 0;
}