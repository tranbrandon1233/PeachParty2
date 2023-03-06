#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"
#include "GameWorld.h"

class StudentWorld;
class Avatar;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor : public  GraphObject  //Actor class inheriting from GraphObject
{
public:
	Actor(StudentWorld* sw, const int imageID, int startX, int startY, int dir = 0, int depth = 0, double size = 1.0, bool baddie = false, bool square=false)  //Constructor for Actor class
		: GraphObject(imageID, startX, startY, dir, depth, size), m_alive(true), sw(sw), direction(dir), impacted(false), isBaddie(baddie), isSquare(square)  //peachHead(new Coords), yoshiHead(new Coords), peachTemp(peachHead), yoshiTemp(yoshiHead)  //Initialize parameters
	{}
	virtual void doSomething() = 0;   //Pure virtual method for doSomething, which will vary for each class

	StudentWorld* getSW() const {  //Get StudentWorld pointer
		return sw;
	}
	bool ifSquare() { return isSquare; }
	bool getImpacted() const { return impacted; }
	void setImpacted(bool wasImpacted) { impacted = wasImpacted; }
	bool getStatus() const {   //Get status of actor
		return m_alive;
	}
	void setStatus(bool status) {
		m_alive = status;
	}
	bool forkDir(int num);

	std::string checkFork(int dir) const;

	void changeDirection(char turn = ' ');  //Function to change directions with paramter if it is required

	int getActorDirection() const { return direction; }  //Get direction of actor
	bool checkValidDir();
	void setActorDirection(int dir) { direction = dir; }
	void moveActor();   //Move actor in  direction


	bool forkContains(std::string dir);
	void teleport();
	bool ifBaddie() const { return isBaddie; }
	bool landedOnSquare(int x, int y, Avatar* avatar, bool& activation);
	bool passedSquare(int x, int y, Avatar* avatar, bool& activation);
	void resetActivation(Avatar* avatar, bool& activation);
private:

	bool m_alive;
	bool isSquare;
	bool impacted;
	int direction;
	StudentWorld* sw;
	bool isBaddie;

};

class Square : public Actor {
public:
	Square(StudentWorld* sw, const int imageID, int startX, int startY, int dir = 0)
		:Actor(sw, imageID, startX, startY, dir, 1,1,false, true)
	{

	}
	int deductCoins(int amt, Avatar* avatar);
};

class Avatar : public Actor { //Player class
public:
	Avatar(StudentWorld* sw, int playerNum, int startX, int startY)  //Constructor for player
		: Actor(sw, playerNum == 1 ? IID_PEACH : IID_YOSHI, startX, startY), coins(0), stars(0), vortex(false), ticks_to_move(0), waitingToRoll(true), playerNum(playerNum)  //Initialize Actor and private vars
	{}
	virtual void doSomething();
	bool getVortex() {  //Get vortex
		if (&vortex == nullptr)
			vortex = false;
		return vortex;
	} 	
	int getPlayerNum() const { return playerNum; }
	void setCoins(int num) { coins = num; }  //Change coins
	void setStars(int num) { stars = num; }  //Change stars
	void setVortex(bool boolean) { vortex = boolean; } //Change vortex
	void setRollState(bool roll) { waitingToRoll = roll; } //CHange roll state
	bool getRollState() const { return waitingToRoll; }  //Set coins
	int getCoins()  {  //Get coins
		if (&coins == nullptr)
			coins = 0;
		return coins; 
	}  
	int getStars() {  //Get stars
		if (&stars == nullptr)
			stars = 0;
		return stars;
	}  	
	int getTicks() {  //Get stars
		if (&ticks_to_move == nullptr)
			ticks_to_move = 0;
		return ticks_to_move;
	} 
	void setTicks(int num) { ticks_to_move = num; } //Change ticks to move
	void swapCoins(Avatar* avatar);   //Change coins

	void swapStars(Avatar* avatar);  //Change stars
	void swapPosition(Avatar* avatar);


private:

	int playerNum;
	int coins;
	int stars;
	bool vortex;
	int ticks_to_move;
	bool waitingToRoll;
};



