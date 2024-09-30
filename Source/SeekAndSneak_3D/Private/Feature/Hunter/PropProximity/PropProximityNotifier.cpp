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
	Tolarance = 2.0f;
	Hot = 940.0f;
	Warm = 385.0f;

	Radius = 3000.0f;
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
		float Distance = FVector::Dist(StartPoint, HitResult.ImpactPoint);
		if (Distance >= Hot + Tolarance)
		{
			UKismetSystemLibrary::PrintString(GetPlayer->GetWorld(),TEXT("Hot"), true, true, FLinearColor::Red, 2);
		}
		else if (Distance >= Warm + Tolarance)
		{
			UKismetSystemLibrary::PrintString(GetPlayer->GetWorld(), TEXT("Warm"), true, true, FLinearColor::Yellow, 2);
		}
		else
		{
			UKismetSystemLibrary::PrintString(GetPlayer->GetWorld(), TEXT("COLD"), true, true, FLinearColor::Blue, 2);
		}
		UKismetSystemLibrary::PrintString(GetPlayer->GetWorld(),FString::Printf(TEXT("%f"),Distance),true,true,FLinearColor::Yellow,2);
	}
	//For Debugging
	DrawDebugSphere(GetPlayer->GetWorld(),EndPoint, Radius, 1, FColor::Red, false, 3);
}
