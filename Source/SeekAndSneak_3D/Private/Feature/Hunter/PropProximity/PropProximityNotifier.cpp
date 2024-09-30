// Fill out your copyright notice in the Description page of Project Settings.


#include "Feature/Hunter/PropProximity/PropProximityNotifier.h"
#include "GameFramework/Character.h"
#include "PropPlayer/PropPlayer.h"
#include "Runtime/Engine/Public/TimerManager.h"

#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"

void UPropProximityNotifier::Start(ACharacter* Player)
{
	GetPlayer = Player;

	//Setting Up The Initial Value
	Radius = 1200.0f;
	TraceParams.AddIgnoredActor(Player);

	FTimerHandle ProximityTimer;
	Player->GetWorld()->GetTimerManager().SetTimer(ProximityTimer, this, &UPropProximityNotifier::CheckProximity, 4,true);
}

void UPropProximityNotifier::CheckProximity()
{
	StartPoint = GetPlayer->GetActorLocation();
	EndPoint = StartPoint;

	bIsHit = GetPlayer->GetWorld()->SweepSingleByChannel(HitResult, StartPoint, EndPoint,
		                                                FQuat::Identity, ECC_Visibility,
		                                                FCollisionShape::MakeSphere(Radius),TraceParams);

	if (bIsHit && HitResult.GetActor()->IsA(APropPlayer::StaticClass()))
	{
		float D = FVector::Dist(StartPoint, HitResult.ImpactPoint);
		UKismetSystemLibrary::PrintString(GetPlayer->GetWorld(),FString::Printf(TEXT("%f"),D),true,true,FLinearColor::Yellow,2);
	}
	//For Debugging
	DrawDebugSphere(GetPlayer->GetWorld(),EndPoint, Radius, 1, FColor::Green, false, 3);
}
