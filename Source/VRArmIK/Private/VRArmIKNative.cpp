// Copyright 2019-current Getnamo. All Rights Reserved.

#include "VRArmIKNative.h"
#include "App.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"

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
									- FMath::Pow(TargetShoulderDistance, 2.f))
									/ (2.f * ArmData->UpperArmLength() * ArmData->LowerArmLength())
								, -1.f, 1.f)
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
	FVector TargetShoulderDirection = (Target.GetLocation() - UpperArmPos);
	TargetShoulderDirection.Normalize();
	float TargetShoulderDistance = (Target.GetLocation() - UpperArmPos).Size();

	EulerAngles.Yaw =	FMath::RadiansToDegrees(
							(bIsLeft ? -1.f : 1.f) *
							FMath::Acos(
								FMath::Clamp(
									(FMath::Pow(TargetShoulderDistance, 2.f)
									+ FMath::Pow(ArmData->UpperArmLength(), 2.f)
									- FMath::Pow(ArmData->LowerArmLength(), 2.f))
									/ (2.f * TargetShoulderDistance * ArmData->UpperArmLength())
								, -1.f, 1.f)
							)
						);

	if (FMath::IsNaN(EulerAngles.Yaw))
	{
		EulerAngles.Yaw = 0.f;
	}
		
	UpperArmRotation = UKismetMathLibrary::FindLookAtRotation(ArmDirection, TargetShoulderDirection);	// FRotationMatrix::MakeFromX(TargetShoulderDirection - ArmDirection).Rotator();
	ArmData->Shoulder.SetRotation(FQuat(LowerArmRotation.Quaternion() * FVector(0, 0, 1.f), FMath::DegreesToRadians(EulerAngles.Yaw)) * ArmData->Shoulder.GetRotation());	//NB: changed degrees to rad
	LowerArmRotation = (UpperArmRotation.Quaternion() * NextLowerArmAngle.Quaternion() * LowerArmStartRotation.Quaternion()).Rotator();
}

float FVROneArmIK::GetElbowTargetAngle()
{
	FVector LocalHandPosNormalized = ShoulderAnchor.InverseTransformPosition(HandPos) / ArmData->ArmLength();

	//angle from Y
	float Angle = ElbowSettings.yWeight * LocalHandPosNormalized.Y + ElbowSettings.OffsetAngle;

	//angle from Z
	if (LocalHandPosNormalized.Y > 0)
	{
		Angle += ElbowSettings.zWeightTop * (
			FMath::Max(ElbowSettings.zDistanceStart - LocalHandPosNormalized.Z, 0.f) *
			FMath::Max(LocalHandPosNormalized.Y, 0.F));
	}
	else
	{
		Angle += ElbowSettings.zWeightBottom * (
			FMath::Max(ElbowSettings.zDistanceStart - LocalHandPosNormalized.Z, 0.f) *
			FMath::Max(-LocalHandPosNormalized.Y, 0.F));
	}

	//angle from x
	Angle += ElbowSettings.xWeight * FMath::Max(
		LocalHandPosNormalized.X * (bIsLeft ? 1.f : -1.f) + ElbowSettings.xDistanceStart, 0.f);

	if (ElbowSettings.bClampElbowAngle)
	{
		if (ElbowSettings.bSoftClampElbowAngle)
		{
			if (Angle < ElbowSettings.MinAngle + ElbowSettings.SoftClampRange)
			{
				float a = ElbowSettings.MinAngle + ElbowSettings.SoftClampRange - Angle;
				Angle = ElbowSettings.MinAngle + ElbowSettings.SoftClampRange * (1.f - FMath::Loge(1.f + a) * 3.f);
			}
		}
		else
		{
			Angle = FMath::Clamp(Angle, ElbowSettings.MinAngle, ElbowSettings.MaxAngle);
		}
	}

	return Angle;
}

