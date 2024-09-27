// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerState/InputState/InputStateAbstract.h"
#include "Interface/Player/HunterPlayerInterface.h"

/**
 * 
 */
class SEEKANDSNEAK_3D_API OnPlayerFire : public InputStateAbstract
{
public:
	OnPlayerFire();
	~OnPlayerFire();

	void Begin(ACharacter* Player)override;
	void End(ACharacter* Player)override;

private:

	float FireIntervalTime;

	//Weapon Variables
	float ShootingRange;

	//Caching Player Weapon Mesh
	USkeletalMeshComponent* WeaponMeshComp;
	//Caching Player Interface
	TScriptInterface<IHunterPlayerInterface>PlayerInterface;

	//Timer For Firing Weapon
	FTimerHandle FireWeaponTimer;

	//LineTrace Variables
	FHitResult HitResult;
	FVector ForwardVector;
	FVector StartPoint;
	FVector EndPoint;
	FCollisionQueryParams TraceCollision;

protected:

	void WeaponFiring(ACharacter* Player);
};
