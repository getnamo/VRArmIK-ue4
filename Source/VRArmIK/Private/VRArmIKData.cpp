// Copyright 2019 Synthetic Insights Ltd. All Rights Reserved.
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
	ArmSpan = (Left.Hand.GetLocation() - Right.Hand.GetLocation()).Size();
	Height = Head.GetLocation().Z;
}