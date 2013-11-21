/*
 * BaseSkin.h
 *
 *  Created on: Oct 28, 2013
 *      Author: probigi
 */

#ifndef BASESKIN_H_
#define BASESKIN_H_

#include "cocos2d.h"

USING_NS_CC;

class BaseSkin : public CCParticleSystem {
public:
	BaseSkin();
	virtual ~BaseSkin();

	void moveTo(float x, float y);
	void moveTo(CCPoint* point);

private:

	int _speed;
	int _viewSize;
	int _rectSize;



};

#endif /* BASESKIN_H_ */
