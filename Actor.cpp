#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"
#include <iostream>

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.
using namespace std;




std::string Actor::checkFork(int dir) const {
	int right = getX() + SPRITE_WIDTH <= VIEW_WIDTH ? getX() + SPRITE_WIDTH : -1; //Check if there is a wall in each direction
	int left = getX() - SPRITE_WIDTH >= 0 ? getX() - SPRITE_WIDTH : -1;
	int up = getY() + SPRITE_HEIGHT <= VIEW_HEIGHT ? getY() + SPRITE_HEIGHT : -1;
	int down = getY() - SPRITE_HEIGHT >= 0 ? getY() - SPRITE_HEIGHT : -1;
	switch (getActorDirection()) {  //Check if there is a fork for each direction
	case 0:  //Facing right
		if (right != -1 && up != -1 && down != -1) {  //Return available paths in fork
			if ((!getSW()->wallFound(right, getY()) && !getSW()->wallFound(getX(), up) && !getSW()->wallFound(getX(), down))) {
				return "urd";
			}
		}
		if (right != -1 && down != -1) {  //Return available paths in fork
			if (!getSW()->wallFound(right, getY()) && !getSW()->wallFound(getX(), down))
				return "rd";
		}
		if (up != -1 && down != -1) {  //Return available paths in fork
			if (!getSW()->wallFound(getX(), up) && !getSW()->wallFound(getX(), down))
				return "ud";
		}
		if (up != -1 && right != -1) {
			if (!getSW()->wallFound(getX(), up) && !getSW()->wallFound(right, getY()))
				return "ur";
		}
		break;
	case 90:  //Facing up
		if (right != -1 && up != -1 && left != -1) {  //Return available paths in fork
			if ((!getSW()->wallFound(left, getY()) && !getSW()->wallFound(getX(), up) && !getSW()->wallFound(right, getY()))) {
				return "url";
			}
		}
		if (right != -1 && left != -1) {  //Return available paths in fork
			if (!getSW()->wallFound(right, getY()) && !getSW()->wallFound(left, getY()))
				return "rl";
		}
		if (up != -1 && left != -1) {   //Return available paths in fork
			if (!getSW()->wallFound(left, getY()) && !getSW()->wallFound(getX(), up))
				return "ul";
		}
		if (right != -1 && up != -1) {   //Return available paths in fork
			if (!getSW()->wallFound(right, getY()) && !getSW()->wallFound(getX(), up))
				return "ur";
		}
		break;
	case 180:  //Facing left
		if (down != -1 && up != -1 && left != -1) {   //Return available paths in fork
			if ((!getSW()->wallFound(left, getY()) && !getSW()->wallFound(getX(), up) && !getSW()->wallFound(getX(), down))) {
				return "uld";
			}
		}
		if (up != -1 && left != -1) {
			if (!getSW()->wallFound(left, getY()) && !getSW()->wallFound(getX(), up))  //Return available paths in fork
				return "ul";
		}
		if (up != -1 && down != -1) {
			if (!getSW()->wallFound(getX(), up) && !getSW()->wallFound(getX(), down))  //Return available paths in fork
				return "ud";
		}
		if (down != -1 && left != -1) {

			if (!getSW()->wallFound(left, getY()) && !getSW()->wallFound(getX(), down))  //Return available paths in fork
				return "ld"; 
		}
		break;
	case 270:  //Facing down
		if (right != -1 && down != -1 && left != -1) {   //Return available paths in fork

			if ((!getSW()->wallFound(left, getY()) && !getSW()->wallFound(getX(), down) && !getSW()->wallFound(right, getY()))) {
				return "lrd";
			}
		}
		if (right != -1 && left != -1) {  //Return available paths in fork

			if (!getSW()->wallFound(left, getY()) && !getSW()->wallFound(right, getY()))
				return "lr";
		}
		if (right != -1 && down != -1) {  //Return available paths in fork
			if (!getSW()->wallFound(right, getY()) && !getSW()->wallFound(getX(), down))
				return "rd";
		}
		if (down != -1 && left != -1) {  //Return available paths in fork
			if (!getSW()->wallFound(left, getY()) && !getSW()->wallFound(getX(), down))
				return "ld";
		}
		break;
	}
	return "";  //Return false if not found
}

