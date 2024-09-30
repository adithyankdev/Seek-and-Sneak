// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Interface/Feature/Hunter/PropProximityInterface.h"
#include "PropProximityNotifier.generated.h"

/**
 * 
 */
UCLASS()
class SEEKANDSNEAK_3D_API UPropProximityNotifier : public UObject , public IPropProximityInterface
{
	GENERATED_BODY()

public:

	void Start(ACharacter* Player) override;

private:

	float Hot;
	float Warm;
	float Cool;
	float Cold;
	float Tolarance;



	ACharacter* GetPlayer;

	void CheckProximity();

	//Trace Variables
	bool bIsHit;
	float Radius;
	FHitResult HitResult;
	FVector StartPoint;
	FVector EndPoint;
	FCollisionQueryParams TraceParams;



};
