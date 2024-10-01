// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerState/InputState/Hunter/OnPlayerFire.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

#include "Runtime/Engine/Public/TimerManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"

OnPlayerFire::OnPlayerFire()
{

	FireAnimation = LoadObject<UAnimSequence>(nullptr, TEXT("/Game/Asset/Weapons/Rifle/Animations/RifileFireAnimation.RifileFireAnimation"));
	WeaponBulletHitParticle = LoadObject<UParticleSystem>(nullptr, TEXT("/Game/Asset/Weapons/Rifle/Vfx/RifileShotImpact.RifileShotImpact"));

	ShootingRange = 2000.0f;
	FireIntervalTime = 0.15f;
}

OnPlayerFire::~OnPlayerFire()
{

}

void OnPlayerFire::Begin(ACharacter* Player)
{
	if (PlayerInterface == nullptr)
	{
		//Call At Once , So Using This For Store Other Datas
		if (IHunterPlayerInterface* Interface = Cast <IHunterPlayerInterface>(Player))
		{
			PlayerInterface.SetObject(Player);
			PlayerInterface.SetInterface(Interface);

			WeaponMeshComp = Interface->GetWeaponMeshComp();
		}
		TraceCollision.AddIgnoredActor(Player);
	}
	Player->GetWorld()->GetTimerManager().SetTimer(FireWeaponTimer, [this,Player]() {WeaponFiring(Player); },FireIntervalTime, true);

	
}

void OnPlayerFire::End(ACharacter* Player)
{
	Player->GetWorld()->GetTimerManager().ClearTimer(FireWeaponTimer);
}

//Contain Fire Weapon Logic
void OnPlayerFire::WeaponFiring(ACharacter* Player)
{
	if(PlayerInterface)PlayerInterface->SetFireWeaponLoc(StartPoint, ForwardVector);  //Passing Value By On Ref 
	//Since EndPoint Return  Only Controller Forward Vector
	EndPoint = StartPoint + (ForwardVector * ShootingRange);

	/*Weapon Animation Added*/
	if(FireAnimation)WeaponMeshComp->PlayAnimation(FireAnimation, false);

	IsHit = Player->GetWorld()->LineTraceSingleByChannel(HitResult, StartPoint, EndPoint, ECC_Visibility, TraceCollision);

	if (IsHit)
	{
		ParticleTransform.SetLocation(HitResult.ImpactPoint);
		UGameplayStatics::SpawnEmitterAtLocation(Player->GetWorld(), WeaponBulletHitParticle, ParticleTransform, true, EPSCPoolMethod::AutoRelease);
	}

	DrawDebugLine(Player->GetWorld(), StartPoint, EndPoint, FColor::Red,false,3);
	//Niagara Hit Effect Need To Add
}