void Actor::moveActor() {
	switch (getActorDirection()) {
	case 0:
			moveTo(getX() + 2, getY());
	
		break;
	case 90:
			moveTo(getX() , getY()+2);
	
		break;
	case 180:
			moveTo(getX() - 2, getY());
		
		break;
	case 270:
			moveTo(getX(), getY()-2);
		
		break;

	}
}
void Actor::changeDirection(char turn) {  //Change direction of actor
	if (turn != ' ') {  //Case if required to turn
		switch (turn) {
		case 'u':

			direction = 90;  //Change direction
			setDirection(0);  //Change direction to left
			break;
		case 'd':

			direction = 270;  //Change direction
			setDirection(0);  //Change direction to left
			break;
		case 'l':
			;
			direction = 180;  //Change direction
			setDirection(180);  //Change direction to left
			break;
		case 'r':

			direction = 0;  //Change direction
			setDirection(0);  //Change direction to left
			break;
		}
		return;
	}
	switch (direction) {
	case 0:   //Facing right
		if (sw->wallFound(getX() + SPRITE_WIDTH, getY()) == true) {  //If a wall was found at that point, 
			if (sw->wallFound(getX(), getY() + SPRITE_HEIGHT) == false) {
				direction = 90;  //Change direction
				setDirection(0);  //Change direction to up
			}
			else if (sw->wallFound(getX(), getY() - SPRITE_HEIGHT) == false) {
				direction = 270;  //Change direction
				setDirection(0);  //Change direction to down

			}

		}
		break;
	case 90:  //Facing up
		if ( sw->wallFound(getX(), getY() +SPRITE_HEIGHT) == true) {  //If a wall was found at that point, 
			if (sw->wallFound(getX() + SPRITE_WIDTH, getY()) == false) {
				direction = 0;  //Change direction
				setDirection(0);  //Change direction to right
			}
			else if (sw->wallFound(getX() -SPRITE_WIDTH, getY()) == false) {
				direction = 180;  //Change direction
				setDirection(180);  //Change direction to left

			}
		}
		break;
	case 180:  //Facing left
		if (sw->wallFound(getX() - SPRITE_WIDTH, getY()) == true) {  //If a wall was found at that point, 
			if (sw->wallFound(getX(), getY() + SPRITE_HEIGHT) == false) {
				direction = 90;  //Change direction
				setDirection(0);  //Change direction to left
			}
			else if (sw->wallFound(getX(), getY() - SPRITE_HEIGHT) == false) {
				direction = 270;  //Change direction
				setDirection(0);  //Change direction to left

			}
		}
		break;
	case 270:   //Facing down
		if (sw->wallFound(getX(), getY() - SPRITE_HEIGHT) == true) {  //If a wall was found at that point, 
			if (sw->wallFound(getX() + SPRITE_WIDTH, getY()) == false) {
				direction = 0;  //Change direction
				setDirection(0);  //Change direction to right
			}
			else if (sw->wallFound(getX() - SPRITE_WIDTH, getY()) == false) {
				direction = 180;  //Change direction
				setDirection(180);  //Change direction to left

			}

		}
		break;

	}
}

bool Actor::checkValidDir() { //Check if direction is valid
	switch (getActorDirection()) {
	case 0:
		if (sw->wallFound(getX() + SPRITE_WIDTH, getY()) == true)   //If a wall was found at that point, 
			return false;
		break;
	case 90:
		if (sw->wallFound(getX(), getY() + SPRITE_HEIGHT) == true)   //If a wall was found at that point, 
			return false;
		break;
	case 180:
		if (sw->wallFound(getX() - SPRITE_WIDTH, getY()) == true)   //If a wall was found at that point, 
			return false;
		break;
	case 270:
		if (sw->wallFound(getX(), getY() - SPRITE_HEIGHT) == true)   //If a wall was found at that point, 
			return false;
		break;
	}
	return true;
}