void FVROneArmIK::CorrectElbowRotation()
{
	const FArmIKBeforePositioningSettings& s = BeforePositioningSettings;

	FVector LocalTargetPos = ShoulderAnchor.InverseTransformPosition(Target.GetLocation()) / ArmData->ArmLength();
	float ElbowOutsideFactor = FMath::Clamp(
		FMath::Clamp((s.StartBelowZ - LocalTargetPos.Z) / FMath::Abs(s.StartBelowZ) * 0.5f, 0.f, 1.f) *
		FMath::Clamp((LocalTargetPos.Y - s.StartAboveY) / FMath::Abs(s.StartAboveY), 0.f, 1.f) *
		FMath::Clamp( 1.f - LocalTargetPos.X * (bIsLeft ? -1.f: 1.f), 0.f, 1.f)
		, 0.f, 1.f) * s.Weight;

	FVector ShoulderHandDirection = (UpperArmPos - HandPos);
	ShoulderHandDirection.Normalize();
	FVector TargetDir = ArmData->Shoulder.GetRotation() * (FVector(0, 0, 1) + (s.bCorrectElbowOutside ? (ArmDirection + FVector(1, 0, 0) * -0.2f) * ElbowOutsideFactor : FVector(0)));
	FVector Cross = FVector::CrossProduct(ShoulderHandDirection, TargetDir * 100000.f);	//x100 of unity
	
	FVector UpperArmUp = UpperArmRotation.Quaternion() * FVector(0, 0, 1);

	float ElbowTargetUp = FVector::DotProduct(UpperArmUp, TargetDir);
	float ElbowAngle = AngleBetween(Cross, UpperArmUp) + (bIsLeft ? 0.f : 180.f);
	FQuat Rotation = FQuat(ShoulderHandDirection, FMath::DegreesToRadians(ElbowAngle * FMath::Sign(ElbowTargetUp)));
	ArmData->Shoulder.SetRotation(Rotation * ArmData->Shoulder.GetRotation());
}

//reduces calculation problems when hand is moving around shoulder XZ coordinates -> forces elbow to be outside of body
void FVROneArmIK::CorrectElbowAfterPositioning()
{
	const FArmIKElbowCorrectionSettings& s = ElbowCorrectionSettings;
	FVector LocalTargetPos = ShoulderAnchor.InverseTransformPosition(Target.GetLocation()) / ArmData->ArmLength();
	FVector ShoulderHandDirection = (UpperArmPos - HandPos);
	ShoulderHandDirection.Normalize();
	FVector ElbowPos = s.LocalElbowPos;

	if (bIsLeft)
	{
		ElbowPos.X *= -1.f;
	}

	FVector TargetDir = ArmData->Shoulder.GetRotation() * ElbowPos.GetSafeNormal();
	FVector Cross = FVector::CrossProduct(ShoulderHandDirection, TargetDir);

	FVector UpperArmUp = UpperArmRotation.Quaternion() * FVector(0, 0, 1);

	FVector Distance = Target.GetLocation() - UpperArmPos;
	Distance = Distance.Size() * ArmData->Shoulder.InverseTransformVectorNoScale(Distance / Distance.Size());

	float Weight = FMath::Clamp(
		FMath::Clamp((s.StartBelowDistance - FVector(Distance.X, 0, Distance.Z).Size() / ArmData->ArmLength()) / s.StartBelowDistance, 0.f, 1.f) * 
		s.Weight +
		FMath::Clamp((-Distance.Z + 0.1f) * 3.f, 0.f, 1.f) * 
		FMath::Clamp((s.StartBelowY - LocalTargetPos.Y) / s.StartBelowY, 0.f, 1.f)
		, 0.f, 1.f);

	float ElbowTargetUp = UpperArmUp | TargetDir;
	float ElbowAngle2 = AngleBetween(Cross, UpperArmUp) + (bIsLeft ? 0.f : 180.f);

	FQuat Rotation = FQuat(ShoulderHandDirection, ElbowAngle2 * ToSignedEulerAngle(FMath::Sign(ElbowTargetUp)) * FMath::Clamp(Weight, 0.f, 1.f));
	ArmData->Shoulder.SetRotation(Rotation * ArmData->Shoulder.GetRotation());
}