class CoinSquare : public Square {  //Class for CoinSquare inheriting from Actor superclass
public:
	CoinSquare(StudentWorld* sw, char type, int startX, int startY) //CoinSquare constructor
		: Square(sw, type == 'b' ? IID_BLUE_COIN_SQUARE : IID_RED_COIN_SQUARE, startX, startY), peachActivated(false), yoshiActivated(false)  //Initialize Actor with appropriate parameters

	{


	}
	virtual void doSomething();
private:
	bool peachActivated;
	bool yoshiActivated;

};

class StarSquare : public Square {
public:
	StarSquare(StudentWorld* sw, int startX, int startY)
		: Square(sw, IID_STAR_SQUARE, startX, startY), peachActivated(false), yoshiActivated(false) //Initialize Actor with appropriate parameters
	{

	}
	void doSomething();

private:
	bool peachActivated;
	bool yoshiActivated;
};

class DirectionalSquare : public Square {
public:
	DirectionalSquare(StudentWorld* sw, int startX, int startY, int dir)
		: Square(sw, IID_DIR_SQUARE, startX, startY, dir) //Initialize Actor with appropriate parameters
	{}
	void doSomething() {}  //Handled by Avatar class
};

class BankSquare : public Square {
public:
	BankSquare(StudentWorld* sw, int startX, int startY)
		: Square(sw, IID_BANK_SQUARE, startX, startY), peachActivated(false), yoshiActivated(false)  //Initialize Actor with appropriate parameters
	{}
	void doSomething();
private:
	bool peachActivated;
	bool yoshiActivated;

};


class EventSquare : public Square {
public:
	EventSquare(StudentWorld* sw, int startX, int startY)
		: Square(sw, IID_EVENT_SQUARE, startX, startY), peachActivated(false), yoshiActivated(false)  //Initialize Actor with appropriate parameters
	{}
	void doSomething();
	void activateEvent(Avatar* avatar);
private:
	bool peachActivated;
	bool yoshiActivated;

};

class DroppingSquare : public Square {
public:
	DroppingSquare(StudentWorld* sw, int startX, int startY)
		: Square(sw, IID_DROPPING_SQUARE, startX, startY), peachActivated(false), yoshiActivated(false)  //Initialize Actor with appropriate parameters
	{}
	void doSomething();
	void dropSomething(Avatar* avatar, bool& activation);
private:
	bool peachActivated;
	bool yoshiActivated;

};

class Baddies : public Actor {
public:
	Baddies(StudentWorld* sw, int id, int startX, int startY)
		:Actor(sw, id, startX, startY, 0, 0, 1, true), ticks_to_move(0), paused(true), pauseCount(180), peachActivated(false), yoshiActivated(false)
	{

	}
	void doSomething(std::string baddie);
	void pauseAction(Avatar* avatar, bool activation, std::string baddie);
	bool getPaused() const { return paused; }
	void setPaused(bool pause) { paused = pause; }
	bool getPeachActivation() const { return peachActivated; }
	void setPeachActivation(bool pause) { peachActivated = pause; }
	bool getYoshiActivation() const { return yoshiActivated; }
	void setYoshiActivation(bool pause) { yoshiActivated = pause; }
	int getTicks() const { return ticks_to_move; }
	void setTicks(int ticks) { ticks_to_move = ticks; }
	int getPauseCount() const { return pauseCount; }
	void setPauseCount(int pc) { pauseCount = pc; }

private:
	bool peachActivated;
	bool yoshiActivated;
	int ticks_to_move;
	bool paused;
	int pauseCount;
};

class Bowser : public Baddies {
public:
	Bowser(StudentWorld* sw, int startX, int startY)
		:Baddies(sw, IID_BOWSER, startX, startY)
	{

	}
	void doSomething() {
		Baddies::doSomething("Bowser");
	}

};

class Boo : public Baddies {
public:
	Boo(StudentWorld* sw, int startX, int startY)
		:Baddies(sw, IID_BOO, startX, startY)
	{

	}
	void doSomething() {
		Baddies::doSomething("Boo");
	}
};

class Vortex : public Actor {
public:
	Vortex(StudentWorld* sw, int dir, int startX, int startY) //Vortex constructor
		: Actor(sw, IID_VORTEX, startX, startY, dir)  //Initialize Actor with appropriate parameters

	{}
	virtual void doSomething();

};

#endif // ACTOR_H