int Square::deductCoins(int amt, Avatar* avatar) {
	if (avatar->getCoins() - amt >= 0) {  //If the player has at least 5 coins
		avatar->setCoins(avatar->getCoins() - amt);  //Take 5 of their coins and deposit into bank
		return amt;
	}
	else {  //If not, take what they do have and deposit into bank
		int amtLost = avatar->getCoins();
		avatar->setCoins(0);
		return amtLost;
	}
	return -1;
}
void Actor::resetActivation(Avatar* avatar, bool& activation) {
	if (avatar != nullptr) {
		int x1 = avatar->getX();
		int x2 = getY();
		if (getX() != avatar->getX() || getY() != avatar->getY())  //Reset once they move off of it
			activation = false;
	}

}

bool Actor::landedOnSquare(int x, int y, Avatar* avatar, bool& activation) {
	if (avatar != nullptr && !activation) {
		if (avatar->getX() == getX() && avatar->getY() == getY() && avatar->getTicks() == 0) { //If player landed on coin square
			activation = true;
			return true;
		}
	}
	resetActivation(avatar, activation); //Reset the activation if necessary
	return false;
}

bool Actor::passedSquare(int x, int y, Avatar* avatar, bool& activation) {
	if (avatar != nullptr && !activation) {
		if (avatar->getX() == getX() && avatar->getY() == getY()) { //If player landed on coin 
			activation = true;
			return true;
		}
	}
	resetActivation(avatar, activation); //Reset the activation if necessary
	return false;
}


void CoinSquare::doSomething() {  //Manages behavior of square
	if (getStatus()) { //Check if alive
		if (landedOnSquare(getX(), getY(), getSW()->getPeach(), peachActivated)) { //If player landed on coin square
			if (getSW()->boardContents(getX(), getY()) == Board::blue_coin_square) {
				getSW()->getPeach()->setCoins(getSW()->getPeach()->getCoins() + 3);
				getSW()->playSound(SOUND_GIVE_COIN);

			}
			else if (getSW()->boardContents(getX(), getY()) == Board::red_coin_square) {
				getSW()->getPeach()->setCoins(getSW()->getPeach()->getCoins() - 3);
				getSW()->playSound(SOUND_TAKE_COIN);
			}

		}

		if (landedOnSquare(getX(), getY(), getSW()->getYoshi(), yoshiActivated)) { //If player landed on coin square
			if (getSW()->boardContents(getX(), getY()) == Board::blue_coin_square) {
				getSW()->getYoshi()->setCoins(getSW()->getYoshi()->getCoins() + 3);
				getSW()->playSound(SOUND_GIVE_COIN);
			}
			else if (getSW()->boardContents(getX(), getY()) == Board::red_coin_square) {
				getSW()->getYoshi()->setCoins(getSW()->getYoshi()->getCoins() - 3);
				getSW()->playSound(SOUND_TAKE_COIN);
			}

		}
	}

	else {  //If not, return
		return;
	}

}
void StarSquare::doSomething() {

	if (passedSquare(getX(), getY(), getSW()->getPeach(), peachActivated)) { //If square has not been activated
		if (getSW()->getPeach()->getCoins() < 20) { //If player does not have enough coins to buy star, return
			return;
		}
		else {  //If player has enough coins, buy star

			getSW()->getPeach()->setCoins(getSW()->getPeach()->getCoins() - 20);
			getSW()->getPeach()->setStars(getSW()->getPeach()->getStars() + 1);
			getSW()->playSound(SOUND_GIVE_STAR);
		}
	}
	if (passedSquare(getX(), getY() == getY(), getSW()->getYoshi(), yoshiActivated)) { //If player landed on star square
		if (getSW()->getYoshi()->getCoins() < 20) {  //If player does not have enough coins to buy star, return
			return;
		}
		else {  //If player has enough coins, buy star
			getSW()->getYoshi()->setCoins(getSW()->getYoshi()->getCoins() - 20);
			getSW()->getYoshi()->setStars(getSW()->getYoshi()->getStars() + 1);
			getSW()->playSound(SOUND_GIVE_STAR);
		}
	}

}

