// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerState/InputState/Prop/OnPropMorph.h"
#include "GameFramework/Character.h"
#include "Engine/StaticMesh.h"
#include "Engine/StaticMeshActor.h"
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
	/* It Only Run Once*/
	if (PlayerInterface == nullptr)
	{
		if (IPropPlayerInterface* Interface = Cast<IPropPlayerInterface>(Player))
		{
			//Storing Player And Interface
			PlayerInterface.SetObject(Cast<UObject>(Player));
			PlayerInterface.SetInterface(Interface);
		}
		//Since The If Only Works At Once -- Setting The Self Ignorance
		TraceCollisionParams.AddIgnoredActor(Player);
	}
	CastLineTrace(Player);
	
}

void OnPropMorph::OnEnd(ACharacter* Player)
{
	
}

/*-----Helper Functions-----*/

void OnPropMorph::CastLineTrace(ACharacter* Player)
{
	Start = Player->GetActorLocation();
	/*Setting A Little High So Colliding With Ground Floor Avoided*/
	Start.Z += 20.0f;
	End = Start;

	IsTraceHit = Player->GetWorld()->SweepSingleByChannel(TraceHitResult, Start, End, FQuat::Identity, ECollisionChannel::ECC_Visibility, FCollisionShape::MakeSphere(TraceRadius), TraceCollisionParams);
	DrawDebugSphere(Player->GetWorld(), End, TraceRadius, 12, IsTraceHit ? FColor::Red : FColor::Green, false, 5);

	if (IsTraceHit && TraceHitResult.GetActor()->IsA(AStaticMeshActor::StaticClass()))
	{
	   SetNewMesh(Player, TraceHitResult);
	}
}

void OnPropMorph::SetNewMesh(ACharacter* Player, FHitResult& HitResult)
{
	/*Casting To StaticMeshComponent For Retreving The Mesh*/
	if (UStaticMeshComponent* StaticMeshComponent = Cast <UStaticMeshComponent>(HitResult.GetComponent()))
	{
		if (StaticMeshComponent->ComponentHasTag("Sample"))
		{
			PlayerInterface->SetPlayerMesh(StaticMeshComponent->GetStaticMesh());
		}
		
	}
}
