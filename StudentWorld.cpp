#include "StudentWorld.h"
#include "Actor.h"
#include "GameConstants.h"
#include "Board.h"
#include <string>

using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
	: GameWorld(assetPath), m_actors(), m_board(), m_peach(nullptr), m_yoshi(nullptr), bankTotal(0)
{
}


int StudentWorld::init()
{

	//create board
	m_board = new Board();
	// create file name string
	std::string file = assetPath() + "board0" + std::to_string(getBoardNumber()) + ".txt";

	Board::LoadResult result = m_board->loadBoard(file);
	startCountdownTimer(99);  //Start timer
	int i = 0;  //Track index of vector
	bool player1Used = false;  //Track if Peach is used for Player 1
	for (int gy = 0; gy < BOARD_HEIGHT; gy++) {  //For entire grid
		for (int gx = 0; gx < BOARD_WIDTH; gx++) {
			switch (m_board->getContentsOf(gx, gy)) {  //Switch to fill vector of actors
			case Board::blue_coin_square:   //Add blue coin squares
				addBlueCoin(SPRITE_WIDTH * gx, SPRITE_HEIGHT * gy);
				break;
			case Board::red_coin_square: //Add red coin squares
				addRedCoin(SPRITE_WIDTH * gx, SPRITE_HEIGHT * gy);
				break;
			case Board::star_square: //Add star squares
				addStarSquare(SPRITE_WIDTH * gx, SPRITE_HEIGHT * gy);
				break;
			case Board::bank_square: //Add bank squares
				addBankSquare(SPRITE_WIDTH * gx, SPRITE_HEIGHT * gy);
				break;
			case Board::down_dir_square: //Add dir squares
				addDirectionalSquare(SPRITE_WIDTH * gx, SPRITE_HEIGHT * gy, 'd');
				break;
			case Board::up_dir_square:
				addDirectionalSquare(SPRITE_WIDTH * gx, SPRITE_HEIGHT * gy, 'u');
				break;
			case Board::left_dir_square:
				addDirectionalSquare(SPRITE_WIDTH * gx, SPRITE_HEIGHT * gy, 'l');
				break;
			case Board::right_dir_square:
				addDirectionalSquare(SPRITE_WIDTH * gx, SPRITE_HEIGHT * gy, 'r');
				break;
			case Board::event_square: //Add event square
				addEventSquare(SPRITE_WIDTH * gx, SPRITE_HEIGHT * gy);
				break;
			case Board::bowser: //Add Bowser
				addBowser(SPRITE_WIDTH * gx, SPRITE_HEIGHT * gy);
				addBlueCoin(SPRITE_WIDTH * gx, SPRITE_HEIGHT * gy);
				break;
			case Board::boo: //Add Boos
				addBoo(SPRITE_WIDTH * gx, SPRITE_HEIGHT * gy);
				addBlueCoin(SPRITE_WIDTH * gx, SPRITE_HEIGHT * gy);
				break;
			default:
				break;
			}
			if (!player1Used && m_board->getContentsOf(gx, gy) == Board::player) {  //Add Peach if it has not been added yet
				addPeach(SPRITE_WIDTH * gx, SPRITE_HEIGHT * gy);
				addBlueCoin(SPRITE_WIDTH * gx, SPRITE_HEIGHT * gy);
				player1Used = true;

			}
			else if (player1Used && m_board->getContentsOf(gx, gy) == Board::player) {  //Add Yoshi after Peach has been added
				addYoshi(SPRITE_WIDTH * gx, SPRITE_HEIGHT * gy);
				addBlueCoin(SPRITE_WIDTH * gx, SPRITE_HEIGHT * gy);
			}
		}
	}
	return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
	// This code is here merely to allow the game to build, run, and terminate after you hit ESC.
	// Notice that the return value GWSTATUS_NOT_IMPLEMENTED will cause our framework to end the game.



	for (list<Actor*>::iterator itr = m_actors.begin(); itr != m_actors.end();){
			if (!(*itr)->getStatus()) { //If actor is dead, delete it and erase it from the list
				delete *itr;
				itr = m_actors.erase(itr);
		}
			else {
				(*itr)->doSomething();  //Each actor runs doSomething every tick
				itr++;
			}
	}

	// Update the Game Status 
	if (getPeach() != nullptr && getYoshi() != nullptr) { //String if both players are playing
		std::string peachVortex = getPeach()->getVortex() ? " VOR" : "";
		std::string yoshiVortex = getYoshi()->getVortex() ? " VOR" : "";
		setGameStatText("P1 Roll : " + std::to_string(getPeach()->getTicks()) + " Stars : " + std::to_string(getPeach()->getStars()) + " $$ : " + std::to_string(getPeach()->getCoins()) + peachVortex + " | Time : " + std::to_string(timeRemaining()) + " | Bank : " + std::to_string(getBankTotal()) + " | P2 Roll : " + std::to_string(getYoshi()->getTicks()) + " Stars : " + std::to_string(getYoshi()->getStars()) + " $$ : " + std::to_string(getYoshi()->getCoins()) + yoshiVortex);
		setFinalScore(getYoshi()->getStars(), getYoshi()->getCoins());
		setFinalScore(getPeach()->getStars(), getPeach()->getCoins());
	}
	else if (getPeach() != nullptr) {  //String if only Peach is playing
		if (getPeach()->getCoins() == NULL && getPeach()->getStars() == NULL) {
			getPeach()->setCoins(0);
			getPeach()->setStars(0);
		}
			std::string peachVortex = getPeach()->getVortex() ? " VOR" : "";
			setGameStatText("P1 Roll : " + std::to_string(getPeach()->getTicks()) + " Stars : " + std::to_string(getPeach()->getStars()) + " $$ : " + std::to_string(getPeach()->getCoins())  + peachVortex + " | Time : " + std::to_string(timeRemaining()) + " | Bank : " + std::to_string(getBankTotal()));
		
	}
	else if (getYoshi() != nullptr) {  //String if only Yoshi is playing
		if (getYoshi()->getCoins() != NULL && getYoshi()->getStars() != NULL) {
			getYoshi()->setCoins(0);
			getYoshi()->setStars(0);
		}
			std::string yoshiVortex = getYoshi()->getVortex() ? " VOR" : "";
			setGameStatText("Time : " + std::to_string(timeRemaining()) + " | Bank : " + std::to_string(getBankTotal()) + " | P2 Roll : " + std::to_string(getYoshi()->getTicks()) + " Stars : " + std::to_string(getYoshi()->getStars()) + " $$ : " + std::to_string(getYoshi()->getCoins()) + yoshiVortex);

		
	}

	if (timeRemaining() == 0)  //If out of time
	{

		playSound(SOUND_GAME_FINISHED);  //Finish game and find winner
		if (getYoshi() != nullptr && getPeach() != nullptr) {
			if (getYoshi()->getCoins() + getYoshi()->getStars() > getPeach()->getCoins() + getPeach()->getStars())
			{
				setFinalScore(getYoshi()->getStars(), getYoshi()->getCoins());
				return GWSTATUS_YOSHI_WON;
			}
			else // peach won
			{
				setFinalScore(getPeach()->getStars(), getPeach()->getCoins());
				return GWSTATUS_PEACH_WON;
			}
		}
		else if (getYoshi() != nullptr) { //Yoshi wins if Peach is not there
			setFinalScore(getYoshi()->getStars(), getYoshi()->getCoins());
			return GWSTATUS_YOSHI_WON;
		}
		else if (getPeach() != nullptr) { //Peach wins if Yoshi is not there
			setFinalScore(getPeach()->getStars(), getPeach()->getCoins());
			return GWSTATUS_PEACH_WON;

		}
	}

	return GWSTATUS_CONTINUE_GAME; //Continue otherwise
}

