/*
 * MapObject.cpp
 *
 *  Created on: Oct 25, 2013
 *      Author: probigi
 */

#include "MapObject.h"
#include "GameScene.h"

USING_NS_CC;

MapObject::MapObject() { }
MapObject::~MapObject() {
	delete _skin;
}




void MapObject::create(int type) {
	_type = type;

	_skin = new CCParticleSystem();
	_skin = CCParticleSun::create();
	initOptions();
	setRandomPos();

	_skin->setScale(0);

	_lifeTime = 500;
	_isLive = true;
}

void MapObject::initOptions() {
	_skin->setSpeed(20);
	_skin->setLife(1);
	_skin->setLifeVar(0.5f);


	/*
	switch(_type) {
	case 0:
		_skin->setStartColor(ccc4f(0.0f,1.0f,0.0f,1.0f));
//		_skin->setStartColorVar(ccc4f(0.5f,0.1f,0.0f,0.1f));

		break;
	case 1:
		_skin->setStartColor(ccc4f(1.0f,0.0f,0.0f,1.0f));
//		_skin->setStartColorVar(ccc4f(0.1f,0.5f,0.0f,0.1f));
		break;
	case 2:
		_skin->setStartColor(ccc4f(0.0f,0.0f,1.0f,1.0f));
//		_skin->setStartColorVar(ccc4f(0.0f,0.3f,0.1f,0.1f));
		break;
	}*/
//	_skin->setStartColor(setRandomColor());
	_skin->setStartColor(setRandomColor());
	_skin->setStartColorVar(setRandomColor());

	CCSize *size = new CCSize(20,20);
	_skin->setContentSize(*size);
	_skin->setStartSize(30);
	_skin->setStartSizeVar(30);

	delete size;
}


ccColor4F MapObject::setRandomColor() {
	float myRand = CCRANDOM_0_1();
	//CCLog("random %f", myRand);

	if (myRand > 0 && myRand <= 0.25) {
		return ccc4f((0.4f + CCRANDOM_0_1()), 0,0,1);
	} else if (myRand > 0.25 && myRand <= 0.5) {
		return ccc4f(0, (0.4f + CCRANDOM_0_1()),0,1);
	} else if (myRand > 0.5 && myRand <= 0.75) {
		return ccc4f(0, 0,(0.4f + CCRANDOM_0_1()),1);
	} else {
		return ccc4f((0.4f + CCRANDOM_0_1()),(0.4f + CCRANDOM_0_1()),(0.4f + CCRANDOM_0_1()),1.0f);
	}
}


void MapObject::redraw() {
	_isLive = true;
	_lifeTime = 500;
	initOptions();
	setRandomPos();
	show();
}

void MapObject::setRandomPos() {
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	int x = _skin->getContentSize().width/2 + CCRANDOM_0_1()*(winSize.width - _skin->getContentSize().width/2);
	int y = _skin->getContentSize().height/2 + CCRANDOM_0_1()*(winSize.height - _skin->getContentSize().height/2);
	_skin->setPosition(x,y);
}

CCParticleSystem* MapObject::getNode() {
	return _skin;
}

bool MapObject::isLive() {
	return _isLive;
}

void MapObject::setLive(bool b) {
	_isLive = b;
}

void MapObject::tick(float dt) {
	_lifeTime -= dt;
	if (_lifeTime <= 0 && _isLive) {
		_isLive = false;
		hide();
	}
}

void MapObject::setPosition(float x, float y) {
	_pos.x = x;
	_pos.y = y;
	_skin->setPosition(_pos);
}

void MapObject::show() {
	//CCLog("SHOW ITEM");
	CCScaleTo *actionScale = CCScaleTo::create(1,1);
	_skin->runAction(actionScale);
}

void MapObject::hide() {
	//CCLog("HIDE ITEM");

	_skin->setSpeed(300);
	_skin->setLife(0.2);
	_skin->setLifeVar(0.2);

	CCScaleTo *actionScale = CCScaleTo::create(1,0);

	SEL_CallFuncN callFunc = callfuncN_selector(MapObject::redraw);

	CCCallFuncN* callback = CCCallFuncN::create(this, callFunc);
	CCFiniteTimeAction* action = CCSequence::create(actionScale, callback, NULL);

	_skin->runAction(action);
}
