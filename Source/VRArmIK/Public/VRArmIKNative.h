// Copyright 2019 Synthetic Insights Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "VRArmIKData.h"
//#include "VRArmIKNative.generated.h"

//This class handles the actual IK logic per hand
class FVROneArmIK
{
public:
	FVROneArmIK();
	~FVROneArmIK();

	void SetArmData(FArmIKArmData& InArmData);
	void SetIsLeft(bool IsLeft);
	void CalculateIK();

protected:
	void UpdateArmAndTurnElbowUp();
	void UpdateUpperArmPosition();
	void CalcElbowInnerAngle();
	void RotateShoulder();
	float GetElbowTargetAngle();
	void CorrectElbowRotation();
	void RotateElbow(float Angle);
	void PositionElbow();
	void CorrectElbowAfterPositioning();
	void RotateElbowWithHandRight();
	void RotateElbowWithHandForward();
	void RotateHand();

	static float AngleBetween(const FVector& A, const FVector& B);
	static float AngleBetweenWithForwardAxis(const FVector& A, const FVector& B, const FVector& Forward, const FVector& Axis);
	static float CustomAxisAngle(const FVector& A, FVector& Forward, const FVector& Axis);

	//Data and Settings
	FArmIKElbowSettings ElbowSettings;
	FArmIKBeforePositioningSettings BeforePositioningSettings;
	FArmIKElbowCorrectionSettings ElbowCorrectionSettings;
	FArmIKHandSettings HandSettings;
	FRotator NextLowerArmAngle;

	FArmIKArmData* ArmData;
	FTransform Target;

	bool bIsLeft;
	FRotator UpperArmStartRotation;
	FRotator LowerArmStartRotation;
	FRotator WristStartRotation;
	FRotator HandStartRotation;

	float InterpolatedDeltaElbow;
	float InterpolatedDeltaElbowForward;

	FVector ArmDirection;
	FVector UpperArmPos;
	FVector LowerArmPos;
	FVector HandPos;
	FTransform ShoulderAnchor;

	FRotator UpperArmRotation;
	FRotator LowerArmRotation;
	FRotator HandRotation;
};

/**
 * Native C++ class for IK handling, allowing portability. Higher level class uses this for e.g. animbp automation.
 */
class VRARMIK_API FVRArmIKNative
{
public:
	FVRArmIKNative();
	~FVRArmIKNative();

	//Update input
	void UpdateInput(const FTransform& InOrigin, const FTransform& InHandLeft, const FTransform& InHandRight, const FTransform& InHead);

	//Callback method, if set, will get called when calculate IK finishes
	TFunction<void(const FArmIKBodyData&)> OnIKUpdated;

	//Fetch results	
	void PollArmIKTransforms(FArmIKBodyData& OutTransforms);

	//Calibrate call based on current inputs, assumes a T pose
	void CalibrateIK();

protected:
	FArmIKBodyData BodyTransforms;
	FVROneArmIK LeftIK;
	FVROneArmIK RightIK;
};