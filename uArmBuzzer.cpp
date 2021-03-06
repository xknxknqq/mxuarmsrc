/**
  ******************************************************************************
  * @file	uArmBuzzer.cpp
  * @author	David.Long
  * @email	xiaokun.long@ufactory.cc
  * @date	2016-09-30
  * @license GNU
  * copyright(c) 2016 UFactory Team. All right reserved
  ******************************************************************************
  */

#include "uArmBuzzer.h"

#define XKNMC

uArmBuzzer gBuzzer;



uArmBuzzer::uArmBuzzer()
{
  mOn = false;
}

void uArmBuzzer::setPin(unsigned char pin)
{
  mPin = pin;
}

void uArmBuzzer::buzz(unsigned int frequency, unsigned long duration)
{
#ifndef XKNMC
	if (duration <= 0)
		return;

  mOn = true;
  pinMode(mPin, OUTPUT);
  mDuration = duration;
  mStartTime = millis();
  tone(mPin, frequency, duration);
	//tone(mPin, frequency, duration);
#endif //XKNMC

}


void uArmBuzzer::stop()
{
	noTone(mPin);
}


void uArmBuzzer::run()
{
#ifndef XKNMC

  if (mOn && (long)((millis() - mStartTime)) >= mDuration)
  {
    noTone(mPin);
    mOn = false;
  }
#endif
}

bool uArmBuzzer::on()
{
  return mOn;
}