void StudentWorld::cleanUp()
{
	for (list<Actor*>::iterator itr = m_actors.begin(); itr != m_actors.end();) {
			delete* itr;
			itr = m_actors.erase(itr);
			itr++;
		}
	m_actors.clear(); //Clear list
	delete m_board;  //Delete board
}

Actor* StudentWorld::overlapsBaddie(int x, int y) const { //Check if there is an overlap at (x,y)
	for (auto actor : m_actors) {  //For each actor in list
		if (actor->ifBaddie()) { //Check if there is sprite overlap for baddies only

			switch (actor->getDirection()) { //Depending on the direction,
			case 0:
				if (actor->getX() <= x && actor->getX() + SPRITE_WIDTH - 1 >= x && actor->getY() == y) //Check if there is sprite overlap
					return actor;
				break;
			case 90:
				if (actor->getY() <= y && actor->getY() + SPRITE_HEIGHT - 1 >= y && actor->getX() == x) //Check if there is sprite overlap
					return actor;
				break;
			case 180:
				if (actor->getX() >= x && actor->getX() - SPRITE_WIDTH + 1 <= x && actor->getY() == y) //Check if there is sprite overlap
					return actor;
				break;
			case 270:
				if (actor->getY() >= y && actor->getY() - SPRITE_HEIGHT + 1 <= y && actor->getX() == x) //Check if there is sprite overlap
					return actor;
				break;

			}
		}
	}
	return nullptr; //Return fals if no overlap found
}

