// Copyright 2019-current Getnamo. All Rights Reserved.

#include "VRArmIKData.h"

//FArmIKArmData
float FArmIKArmData::UpperArmLength()
{
	return (Shoulder.GetLocation() - Elbow.GetLocation()).Size();
}

float FArmIKArmData::LowerArmLength()
{
	return (Elbow.GetLocation() - Hand.GetLocation()).Size();
}

float FArmIKArmData::ArmLength()
{
	return UpperArmLength() + LowerArmLength();
}

//FArmIKBodyData
void FArmIKBodyData::Calibrate()
{
	Calibrated.ArmSpan = (Left.Hand.GetLocation() - Right.Hand.GetLocation()).Size();
	Calibrated.Height = Head.GetLocation().Z;
}