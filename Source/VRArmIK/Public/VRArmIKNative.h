// // Copyright 2019 Synthetic Insights Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "VRArmIKNative.generated.h"

USTRUCT(BlueprintType)
struct VRARMIK_API FArmIKElbowSettings
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ArmIKElborSettings")
	bool bCalcElbowAngle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ArmIKElborSettings")
	bool bClampElbowAngle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ArmIKElborSettings")
	bool bSoftClampElbowAngle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ArmIKElborSettings")
	float MaxAngle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ArmIKElborSettings")
	float MinAngle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ArmIKElborSettings")
	float SoftClampRange;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ArmIKElborSettings")
	float OffsetAngle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ArmIKElborSettings")
	float zWeight;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ArmIKElborSettings")
	float zWeightTop;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ArmIKElborSettings")
	float zWeightBottom;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ArmIKElborSettings")
	float zBorderY;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ArmIKElborSettings")
	float zDistanceStart;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ArmIKElborSettings")
	float xWeight;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ArmIKElborSettings")
	float xDistanceStart;

	FArmIKElbowSettings()
	{
		bCalcElbowAngle = true;
		bClampElbowAngle = true;
		bSoftClampElbowAngle = true;
		MaxAngle = 175.f;
		MinAngle = 13.f;
		SoftClampRange = 10.f;
		OffsetAngle = 135.f;
		zWeight = -60.f;
		zWeightTop = 260.f;
		zWeightBottom = -100.f;
		zBorderY = -0.25f;
		zDistanceStart = 0.6f;
		xWeight = -50.f;
		xDistanceStart = 0.1f;
	}
};

USTRUCT(BlueprintType)
struct VRARMIK_API FArmIKBeforePositioningSettings
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ArmIKBeforePositioningSettings")
	bool bCorrectElbowOutside;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ArmIKBeforePositioningSettings")
	float Weight;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ArmIKBeforePositioningSettings")
	float StartBelowZ;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ArmIKBeforePositioningSettings")
	float StartAboveY;

	FArmIKBeforePositioningSettings()
	{
		bCorrectElbowOutside = true;
		Weight = -0.5f;
		StartBelowZ = 0.4f;
		StartAboveY = 0.1f;
	}
};

USTRUCT(BlueprintType)
struct VRARMIK_API FArmIKElbowCorrectionSettings
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ArmIKElbowCorrectionSettings")
	bool bUseFixedElbowWhenNearShoulder;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ArmIKElbowCorrectionSettings")
	float StartBelowDistance;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ArmIKElbowCorrectionSettings")
	float StartBelowY;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ArmIKElbowCorrectionSettings")
	float Weight;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ArmIKElbowCorrectionSettings")
	FVector LocalElbowPos;

	FArmIKElbowCorrectionSettings()
	{
		bUseFixedElbowWhenNearShoulder = true;
		StartBelowDistance = 0.5f;
		StartBelowY = 0.1f;
		Weight = 2.f;
		LocalElbowPos = FVector(0.3f, -1.f, -2.f);
	}
};

USTRUCT(BlueprintType)
struct VRARMIK_API FArmIKHandSettings
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ArmIKHandSettings")
	bool bUseWristRotation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ArmIKHandSettings")
	bool bRotateElbowWithHandRight;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ArmIKHandSettings")
	bool bRotateElbowWithHandForward;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ArmIKHandSettings")
	float HandDeltaPow;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ArmIKHandSettings")
	float HandDeltaFactor;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ArmIKHandSettings")
	float HandDeltaOffset;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ArmIKHandSettings")
	float HandDeltaForwardPow;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ArmIKHandSettings")
	float HandDeltaForwardFactor;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ArmIKHandSettings")
	float HandDeltaForwardOffset;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ArmIKHandSettings")
	float HandDeltaForwardDeadzone;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ArmIKHandSettings")
	float RotateElbowWithHandDelay;

	FArmIKHandSettings()
	{
		bUseWristRotation = true;
		bRotateElbowWithHandRight = true;
		bRotateElbowWithHandForward = true;
		HandDeltaPow = 1.5;
		HandDeltaFactor = -0.3f;
		HandDeltaOffset = 45.f;
		HandDeltaForwardPow = 2.f;
		HandDeltaForwardFactor = 1.f;
		HandDeltaForwardOffset = 0.f;
		HandDeltaForwardDeadzone = 0.3f;
		RotateElbowWithHandDelay = 0.08f;
	}
};

USTRUCT(BlueprintType)
struct VRARMIK_API FArmIKTransforms
{
	GENERATED_USTRUCT_BODY()

	//Input, also the 'target' in the unity reference
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FArmIKTransforms")
	FTransform Hand;

	//Derived
	UPROPERTY(BlueprintReadOnly, Category = "FArmIKTransforms")
	FTransform Elbow;

	UPROPERTY(BlueprintReadOnly, Category = "FArmIKTransforms")
	FTransform Shoulder;

	float UpperArmLength();
	float LowerArmLength();
	float ArmLength();

	//todo add scaling func/params, needs thought of how to integrate this in ue4 way
};

USTRUCT(BlueprintType)
struct VRARMIK_API FArmIKBodyTransforms
{
	GENERATED_USTRUCT_BODY()

	//Input
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FArmIKTransforms")
	FTransform Origin;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FArmIKTransforms")
	FTransform Head;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FArmIKTransforms")
	FArmIKTransforms Left;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FArmIKTransforms")
	FArmIKTransforms Right;

	//Derived
	UPROPERTY(BlueprintReadOnly, Category = "FArmIKTransforms")
	FTransform Neck;

	//Derived at Calibration
	UPROPERTY(BlueprintReadOnly, Category = "FArmIKTransforms")
	float ArmSpan;

	UPROPERTY(BlueprintReadOnly, Category = "FArmIKTransforms")
	float Height;

	//should only be called during calibration pose (T pose)
	void Calibrate();
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

	//Fetch results	
	void PollArmIKTransforms(FArmIKBodyTransforms& OutTransforms);

	//Calibrate call based on current inputs
	void CalibrateIK();

	//Callback method, if set, will get called when calculate IK finishes
	TFunction<void(const FArmIKBodyTransforms&)> OnIKUpdated;

protected:

	void CalculateIK();
	void UpdateArmAndTurnElbowUp();
	void UpdateUpperArmPosition();
	void CalcElbowInnerAngle();
	void RotateShoulder();
	void CorrectElbowRotation();
	void PositionElbow();
	void CorrectElbowAfterPositioning();
	void RotateElbowWithHandRight();
	void RotateElbowWithHandForward();
	void RotateHand();

	//Data and Settings
	FArmIKBodyTransforms BodyTransforms;
	FArmIKElbowSettings ElbowSettings;
	FArmIKBeforePositioningSettings BeforePositioningSettings;
	FArmIKElbowCorrectionSettings ElbowCorrectionSettings;
	FArmIKHandSettings HandSettings;
};
