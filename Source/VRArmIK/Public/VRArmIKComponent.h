// Copyright 2019-current Getnamo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "VRArmIKData.h"
#include "VRArmIKNative.h"
#include "Components/ActorComponent.h"
#include "VRArmIKComponent.generated.h"

/**
Component form of using VArmIK functionality
*/

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FVRArmIKBodySignature, const FArmIKBodyData&, BodyData);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VRARMIK_API UVRArmIKComponent : public UActorComponent
{
	GENERATED_UCLASS_BODY()

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable, Category="VRArmIK Component Events")
	FVRArmIKBodySignature OnIKUpdated;

	UFUNCTION(BlueprintCallable, Category="VRArmIK Functions")
	void UpdateInput(const FTransform& InOrigin, const FTransform& InHandLeft, const FTransform& InHandRight, const FTransform& InHead);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	TSharedPtr<FVRArmIKNative> VRArmIK;
};
