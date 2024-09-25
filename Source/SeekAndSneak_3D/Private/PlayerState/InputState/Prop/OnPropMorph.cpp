// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerState/InputState/Prop/OnPropMorph.h"
#include "GameFramework/Character.h"
#include "Engine/StaticMesh.h"

#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"

OnPropMorph::OnPropMorph()
{
	TraceRadius = 50.0f;
}

OnPropMorph::~OnPropMorph()
{
}

void OnPropMorph::OnBegin(ACharacter* Player)
{
	if (PlayerInterface == nullptr)
	{
		if (IPropPlayerInterface* Interface = Cast<IPropPlayerInterface>(Player))
		{
			PlayerInterface.SetObject(Cast<UObject>(Player));
			PlayerInterface.SetInterface(Interface);
		}
	}

	Start = Player->GetActorLocation();
	Start.Z += 15.0f;
	End = Start;

	IsTraceHit = Player->GetWorld()->SweepSingleByChannel(TraceHitResult, Start, End, FQuat::Identity, ECollisionChannel::ECC_Visibility, FCollisionShape::MakeSphere(TraceRadius), TraceCollisionParams);
	DrawDebugSphere(Player->GetWorld(), End, TraceRadius, 12, IsTraceHit ? FColor::Red : FColor::Green, false, 5);

	UKismetSystemLibrary::PrintString(Player->GetWorld(), TEXT("Morphed"), true, true, FLinearColor::Blue);
}

void OnPropMorph::OnEnd(ACharacter* Player)
{
	
}
