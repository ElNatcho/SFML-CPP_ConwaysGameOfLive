#include"CellMgr.hpp"

CellMgr::CellMgr(int *width, int *height, int *faktor) //Konstruktor/////////
{
	std::cout << ">CellMgr: Konstruktor" << std::endl;
	//Init Pointers//////////////////////////////////////////////////////////
	_imgCellMatrix = new sf::Image();   ///Image Pointer for the texture Matrix
	_matrixSize	   = new sf::Vector2i();///Size of the matrix 
	_texCellMatrix = new sf::Texture(); ///Texture Pointer for the sprite Matrix
	_sprCellMatrix = new sf::Sprite();  ///Sprite Pointer for the window
	_tempClock	   = new sf::Time();    ///Temp clock for the timer
	_elapsed       = new sf::Time();    ///Elapsed var for the temp clock
	_clock		   = new sf::Clock();	///Clock for the elapsed var
	_iFaktor	   = new int;           ///Faktor for the window
	_fDelay		   = new float; ///Delay value
	//_iCellCount    = new int;           ///Count of cells around one cell

	//Set value of vars//////////////////////////////////////////////////////
	_matrixSize->x = *width;  ///Set the width of the size matrix
	_matrixSize->y = *height; ///Set the height of the size matrix

	_tempChar = false; ///Set black pixel

	for (int x = 0; x < _matrixSize->x; x++) {
		_tempVector.push_back(_tempChar); ///Push back the temp char
	}

	for (int y = 0; y < _matrixSize->y; y++) {
		_cellMatrix.push_back(_tempVector);    ///Push back the temp vector
		_tempCellMatrix.push_back(_tempVector);///Push back the temp vector
	}

	_imgCellMatrix->create(_matrixSize->x, _matrixSize->y, sf::Color::Black); ///Create the cell matrix and set the size and default color
	std::cout << ">CellMgr: Matrix width = " << *width << " height = " << *height << std::endl;

	*_fDelay = 0;

	_iFaktor = faktor; ///Set value of the _iFaktor var
	_iCellCount = 0;   ///Set value of the cellcount to 0
	_iCount		= 0;

}

int CellMgr::_testPixel(sf::Vector2i *pos) //Test wether the cell at the position _pixelPos is alive or dead
{
	_iCellCount = 0;
	if (pos->y > 0) {
		if (_cellMatrix.at(pos->y - 1).at(pos->x))
			_iCellCount++;
		if (pos->x > 0 && _cellMatrix.at(pos->y - 1).at(pos->x - 1))
			_iCellCount++;
		if (pos->x + 1 < _matrixSize->x && _cellMatrix.at(pos->y - 1).at(pos->x + 1))
			_iCellCount++;
	}

	if (pos->y + 1 < _matrixSize->y) {
		if (_cellMatrix.at(pos->y + 1).at(pos->x))
			_iCellCount++;
		if (pos->x > 0 && _cellMatrix.at(pos->y + 1).at(pos->x - 1))
			_iCellCount++;
		if (pos->x + 1 < _matrixSize->x &&_cellMatrix.at(pos->y + 1).at(pos->x + 1))
			_iCellCount++;
	}

	if (pos->x > 0 && _cellMatrix.at(pos->y).at(pos->x - 1))
		_iCellCount++;
	if (pos->x + 1 < _matrixSize->x && _cellMatrix.at(pos->y).at(pos->x + 1))
		_iCellCount++;

	//std::cout << ">CellMgr _testPixel(x=" << pos->x << ", y=" << pos->y << "): count = " << _iCellCount << std::endl;
	return _iCellCount;
}

void CellMgr::_InitImage() //Overwrite the image with the main matrix
{
	for (int y = 0; y < _matrixSize->y; y++) {
		for (int x = 0; x < _matrixSize->x; x++) {
			if (_cellMatrix.at(y).at(x)) ///Check if the pixel is white
				_imgCellMatrix->setPixel(x, y, sf::Color::White); ///Set the pixel to white
			else
				_imgCellMatrix->setPixel(x, y, sf::Color::Black); ///Set the pixel to black
		}
	}
}

void CellMgr::overWriteMainMatrix() //Overwrite the main matrix with the temp matrix
{
	for (int y = 0; y < _matrixSize->y; y++) {///Run through vertical line
		for (int x = 0; x < _matrixSize->x; x++) {///Run throug horizontal line
			_cellMatrix.at(y).at(x) = _tempCellMatrix.at(y).at(x); ///Overwrite the value
		}
	}
}

void CellMgr::overWriteTempMatrix() //Overwrite the temp matrix with the main matrix
{
	for (int y = 0; y < _matrixSize->y; y++) {///Run through vertical line
		for (int x = 0; x < _matrixSize->x; x++) {///Run throug horizontal line
			_tempCellMatrix.at(y).at(x) = _cellMatrix.at(y).at(x); ///Overwrite the value
		}
	}
}

