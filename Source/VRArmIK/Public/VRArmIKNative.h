// // Copyright 2019 Synthetic Insights Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "VRArmIKNative.generated.h"

USTRUCT(BlueprintType)
struct VRARMIK_API FArmIKElbowSettings
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ArmIKElborSettings")
	bool CalcElbowAngle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ArmIKElborSettings")
	bool ClampElbowAngle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ArmIKElborSettings")
	bool SoftClampElbowAngle;

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
		CalcElbowAngle = true;
		ClampElbowAngle = true;
		SoftClampElbowAngle = true;
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

/**
 * Native C++ class for IK handling, allowing portability
 */
class VRARMIK_API FVRArmIKNative
{
public:
	FVRArmIKNative();
	~FVRArmIKNative();
};