const bool StudentWorld::wallFound(int x, int y)  //Check if there is an overlap at (x,y)
{
	if (m_board->getContentsOf(x / SPRITE_WIDTH, y / SPRITE_HEIGHT) != Board::empty) {  //Check if there is overlap
		return false;   //If so, return true
	}

	return true;   //If not found, return false
}

void StudentWorld::deleteSquare(int x, int y) {
	for (auto actor : m_actors) {
		if (actor->getX() == x && actor->getY() == y && isSquare(actor->getX(), actor->getY()) == actor) {  //Check if there is an actor at (x,y) and is a square
			actor->setStatus(false);
			break;
		}
	}
}

Actor* StudentWorld::isSquare(int x, int y) {
	for (auto actor : m_actors) {
		if (actor->getX() == x && actor->getY() == y && actor->ifSquare()) //Check if there is an actor at (x,y) and is a square
			return actor; //Return the square
	}
	return nullptr; //Return nullptr if not found
}

void StudentWorld::addPeach(const int x, const int y) {  //Methods for all actors
	m_peach = new Avatar(this, 1, x, y);
	addActor(m_peach);
}
void StudentWorld::addYoshi(const int x, const int y) {
	m_yoshi = new Avatar(this, 2, x, y);
	addActor(m_yoshi);
}
void StudentWorld::addRedCoin(const int x, const int y) { addActor(new CoinSquare(this, 'r', x, y)); }
void StudentWorld::addBlueCoin(const int x, const int y) { addActor(new CoinSquare(this, 'b', x, y)); }
void StudentWorld::addStarSquare(const int x, const int y) { addActor(new StarSquare(this, x, y)); }
void StudentWorld::addDirectionalSquare(const int x, const int y, const char dir) { addActor(new DirectionalSquare(this, dir, x, y)); }
void StudentWorld::addBankSquare(const int x, const int y) { addActor(new BankSquare(this, x, y)); }
void StudentWorld::addEventSquare(const int x, const int y) { addActor(new EventSquare(this, x, y)); }
void StudentWorld::addVortex(const int x, const int y, int dir) { addActor(new Vortex(this, x, y, dir)); }
void StudentWorld::addDroppingSquare(const int x, const int y) { addActor(new DroppingSquare(this, x, y)); }
void StudentWorld::addBowser(const int x, const int y) { addActor(new Bowser(this, x, y)); }
void StudentWorld::addBoo(const int x, const int y) { addActor(new Boo(this, x, y)); }

void StudentWorld::addActor(Actor* actor) {  //Add actors into list
	if (actor != nullptr && actor->getSW() != nullptr)
		m_actors.push_back(actor);
}