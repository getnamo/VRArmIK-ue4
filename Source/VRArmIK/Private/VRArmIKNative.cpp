// // Copyright 2017 Synthetic Insights Ltd. All Rights Reserved.sadasd

#include "VRArmIKNative.h"

FVRArmIKNative::FVRArmIKNative()
{
	ArmIKTransforms = MakeShareable(new FArmIKTransforms);
}

FVRArmIKNative::~FVRArmIKNative()
{
}

void FVRArmIKNative::UpdateInput(const FTransform& InOrigin, const FTransform& InHandLeft, const FTransform& InHandRight, const FTransform& InHead)
{
	ArmIKTransforms->Origin = InOrigin;
	ArmIKTransforms->HandLeft = InHandLeft;
	ArmIKTransforms->HandRight = InHandRight;
	ArmIKTransforms->Head = InHead;

	CalculateIK();
}

void FVRArmIKNative::PollArmIKTransforms(FArmIKTransforms& OutTransforms)
{
	OutTransforms = *ArmIKTransforms.Get();
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
			CorrectElbowAfterPositioning();
		if (HandSettings.bRotateElbowWithHandRight)
			RotateElbowWithHandRight();
		if (HandSettings.bRotateElbowWithHandForward)
			RotateElbowWithHandForward();
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
