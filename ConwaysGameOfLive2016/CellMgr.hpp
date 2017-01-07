#ifndef CELLMGR_HPP
#define CELLMGR_HPP

//Includes
#include<SFML\Graphics.hpp>
#include<iostream>
#include<memory>
#include<vector>

//Class
class CellMgr{
public:
	CellMgr(int *width, int *height, int *faktor);  ///Konstruktor
	~CellMgr(); ///Destruktor

	//Functions/////////////////////////////////////////////////////
	void Update(); ///Update the matrices
	void Clear(); ///Clear the matrix
	void overWriteMainMatrix(); ///Overwrite the main matrix with the temp matrix
	void overWriteTempMatrix(); ///Overwrite the temp matrix with the main matrix
	void showMapData(); ///Print the map data in the console
	void setDelay(float *delay); ///Set the update time 
	void setPixel(sf::Vector2i *pos, sf::Color *color); ///Set a pixel
	void setPixel(sf::Vector2i *pos); ///Set a pixel
	sf::Sprite *returnCellMatrix(); ///Return a drawable sprite

private:
	//_Objekt members_//////////////////////////////////////////////
	//Functions/////////////////////////////////////////////////////
	int  _testPixel(sf::Vector2i *pos); ///Check the 8 pixels around one cell
	void _InitImage(); ///Overwrite the image with the main matrix

	//Vars//////////////////////////////////////////////////////////
	sf::Image   *_imgCellMatrix; ///Image for the cells
	sf::Texture *_texCellMatrix; ///Texture of the image
	sf::Sprite  *_sprCellMatrix; ///Sprite for the texture

	sf::Time *_tempClock; ///Temp clock for the timer
	sf::Time *_elapsed;   ///Elapsed var for the temp clock
	sf::Clock *_clock;    ///Clock for the elapsed var

	sf::Vector2i *_matrixSize; ///Size of the matrix

	bool _tempChar; ///Temp char for the char vector
	std::vector<bool> _tempVector; ///Temp char vector for the cell matrix and temp cell matrix
	std::vector<std::vector<bool>> _cellMatrix; ///Cell Matrix 
	std::vector<std::vector<bool>> _tempCellMatrix; ///Temp Cell Matrix

	float *_fDelay; ///Update time

	int *_iFaktor;	  ///Faktor for the scale
	int  _iCellCount; ///Number of cells around one cell
	int  _iCount; 

};

#endif