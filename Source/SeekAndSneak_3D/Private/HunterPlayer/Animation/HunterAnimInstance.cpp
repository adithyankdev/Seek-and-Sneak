// Fill out your copyright notice in the Description page of Project Settings.


#include "HunterPlayer/Animation/HunterAnimInstance.h"
#include "GameFramework/Character.h"

void UHunterAnimInstance::NativeInitializeAnimation()
{
	 OwnerCharacter = Cast <ACharacter>(GetOwningActor());
}

void UHunterAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	if (OwnerCharacter)
	{
		Velocity = OwnerCharacter->GetVelocity();
		Speed = Velocity.Size();
		Direction = CalculateDirection(Velocity, OwnerCharacter->GetActorRotation());
	}
}
