// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerState/InputState/Prop/OnPropClone.h"
#include "GameFramework/Character.h"
#include "PropPlayer/CloneActor/PropCloneActor.h"

OnPropClone::OnPropClone()
{
}

OnPropClone::~OnPropClone()
{
}

void OnPropClone::Begin(ACharacter* Player)
{
	if (PlayerInterface == nullptr)
	{
		if (IPropPlayerInterface* Interface = Cast <IPropPlayerInterface>(Player))
		{
			PlayerInterface.SetObject(Player);
			PlayerInterface.SetInterface(Interface);
		}
		CloneActorClass = APropCloneActor::StaticClass();
	}
	SpawnTransform.SetLocation(Player->GetActorLocation());
	ClonedActor = Player->GetWorld()->SpawnActor<APropCloneActor>(CloneActorClass, SpawnTransform);
	if (ClonedActor)
	{
		ClonedActor->ActorMeshComp->SetStaticMesh(PlayerInterface->GetPlayerMesh());
	}
}

void OnPropClone::End(ACharacter* Player)
{

}