void FVROneArmIK::RotateElbow(float Angle)
{
	FVector ShoulderHandDirection = (UpperArmPos - HandPos);
	ShoulderHandDirection.Normalize();

	FQuat Rotation = FQuat(ShoulderHandDirection, FMath::DegreesToRadians(Angle));
	UpperArmRotation = (Rotation * UpperArmRotation.Quaternion()).Rotator();
}

void FVROneArmIK::PositionElbow()
{
	float TargetElbowAngle = GetElbowTargetAngle();
	RotateElbow(TargetElbowAngle);
}



void FVROneArmIK::RotateElbowWithHandRight()
{
	const FArmIKHandSettings& s = HandSettings;
	FVector HandUpVec = Target.GetRotation().GetUpVector();
	float ForwardAngle = AngleBetweenWithForwardAxis(
		LowerArmRotation.Quaternion() * FVector::RightVector, 
		Target.GetRotation() * FVector::RightVector,
		LowerArmRotation.Quaternion() * FVector::UpVector,
		LowerArmRotation.Quaternion() * FVector::ForwardVector);

	// todo reduce influence if hand local forward rotation is high (hand tilted inside)
	FQuat HandForwardRotation = FQuat(LowerArmRotation.Quaternion() * FVector::ForwardVector, FMath::DegreesToRadians(-ForwardAngle));	//should this not have deg2rad?
	HandUpVec = HandForwardRotation * HandUpVec;

	float ElbowTargetAngle = AngleBetweenWithForwardAxis(
		LowerArmRotation.Quaternion() * FVector::UpVector,
		HandUpVec,
		LowerArmRotation.Quaternion() * FVector::ForwardVector,
		LowerArmRotation.Quaternion() * ArmDirection);

	float DeltaElbow = (ElbowTargetAngle + (bIsLeft ? -s.HandDeltaOffset : s.HandDeltaOffset)) / 180.f;

	DeltaElbow = FMath::Sign(DeltaElbow) * FMath::Pow(FMath::Abs(DeltaElbow), s.HandDeltaPow) * 180.f * s.HandDeltaFactor;
	
	//todo: feed in deltatime
	float DeltaTime = FApp::GetDeltaTime();
	InterpolatedDeltaElbow = FMath::Lerp(InterpolatedDeltaElbow, DeltaElbow, DeltaTime / s.RotateElbowWithHandDelay);
	RotateElbow(InterpolatedDeltaElbow);
}

void FVROneArmIK::RotateElbowWithHandForward()
{
	const FArmIKHandSettings& s = HandSettings;
	FVector HandRightVec = Target.GetRotation() * ArmDirection;

	float ElbowTargetAngleForward = AngleBetweenWithForwardAxis(
		LowerArmRotation.Quaternion() * ArmDirection,
		HandRightVec,
		LowerArmRotation.Quaternion().GetUpVector(),
		LowerArmRotation.Quaternion().GetForwardVector()
	);

	float DeltaElbowForward = (ElbowTargetAngleForward + (bIsLeft ? -s.HandDeltaForwardOffset : s.HandDeltaForwardOffset)) / 180.f;

	if (FMath::Abs(DeltaElbowForward) < s.HandDeltaForwardDeadzone)
	{
		DeltaElbowForward = 0.f;
	}
	else
	{
		DeltaElbowForward = (DeltaElbowForward - FMath::Sign(DeltaElbowForward) * s.HandDeltaForwardDeadzone) / (1.f - s.HandDeltaForwardDeadzone);
	}

	//todo: feed in deltatime
	float DeltaTime = FApp::GetDeltaTime();
	DeltaElbowForward = FMath::Sign(DeltaElbowForward) * FMath::Pow(FMath::Abs(DeltaElbowForward), s.HandDeltaForwardPow) * 180.f;
	InterpolatedDeltaElbowForward = FMath::Lerp(InterpolatedDeltaElbowForward, DeltaElbowForward, DeltaTime / s.RotateElbowWithHandDelay);

	float SignedInterpolated = ToSignedEulerAngle(InterpolatedDeltaElbowForward);
	RotateElbow(SignedInterpolated * s.HandDeltaForwardFactor);
}