void CellMgr::showMapData() //Show the data of the two maps
{
	std::cout << ">CellMgr: CellMatrix-MapData:" << std::endl;
	for (int y = 0; y < _matrixSize->y; y++) { ///Run through vertical line 
		for (int x = 0; x < _matrixSize->x; x++) { ///Run throug horizontal line
			if (_cellMatrix.at(y).at(x))
				std::cout << "1";
			else
				std::cout << "0";
		}
		std::cout << std::endl;
	}
	std::cout << ">CellMgr: TempCellMatrix-MapData:" << std::endl;
	for (int y = 0; y < _matrixSize->y; y++){ ///Run through vertical line 
		for (int x = 0; x < _matrixSize->x; x++) { ///Run throug horizontal line
			if (_tempCellMatrix.at(y).at(x))
				std::cout << "1";
			else
				std::cout << "0";
		}
		std::cout << std::endl;
	}
}

void CellMgr::setDelay(float *delay) //Set the update time
{
	_fDelay = delay;
	std::cout << ">CellMgr: delay = " << *_fDelay << std::endl;
}

void CellMgr::Update() //Update the cell matrix
{
	*_elapsed = _clock->restart(); ///Get the elapsed time
	*_tempClock += *_elapsed;      ///Add the elapsed time to the temp time

	if (_tempClock->asSeconds() >= *_fDelay) {
		std::cout << ">CellMgr: Update matrix" << std::endl;
		for (int y = 0; y < _matrixSize->y; y++) { ///Run through vertical line 
			for (int x = 0; x < _matrixSize->x; x++) { ///Run throug horizontal line
				int _iCount = _testPixel(&sf::Vector2i(x, y));
				if (_cellMatrix.at(y).at(x) && (_iCount == 2 || _iCount == 3))
					_tempCellMatrix.at(y).at(x) = true;
				else if (!_cellMatrix.at(y).at(x) && _iCount == 3)
					_tempCellMatrix.at(y).at(x) = true;
				else
					_tempCellMatrix.at(y).at(x) = false;		
			}
		}
		overWriteMainMatrix();
		*_tempClock = _tempClock->Zero;
	}

}

void CellMgr::Clear() //Clear the matrix
{
	for (int y = 0; y < _matrixSize->y; y++) {
		for (int x = 0; x < _matrixSize->x; x++) {
			_cellMatrix.at(y).at(x)		= false;
			_tempCellMatrix.at(y).at(x) = false;
		}
	}
}

void CellMgr::setPixel(sf::Vector2i *pos, sf::Color *color) //Set a pixel
{
	if (*color == sf::Color::White) {
		_cellMatrix.at(pos->y).at(pos->x)	  = true; ///Set pixel to white
		_tempCellMatrix.at(pos->y).at(pos->x) = true; ///Set pixel to white
	}else {
		_cellMatrix.at(pos->y).at(pos->x)	  = false; ///Set pixel to black
		_tempCellMatrix.at(pos->y).at(pos->x) = false; ///Set pixel to black
	}
}

void CellMgr::setPixel(sf::Vector2i *pos) //Set a pixel
{
	if(_cellMatrix.at(pos->y).at(pos->x)){
		_cellMatrix.at(pos->y).at(pos->x)     = false; ///Set pixel to black
		_tempCellMatrix.at(pos->y).at(pos->x) = false; ///Set pixel to black
	}else{
		_cellMatrix.at(pos->y).at(pos->x)     = true; ///Set pixel to white
		_tempCellMatrix.at(pos->y).at(pos->x) = true; ///Set pixel to white
	}
}

sf::Sprite *CellMgr::returnCellMatrix() //Return the sprite of the matrix
{
	_InitImage(); ///Init the image
	_texCellMatrix->loadFromImage(*_imgCellMatrix); ///Load the texture as image
	_sprCellMatrix->setTexture(*_texCellMatrix);    ///Set the texture of the sprite matrix
	_sprCellMatrix->setScale(*_iFaktor, *_iFaktor); ///Scale the sprite 
	return _sprCellMatrix;
}

CellMgr::~CellMgr() //Destruktor
{
	delete _fDelay;         ///Delete the pointer
	delete _imgCellMatrix;	///Delete the pointer
	delete _texCellMatrix;  ///Delete the pointer
	delete _sprCellMatrix;  ///Delete the pointer
	delete _matrixSize;     ///Delete the pointer
	delete _tempClock;      ///Delete the pointer
	delete _elapsed;	    ///Delete the pointer
	delete _clock;          ///Delete the pointer
	delete _iFaktor;        ///Delete the pointer
	//delete _iCellCount;   ///Delete the pointer
}