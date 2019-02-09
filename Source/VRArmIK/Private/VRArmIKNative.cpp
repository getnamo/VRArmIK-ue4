// // Copyright 2017 Synthetic Insights Ltd. All Rights Reserved.sadasd

#include "VRArmIKNative.h"

//FVRArmIKNative
FVROneArmIK::FVROneArmIK()
{
}

FVROneArmIK::~FVROneArmIK()
{
}

void FVROneArmIK::SetArmData(FArmIKArmData& InArmData)
{
	ArmData = &InArmData;
}

void FVROneArmIK::CalculateIK()
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

void FVROneArmIK::UpdateArmAndTurnElbowUp()
{
	UpdateUpperArmPosition();
	CalcElbowInnerAngle();
	RotateShoulder();
	CorrectElbowRotation();
}

void FVROneArmIK::UpdateUpperArmPosition()
{
	//not used
}

void FVROneArmIK::CalcElbowInnerAngle()
{
	FRotator EulerAngles;
	//todo
}

void FVROneArmIK::RotateShoulder()
{
	FRotator EulerAngles;
	//todo
}

void FVROneArmIK::CorrectElbowRotation()
{
	//todo
}

void FVROneArmIK::PositionElbow()
{
	//todo
}

void FVROneArmIK::CorrectElbowAfterPositioning()
{
	//todo
}

void FVROneArmIK::RotateElbowWithHandRight()
{
	//todo
}

void FVROneArmIK::RotateElbowWithHandForward()
{
	//todo
}

void FVROneArmIK::RotateHand()
{
	//todo
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

	//do ik per arm
	LeftIK.SetArmData(BodyTransforms.Left);
	RightIK.SetArmData(BodyTransforms.Right);

	LeftIK.CalculateIK();
	RightIK.CalculateIK();

	//callback
	if (OnIKUpdated != nullptr)
	{
		OnIKUpdated(BodyTransforms);
	}
}

void FVRArmIKNative::PollArmIKTransforms(FArmIKBodyData& OutTransforms)
{
	OutTransforms = BodyTransforms;
}

void FVRArmIKNative::CalibrateIK()
{
	BodyTransforms.Calibrate();
}