void BankSquare::doSomething() {
	if (landedOnSquare(getX(), getY(), getSW()->getPeach(), peachActivated)) { //If player landed on bank square
		getSW()->getPeach()->setCoins(getSW()->getPeach()->getCoins() + getSW()->getBankTotal());  //Give them the bank total and empty it
		getSW()->setBankTotal(0);
		getSW()->playSound(SOUND_WITHDRAW_BANK);
	}

	else if (passedSquare(getX(), getY(), getSW()->getPeach(), peachActivated)) { //If player passed the bank square
		int amt = deductCoins(5, getSW()->getPeach());
		getSW()->setBankTotal(amt + getSW()->getBankTotal());
		getSW()->playSound(SOUND_DEPOSIT_BANK);
	}


	if (landedOnSquare(getX(), getY(), getSW()->getYoshi(), yoshiActivated)) { //If player landed on bank square
		getSW()->getYoshi()->setCoins(getSW()->getYoshi()->getCoins() + getSW()->getBankTotal());  //Give them the bank total and empty it
		getSW()->setBankTotal(0);
		getSW()->playSound(SOUND_WITHDRAW_BANK);
	}

	else if (passedSquare(getX(), getY(), getSW()->getYoshi(), yoshiActivated)) { //If player passed the bank square
		int amt = deductCoins(5, getSW()->getYoshi());
		getSW()->setBankTotal(amt + getSW()->getBankTotal());
		getSW()->playSound(SOUND_DEPOSIT_BANK);
	}


}

void EventSquare::doSomething() {
	if (landedOnSquare(getX(), getY(), getSW()->getPeach(), peachActivated))  //Activate event for both players
		activateEvent(getSW()->getPeach());

	if (landedOnSquare(getX(), getY(), getSW()->getYoshi(), yoshiActivated))
		activateEvent(getSW()->getYoshi());


}

void EventSquare::activateEvent(Avatar* avatar) {
	switch (randInt(1, 3)) {
	case 1: //Teleporting
		avatar->teleport();
		setActorDirection(-1); //Make direction invalid
		getSW()->playSound(SOUND_PLAYER_TELEPORT);
		break;
	case 2:  //Swap positions
		avatar->swapPosition(avatar->getPlayerNum() == 1 ? getSW()->getYoshi() : getSW()->getPeach());
		yoshiActivated = avatar->getPlayerNum() == 1 ? true : yoshiActivated;  //Prevents other avatar from teleporting
		peachActivated = avatar->getPlayerNum() == 2 ? true : peachActivated;  //Prevents other avatar from teleporting
		getSW()->playSound(SOUND_PLAYER_TELEPORT);
		break;
	case 3: //Give vortex
		avatar->setVortex(true);
		getSW()->playSound(SOUND_GIVE_VORTEX);
		break;
	}
}


void DroppingSquare::dropSomething(Avatar* avatar, bool& activation) {
	if (landedOnSquare(getX(), getY(), avatar, activation)) {  //If player landed on a square,
		switch (randInt(1, 2)) {   //Randomly deduct coins or a star and play sound
		case 1:
			deductCoins(10, avatar);
			break;
		case 2:
			avatar->setStars(avatar->getStars() - 1 > 0 ? avatar->getStars() - 1 : 0);
			break;
		}
		getSW()->playSound(SOUND_DROPPING_SQUARE_ACTIVATE);
	}
}

void DroppingSquare::doSomething() {
	dropSomething(getSW()->getPeach(), peachActivated);  //Drop something from Peach and Yoshi
	dropSomething(getSW()->getYoshi(), yoshiActivated);
}


void Vortex::doSomething() {
	if (!getStatus()) {  //Return if not alive
		return;
	}
	moveActor();  //Move vortex

	if (getX() > BOARD_WIDTH || getX() < 0 || getY() < 0 || getY() > BOARD_HEIGHT) {  //Kill if out of bounds
		setStatus(false);
	}
	Actor* baddie = getSW()->overlapsBaddie(getX(), getY());
	if (baddie != nullptr) {  //If baddie hit, impact it
		baddie->setImpacted(true);
		setStatus(false);  //Delete self
		getSW()->playSound(SOUND_HIT_BY_VORTEX);
	}

}

bool Actor::forkContains(std::string dir) {
	return checkFork(getActorDirection()).find(dir) != std::string::npos;  //Return if direction is found in fork
}




