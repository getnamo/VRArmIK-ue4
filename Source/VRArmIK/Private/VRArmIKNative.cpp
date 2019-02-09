// // Copyright 2017 Synthetic Insights Ltd. All Rights Reserved.sadasd

#include "VRArmIKNative.h"

//FVRArmIKNative
FVROneArmIK::FVROneArmIK()
{
	bIsLeft = true;
	UpperArmStartRotation = FRotator(0.f);
	LowerArmStartRotation = FRotator(0.f);
	WristStartRotation = FRotator(0.f);
	HandStartRotation = FRotator(0.f);
}

FVROneArmIK::~FVROneArmIK()
{
}

void FVROneArmIK::SetArmData(FArmIKArmData& InArmData)
{
	ArmData = &InArmData;
	Target = InArmData.Hand;
	ArmDirection = bIsLeft ? FVector(0, -1.f, 0) : FVector(0, 1.f, 0);
	UpperArmPos = InArmData.Shoulder.GetLocation();
	LowerArmPos = InArmData.Elbow.GetLocation();
	HandPos = InArmData.Hand.GetLocation();
	ShoulderAnchor = InArmData.Shoulder;

	//optimization: use quaternions only
	UpperArmRotation = (InArmData.Shoulder.GetRotation() * UpperArmStartRotation.Quaternion().Inverse()).Rotator();
	LowerArmRotation = (InArmData.Elbow.GetRotation() * LowerArmStartRotation.Quaternion().Inverse()).Rotator();
	HandRotation = (InArmData.Hand.GetRotation() * HandStartRotation.Quaternion().Inverse()).Rotator();
}

void FVROneArmIK::SetIsLeft(bool IsLeft)
{
	bIsLeft = IsLeft;
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
	
	float TargetShoulderDistance = (Target.GetLocation() - UpperArmPos).Size();
	float InnerAngle;

	if (TargetShoulderDistance > ArmData->ArmLength())
	{
		InnerAngle = 0.f;
	}
	else
	{
		InnerAngle =	FMath::RadiansToDegrees(
							FMath::Acos(
								FMath::Clamp(
									(FMath::Pow(ArmData->UpperArmLength(), 2.f)
									+ FMath::Pow(ArmData->LowerArmLength(), 2.f)
									- FMath::Pow(TargetShoulderDistance, 2.f)) / 
										(2.f * ArmData->UpperArmLength() * ArmData->LowerArmLength()), -1.f, 1.f)
							)
						);

		if (bIsLeft)
		{
			InnerAngle = 180.f - InnerAngle;
		}
		else
		{
			InnerAngle = 180.f + InnerAngle;
		}
		if (FMath::IsNaN(InnerAngle))
		{
			InnerAngle = 180.f;
		}
	}
	EulerAngles.Yaw = InnerAngle;
	NextLowerArmAngle = EulerAngles;
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
	LeftIK.SetIsLeft(true);
	RightIK.SetIsLeft(false);
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

	//do IK per arm
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
