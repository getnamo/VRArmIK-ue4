// Copyright 2019-current Getnamo. All Rights Reserved.

#include "VRArmIKComponent.h"
#include "SIOJConvert.h"
#include "Runtime/Core/Public/Misc/Paths.h"
#include "Runtime/Core/Public/Misc/FileHelper.h"

UVRArmIKComponent::UVRArmIKComponent(const FObjectInitializer &init) : UActorComponent(init)
{
	PrimaryComponentTick.bCanEverTick = false;
	VRArmIK = MakeShareable(new FVRArmIKNative());
	DefaultsJsonFile = TEXT("VRArmIKCalibration.json");
}


void UVRArmIKComponent::BeginPlay()
{
	Super::BeginPlay();
	VRArmIK->OnIKUpdated = [this](const FArmIKBodyData& Data)
	{
		OnIKUpdated.Broadcast(Data);
	};

	const FString SavedDir = FPaths::ProjectSavedDir();
	const FString FullPath = SavedDir + DefaultsJsonFile;

	//load defaults if they exist
	FArmIKBodyCalibration LoadedBodyCalibration;

	bool bDidLoad = USIOJConvert::JsonFileToUStruct(FullPath, FArmIKBodyCalibration::StaticStruct(), &LoadedBodyCalibration);

	if (bDidLoad)
	{
		VRArmIK->CalibrateFromSaved(LoadedBodyCalibration);
	}
}

void UVRArmIKComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UVRArmIKComponent::UpdateInput(const FTransform& InOrigin, const FTransform& InHandLeft, const FTransform& InHandRight, const FTransform& InHead)
{
	VRArmIK->UpdateInput(InOrigin, InHandLeft, InHandRight, InHead);
}

void UVRArmIKComponent::CalibrateAtTPose()
{
	VRArmIK->CalibrateAtTPose();

	//save calibration
	const FString SavedDir = FPaths::ProjectSavedDir();
	const FString FullPath = SavedDir + DefaultsJsonFile;

	FArmIKBodyData CalibratedBodyData;
	VRArmIK->PollArmIKTransforms(CalibratedBodyData);

	USIOJConvert::ToJsonFile(FullPath, FArmIKBodyCalibration::StaticStruct(), &(CalibratedBodyData.Calibrated));
}

void UVRArmIKComponent::PollLatestData(FArmIKBodyData& OutBodyData)
{
	VRArmIK->PollArmIKTransforms(OutBodyData);
}

