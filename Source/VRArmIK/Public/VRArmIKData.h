// Copyright 2019-current Getnamo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "VRArmIKData.generated.h"

USTRUCT(BlueprintType)
struct VRARMIK_API FArmIKElbowSettings
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ArmIKElbowSettings")
	bool bCalcElbowAngle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ArmIKElbowSettings")
	bool bClampElbowAngle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ArmIKElbowSettings")
	bool bSoftClampElbowAngle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ArmIKElbowSettings")
	float MaxAngle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ArmIKElbowSettings")
	float MinAngle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ArmIKElbowSettings")
	float SoftClampRange;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ArmIKElbowSettings")
	float OffsetAngle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ArmIKElbowSettings")
	float yWeight;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ArmIKElbowSettings")
	float zWeightTop;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ArmIKElbowSettings")
	float zWeightBottom;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ArmIKElbowSettings")
	float zBorderY;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ArmIKElbowSettings")
	float zDistanceStart;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ArmIKElbowSettings")
	float xWeight;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ArmIKElbowSettings")
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
		yWeight = -60.f;
		zWeightTop = 260.f;
		zWeightBottom = -100.f;
		zBorderY = -25.f;
		zDistanceStart = 60.f;
		xWeight = -50.f;
		xDistanceStart = 10.f;
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
		StartBelowZ = 40.f;
		StartAboveY = 10.f;
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
		StartBelowDistance = 50.f;
		StartBelowY = 10.f;
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
		HandDeltaForwardDeadzone = 30.f;
		RotateElbowWithHandDelay = 0.08f;
	}
};

USTRUCT(BlueprintType)
struct VRARMIK_API FArmIKArmData
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
struct VRARMIK_API FArmIKBodyCalibration
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "FArmIKBodyData")
	float ShoulderWidth;

	//Derived at Calibration
	UPROPERTY(BlueprintReadOnly, Category = "FArmIKBodyData")
	float ArmSpan;

	UPROPERTY(BlueprintReadOnly, Category = "FArmIKBodyData")
	float Height;

	FArmIKBodyCalibration()
	{
		//defaults in cm, some will be overwritten by calibrate
		ArmSpan = 139.f;
		Height = 170.f;
		ShoulderWidth = 31.f;
	}
};

USTRUCT(BlueprintType)
struct VRARMIK_API FArmIKBodyData
{
	GENERATED_USTRUCT_BODY()

	//Input
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FArmIKBodyData")
	FTransform Origin;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FArmIKBodyData")
	FTransform Head;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FArmIKBodyData")
	FArmIKArmData Left;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FArmIKBodyData")
	FArmIKArmData Right;

	UPROPERTY(BlueprintReadOnly, Category = "FArmIKBodyData")
	FArmIKBodyCalibration Calibrated;

	//Derived
	UPROPERTY(BlueprintReadOnly, Category = "FArmIKBodyData")
	FTransform Neck;

	//should only be called during calibration pose (T pose)
	void Calibrate();
};