void FVROneArmIK::RotateHand()
{
	if (HandSettings.bUseWristRotation)
	{
		FVector HandUpVec = Target.GetRotation().GetUpVector();
		float ForwardAngle = AngleBetweenWithForwardAxis(
			LowerArmRotation.Quaternion().GetRightVector(),
			Target.GetRotation().GetRightVector(),
			LowerArmRotation.Quaternion().GetUpVector(),
			LowerArmRotation.Quaternion().GetForwardVector()
		);

		// todo reduce influence if hand local forward rotation is high (hand tilted inside)
		FQuat HandForwardRotation = FQuat(LowerArmRotation.Quaternion().GetForwardVector(), -ForwardAngle);
		HandUpVec = HandForwardRotation * HandUpVec;

		float ElbowTargetAngle = AngleBetweenWithForwardAxis(
			LowerArmRotation.Quaternion().GetUpVector(),
			HandUpVec,
			LowerArmRotation.Quaternion().GetForwardVector(),
			LowerArmRotation.Quaternion() * ArmDirection
		);

		ElbowTargetAngle = FMath::Clamp(ElbowTargetAngle, -90.f, 90.f);
		
		/* this part is ignored for now
		if (arm.wrist1 != null)
			setWrist1Rotation(Quaternion.AngleAxis(elbowTargetAngle * .3f, lowerArmRotation * armDirection) * lowerArmRotation);
		if (arm.wrist2 != null)
			setWrist2Rotation(Quaternion.AngleAxis(elbowTargetAngle * .8f, lowerArmRotation * armDirection) * lowerArmRotation);
		*/
	}
	
	HandRotation = Target.Rotator();
}

float FVROneArmIK::AngleBetween(const FVector& A, const FVector& B)
{
	return FMath::RadiansToDegrees(acosf(A | B));
}

float FVROneArmIK::AngleBetweenWithForwardAxis(const FVector& A, const FVector& B, const FVector& Forward, const FVector& Axis)
{
	FVector TempForward = Forward;
	float AngleA = CustomAxisAngle(A, TempForward, Axis);
	float AngleB = CustomAxisAngle(B, TempForward, Axis);
	
	return FMath::FindDeltaAngleDegrees(AngleA, AngleB);
}

float FVROneArmIK::CustomAxisAngle(const FVector& A, FVector& Forward, const FVector& Axis)
{
	FVector Right = FVector::CrossProduct(Axis, Forward);
	Forward = FVector::CrossProduct(Right, Axis);
	return FMath::Atan2(A | Right, FMath::RadiansToDegrees(A | Forward)); //not sure if we need that conversion vs unity
}

float FVROneArmIK::ToSignedEulerAngle(float InFloat)
{
	float result = ToPositiveEulerAngle(InFloat);
	if (result > 180.f) 
	{
		result = result - 360.f;
	}
	return result;
}

float FVROneArmIK::ToPositiveEulerAngle(float InFloat)
{
	return FMath::Fmod(FMath::Fmod(InFloat, 360.f) + 360.f, 360.f);
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

void FVRArmIKNative::CalibrateAtTPose()
{
	BodyTransforms.Calibrate();
}

void FVRArmIKNative::CalibrateFromSaved(const FArmIKBodyCalibration& SavedData)
{
	BodyTransforms.Calibrated = SavedData;
}