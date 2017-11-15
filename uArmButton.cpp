/**
  ******************************************************************************
  * @file	uArmButton.cpp
  * @author	David.Long
  * @email	xiaokun.long@ufactory.cc
  * @date	2016-10-17
  ******************************************************************************
  */

#include "uArmButton.h"
#define XKNMC

uArmButton::uArmButton()
{
#ifndef XKNMC
	mPin = 0xff;
	mState = INIT;
	mEvent = EVENT_NONE;
#endif
}

void uArmButton::setPin(unsigned char pin)
{
#ifndef XKNMC
	mPin = pin;
	mState = IDLE;
#endif
}

bool uArmButton::clicked()
{
#ifndef XKNMC
	return (mEvent == EVENT_CLICK);
#endif
}

bool uArmButton::longPressed()
{
#ifndef XKNMC
	return (mEvent == EVENT_LONG_PRESS);
#endif
}

bool uArmButton::isPressed()
{
#ifndef XKNMC
	if (!digitalRead(mPin))
		return true;
#endif
	return false;
}

void uArmButton::clearEvent()
{
	mEvent = EVENT_NONE;
}

void uArmButton::tick()
{
#ifndef XKNMC
	switch (mState)
	{
	case IDLE:
		if (isPressed())
		{
			mTicks = 0;
			mState = HALF_PRESSED;
		}
		break;

	case HALF_PRESSED:
		if (isPressed())
		{
			gBuzzer.buzz(4000, 100);
			mState = PRESSED;
		}
		else
		{
			mState = IDLE;
		}
		break;

	case PRESSED:
		if (isPressed())
		{

			mTicks++;
		}
		else
		{
			mState = RELEASE;
		}
		break;

	case RELEASE:

		if (mTicks >= (1000/TICK_INTERVAL))
		{
			mEvent = EVENT_LONG_PRESS;
		}
		else
		{
			mEvent = EVENT_CLICK;
		}

		mTicks = 0;
		mState = IDLE;
		break;

	default:
		break;
	}
#endif //XKNMC
}