void Avatar::doSomething()
{
	int input = getSW()->getAction(playerNum);

	if (waitingToRoll) {   //Check if waiting to roll
		if (input == ACTION_ROLL) {
			changeDirection();  //Change direction if needed
			ticks_to_move = 8 * randInt(1, 10);  //Set ticks to move
			waitingToRoll = false;  //No longer waiting to roll
		}
		else if (input == ACTION_FIRE && vortex) {  //If firing and has a vortex
			switch (getActorDirection()) {  //Create vortex based on direction
			case 0:
				getSW()->addVortex(getX() + SPRITE_WIDTH, getY(), getActorDirection());
				break;
			case 90:
				getSW()->addVortex(getX(), getY() + SPRITE_HEIGHT, getActorDirection());
				break;
			case 180:
				getSW()->addVortex(getX() - SPRITE_WIDTH, getY(), getActorDirection());
				break;
			case 270:
				getSW()->addVortex(getX(), getY() - SPRITE_HEIGHT, getActorDirection());
				break;
			}
			getSW()->playSound(SOUND_PLAYER_FIRE);
			vortex = false;
		}

		else {
			return;
		}

	}
	else {

		if (getSW()->boardContents(getX(), getY()) == Board::down_dir_square) { //If on top of a dir square
			changeDirection('d');
		}
		else if (getSW()->boardContents(getX(), getY()) == Board::up_dir_square) {
			changeDirection('u');
		}
		else if (getSW()->boardContents(getX(), getY()) == Board::left_dir_square) {
			changeDirection('l');
		}
		else if (getSW()->boardContents(getX(), getY()) == Board::right_dir_square) {
			changeDirection('r');
		}
		else if (checkFork(getActorDirection()) != "") { //If there is a fork, change direction based on user input				
			int input = getSW()->getAction(playerNum);
			if (getX() % SPRITE_WIDTH == 0 && getY() % SPRITE_HEIGHT == 0) {
				if (input == ACTION_LEFT && forkContains("l")) {
					changeDirection('l');
					moveActor();
				}
				else if (input == ACTION_RIGHT && forkContains("r")) {
					changeDirection('r');
					moveActor();
				}
				else if (input == ACTION_DOWN && forkContains("d")) {
					changeDirection('d');
					moveActor();
				}
				else if (input == ACTION_UP && forkContains("u")) {
					changeDirection('u');
					moveActor();

				}

				else {
					return;
				}
			}
		}
			changeDirection();
		
				moveActor();
		ticks_to_move--;  //Decrement ticks to move
		if (!ticks_to_move)  //If ticks to move is zero, set waiting to roll to true
			waitingToRoll = true;
	}
}

void Avatar::swapCoins(Avatar* avatar) {   //Change coins
	int tempCoins = coins;
	coins = avatar->getCoins();
	avatar->setCoins(tempCoins);
}
void Avatar::swapStars(Avatar* avatar) {  //Change stars
	int tempStars = stars;
	stars = avatar->getStars();
	avatar->setStars(tempStars);
}
void Avatar::swapPosition(Avatar* avatar) {
	int tempTicks = ticks_to_move; //Swap ticks
	ticks_to_move = avatar->getTicks();
	avatar->setTicks(tempTicks);

	bool tempRoll = waitingToRoll; //Swap roll states
	waitingToRoll = avatar->getRollState();
	avatar->setRollState(tempRoll);

	int tempDir = getActorDirection(); //Swap directions
	setActorDirection(avatar->getActorDirection());
	avatar->setActorDirection(tempDir);

	int tempSpriteDir = getDirection(); //Swap sprite directions
	setDirection(avatar->getDirection());
	avatar->setDirection(tempSpriteDir);
}

void newCoords(int& x, int& y) {
	x = randInt(0, BOARD_WIDTH - 1); //Get random x and y
	y = randInt(0, BOARD_HEIGHT - 1); //Get random x and y
}

void Actor::teleport() {
	int x, y;
	newCoords(x, y);
	while (getSW()->isSquare(x,y) == nullptr) {  //Loop while  (x,y) is not a square
		newCoords(x, y); //Randomize again

	}
	moveTo(x , y );  //Move the avatar there
}

