// // Copyright 2017 Synthetic Insights Ltd. All Rights Reserved.sadasd

#include "VRArmIKNative.h"

//FArmIKTransforms
float FArmIKTransforms::UpperArmLength()
{
	return (Shoulder.GetLocation() - Elbow.GetLocation()).Size();
}

float FArmIKTransforms::LowerArmLength()
{
	return (Elbow.GetLocation() - Hand.GetLocation()).Size();
}

float FArmIKTransforms::ArmLength()
{
	return UpperArmLength() + LowerArmLength();
}

//FArmIKBodyTransforms
void FArmIKBodyTransforms::Calibrate()
{
	ArmSpan = (Left.Hand.GetLocation() - Right.Hand.GetLocation()).Size();
	Height = Head.GetLocation().Z;
}

//FVRArmIKNative
FVRArmIKNative::FVRArmIKNative()
{
}

FVRArmIKNative::~FVRArmIKNative()
{
}

void FVRArmIKNative::UpdateInput(const FTransform& InOrigin, const FTransform& InHandLeft, const FTransform& InHandRight, const FTransform& InHead)
{
	BodyTransforms.Origin = InOrigin;
	BodyTransforms.Left.Hand = InHandLeft;
	BodyTransforms.Right.Hand = InHandRight;
	BodyTransforms.Head = InHead;

	CalculateIK();

	if (OnIKUpdated != nullptr)
	{
		OnIKUpdated(BodyTransforms);
	}
}

void FVRArmIKNative::PollArmIKTransforms(FArmIKBodyTransforms& OutTransforms)
{
	OutTransforms = BodyTransforms;
}

void FVRArmIKNative::CalibrateIK()
{
	BodyTransforms.Calibrate();
}

void FVRArmIKNative::CalculateIK()
{
	UpdateUpperArmPosition();
	CalcElbowInnerAngle();
	RotateShoulder();
	CorrectElbowRotation();
	if (ElbowSettings.bCalcElbowAngle)
	{
		PositionElbow();
		if (ElbowCorrectionSettings.bUseFixedElbowWhenNearShoulder)
		{
			CorrectElbowAfterPositioning();
		}
		if (HandSettings.bRotateElbowWithHandRight)
		{
			RotateElbowWithHandRight();
		}
		if (HandSettings.bRotateElbowWithHandForward)
		{
			RotateElbowWithHandForward();
		}
		RotateHand();
	}
}

void FVRArmIKNative::UpdateArmAndTurnElbowUp()
{
	UpdateUpperArmPosition();
	CalcElbowInnerAngle();
	RotateShoulder();
	CorrectElbowRotation();
}

void FVRArmIKNative::UpdateUpperArmPosition()
{
	//not used
}

void FVRArmIKNative::CalcElbowInnerAngle()
{
	FRotator EulerAngles;
	//todo
}

void FVRArmIKNative::RotateShoulder()
{
	FRotator EulerAngles;
	//todo
}

void FVRArmIKNative::CorrectElbowRotation()
{
	//todo
}

void FVRArmIKNative::PositionElbow()
{
	//todo
}

void FVRArmIKNative::CorrectElbowAfterPositioning()
{
	//todo
}

void FVRArmIKNative::RotateElbowWithHandRight()
{
	//todo
}

void FVRArmIKNative::RotateElbowWithHandForward()
{
	//todo
}

void FVRArmIKNative::RotateHand()
{
	//todo
}



