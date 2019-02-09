// // Copyright 2019-Current Synthetic Insights Ltd. All Rights Reserved.

#include "VRArmIKComponent.h"

UVRArmIKComponent::UVRArmIKComponent(const FObjectInitializer &init) : UActorComponent(init)
{
	PrimaryComponentTick.bCanEverTick = false;
	VRArmIK = MakeShareable(new FVRArmIKNative());
}


void UVRArmIKComponent::BeginPlay()
{
	Super::BeginPlay();
	VRArmIK->OnIKUpdated = [this](const FArmIKBodyData& Data)
	{
		OnIKUpdated.Broadcast(Data);
	};
}

void UVRArmIKComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UVRArmIKComponent::UpdateInput(const FTransform& InOrigin, const FTransform& InHandLeft, const FTransform& InHandRight, const FTransform& InHead)
{
	VRArmIK->UpdateInput(InOrigin, InHandLeft, InHandRight, InHead);
}