void Baddies::pauseAction(Avatar* avatar, bool activation, std::string baddie) {
	if (avatar != nullptr) {
		if (getX() == avatar->getX() && getY() == avatar->getY() && avatar->getRollState() == true && !activation) {
			if (baddie == "Bowser") {  //Lose coins and stars if Bowser
				switch (randInt(1, 2)) {
				case 1:  //50% chance
					avatar->setCoins(0);
					avatar->setStars(0);

					if (avatar->getPlayerNum() == 1) {  //Swap them if Boo
						avatar->swapCoins(getSW()->getYoshi());
						avatar->swapStars(getSW()->getYoshi());
					}
					else if (avatar->getPlayerNum() == 2) {
						avatar->swapCoins(getSW()->getPeach());
						avatar->swapStars(getSW()->getPeach());
					}
					break;
				}
			}
			else if (baddie == "Boo") {
				if (avatar->getPlayerNum() == 1 && getSW()->getYoshi() != nullptr) {  //Swap them if Boo
					avatar->swapCoins(getSW()->getYoshi());
					avatar->swapStars(getSW()->getYoshi());
				}
				else if (avatar->getPlayerNum() == 2 && getSW()->getPeach() != nullptr) {
					avatar->swapCoins(getSW()->getPeach());
					avatar->swapStars(getSW()->getPeach());

				}
			}
			getSW()->playSound(baddie == "Bowser" ? SOUND_BOWSER_ACTIVATE : SOUND_BOO_ACTIVATE);  //Play sound if Bowser or Boo
			setPeachActivation(avatar->getPlayerNum() == 1 ? true : getPeachActivation());  //Set activation as needed
			setYoshiActivation(avatar->getPlayerNum() == 2 ? true : getYoshiActivation());


		}
		if (floor(getX() / SPRITE_WIDTH) != floor(avatar->getX() / SPRITE_WIDTH) || floor(avatar->getY() / SPRITE_HEIGHT) != floor(getY() / SPRITE_HEIGHT)) {  //Reset once they move off of it
			setPeachActivation(avatar->getPlayerNum() == 1 ? false : getPeachActivation());  //Set activation as needed
			setYoshiActivation(avatar->getPlayerNum() == 2 ? false : getYoshiActivation());
		}
	}
}
void Baddies::doSomething(std::string baddie) {
	if (getPaused()) {
		pauseAction(getSW()->getPeach(), getPeachActivation(), baddie);  //Pause actions for both players
		pauseAction(getSW()->getYoshi(), getYoshiActivation(), baddie);
		setPauseCount(getPauseCount() - 1);  //Decrement pause ticks
		if (getPauseCount() <= 0) {
			int squares_to_move = randInt(1, baddie == "Bowser" ? 10 : 3);
			setTicks(squares_to_move * 8);
			while (!checkValidDir()) {
				switch (randInt(1, 4)) {  //Randomly select direction
				case 1:
					changeDirection('u');
					break;
				case 2:
					changeDirection('d');
					break;
				case 3:
					changeDirection('l');
					break;
				case 4:
					changeDirection('r');
					break;
				}
			}
			setPaused(false);
		}
	}
	if (!getPaused()) {
		if (getX() % 16 == 0 && getY() % 16 == 0) { //If on top of square
			if (checkFork(getActorDirection()) != "")  //If at fork
				switch (randInt(1, 4)) { //Randomly select direction if valid
				case 1:
					if (forkContains("u")) {
						changeDirection('u');
					}
					break;
				case 2:
					if (forkContains("d")) {
						changeDirection('d');
					}
					break;
				case 3:
					if (forkContains("r")) {
						changeDirection('r');
					}
					break;
				case 4:
					if (forkContains("l")) {
						changeDirection('l');
					}
					break;
				}
			while (!checkValidDir()) {  //Change direction until it is valid
				changeDirection();
			}
		}
		moveActor();
		setTicks(getTicks() - 1);
		if (getTicks() == 0) {
			setPaused(true);
			setPauseCount(180);
			if (baddie == "Bowser") {  //Only do this if Bowser
				switch (randInt(1, 4)) {  //1 in 4 chance to create a dropping square
				case 1:
					getSW()->deleteSquare(getX(), getY());
					getSW()->addDroppingSquare(getX(), getY());
					getSW()->playSound(SOUND_DROPPING_SQUARE_CREATED);
					break;
				}
			}
		}

	}
	if (getImpacted()) {  //If impacted,
		teleport();  //Teleport, set direciton, and pause
		setDirection(0);
		setActorDirection(0);
		setPaused(true);
		setPauseCount(180);
	}
}