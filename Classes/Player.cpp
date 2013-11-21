/*
 * Player.cpp
 *
 *  Created on: Oct 24, 2013
 *      Author: probigi
 */

#include "Player.h"

USING_NS_CC;

Player::Player() {
}

void Player::create() {
	_skins = new std::vector<CCParticleSystem*>();
	_velocityes = new std::vector<CCPoint*>();
	_targets = new std::vector<CCPoint*>();

	activeTouches = 1;

	addSkin();
}

void Player::addSkin() {
	isLive = true;
	_speed = 30 + CCRANDOM_0_1()*300;
	_viewSize = 40 + CCRANDOM_0_1()*30;

	CCParticleSystem* skin = new CCParticleSystem();

	skin = CCParticleMeteor::create();
	skin->setStartColor(ccc4f(1,1,1,1));
	skin->setGravity(ccp(0,0));
	skin->setLife(0.5);
	skin->setLifeVar(0.1);
	skin->setContentSize(CCSize(_viewSize, _viewSize));
	skin->setStartSize(_viewSize);
    skin->setStartSizeVar(_viewSize);
	_skins->push_back(skin);

	CCPoint *v = new CCPoint(0,0);
	CCPoint *t = new CCPoint(0,0);
	_velocityes->push_back(v);
	_targets->push_back(t);

	if (_skins->size() > 1) {
		CCParticleSystem* first = _skins->front();
		skin->setPosition(first->getPosition());
		first->getParent()->addChild(skin);
	}
}

void Player::removeSkin(int id) {
	CCParticleSystem *skin = _skins->at(id);

	_skins->erase(_skins->begin()+id);
	_targets->erase(_targets->begin() + id);
	_velocityes->erase(_velocityes->begin() + id);


	skin->setStartSize(_viewSize*2);
	skin->setStartSizeVar(_viewSize*2);
	skin->setSpeed(300);
	skin->setLife(0.2);
	skin->setLifeVar(0.2);

	CCScaleTo *actionScale = CCScaleTo::create(1,0);

	SEL_CallFuncN callFunc = callfuncN_selector(Player::clearSkin);
	CCCallFuncN* callback = CCCallFuncN::create(this, callFunc);
	CCFiniteTimeAction* action = CCSequence::create(actionScale, callback, NULL);

	skin->runAction(action);
}

void Player::clearSkin(CCNode *skin) {
	((CCParticleSystem*)skin)->setAutoRemoveOnFinish(true);
	((CCParticleSystem*)skin)->stopSystem();
}

std::vector<CCParticleSystem*>* Player::getNodes() {
	return _skins;
}

void Player::redraw() {
	updateAsterPosition();
}

void Player::checkForRemove() {
	CCParticleSystem* node = _skins->front();
	if (node->getPositionY() <= 0) { isLive = false; }
}

void Player::updateAsterPosition() {
	CCParticleSystem* node = _skins->front();
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	float x = node->getContentSize().width/2 + CCRANDOM_0_1()*(winSize.width - node->getContentSize().width/2);
	float y = winSize.height + node->getContentSize().height;
	node->setPositionX(x);
	node->setPositionY(y);

	float toX = node->getContentSize().width/2 + CCRANDOM_0_1()*(winSize.width - node->getContentSize().width/2);
	float toY = -10;
	moveTo(0, toX, toY);
	setRandomColorForSkin(0);
}

void Player::setRandomColorForSkin(int id) {
	float myRand = CCRANDOM_0_1();
	//CCLog("random %f", myRand);
	ccColor4F color;
	if (myRand > 0 && myRand <= 0.25) {
		color = ccc4f((0.4f + CCRANDOM_0_1()), 0,0,1);
	} else if (myRand > 0.25 && myRand <= 0.5) {
		color = ccc4f(0, (0.4f + CCRANDOM_0_1()),0,1);
	} else if (myRand > 0.5 && myRand <= 0.75) {
		color = ccc4f(0, 0,(0.4f + CCRANDOM_0_1()),1);
	} else {
		color = ccc4f((0.4f + CCRANDOM_0_1()),(0.4f + CCRANDOM_0_1()),(0.4f + CCRANDOM_0_1()),1.0f);
	}
	CCParticleSystem *node = _skins->front();
	node->setStartColor(color);
	node->setStartColorVar(color);
}


void Player::tick(float dt) {
	for (unsigned i = 0; i < _skins->size(); ++i) {
		CCParticleSystem* skin = _skins->at(i);
		if (activeTouches == 1 && i > 0) {
			CCParticleSystem* first = _skins->at(0);
			moveTo(i, first->getPositionX(), first->getPositionY());
			if (checkClonePos(i)) {
				removeSkin(i);
				i--;
				continue;
			}
		}
		CCPoint* target = _targets->at(i);
		CCPoint* velocity = _velocityes->at(i);

		CCPoint pos = skin->getPosition();

		int dx = target->x - pos.x;
		int dy = target->y - pos.y;
		if (abs(dx) <= 5 && abs(dy) <= 5) {
			continue;
		}

		skin->setPositionX((pos.x + velocity->x * dt));
		skin->setPositionY((pos.y + velocity->y * dt));
	}
}

bool Player::checkClonePos(int id) {
	CCParticleSystem *front = _skins->at(0);
	CCParticleSystem *skin = _skins->at(id);

	CCPoint pos = skin->getPosition();
	int dx = front->getPositionX() - pos.x;
	int dy = front->getPositionY() - pos.y;
	if (abs(dx) <= 10 && abs(dy) <= 10) {
		return true;
	}
	return false;
}

void Player::setSkin(int id, CCParticleSystem *item) {
	CCParticleSystem* skin = _skins->at(id);
	skin->setStartColor(item->getStartColor());
	skin->setStartColorVar(item->getStartColorVar());
	skin->setEndColor(item->getEndColor());
	skin->setEndColorVar(item->getEndColorVar());
}

void Player::moveTo(int id, float tx, float ty) {
	CCParticleSystem* skin = _skins->at(id);
	CCPoint* target = _targets->at(id);

	target->x = tx;
	target->y = ty;

	CCPoint pos = skin->getPosition();

	float dx = target->x - pos.x;
	float dy = target->y - pos.y;

	float h = (float) sqrt((double) (dx * dx + dy * dy));
	float vx = dx / h * _speed;
	float vy = dy / h * _speed;

	setVelocity(id, vx, vy);
}

void Player::setVelocity(int id, float vx, float vy) {
	CCPoint *velocity = _velocityes->at(id);

	velocity->x = vx;
	velocity->y = vy;
}

