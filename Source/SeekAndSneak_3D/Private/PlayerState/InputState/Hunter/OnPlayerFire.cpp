// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerState/InputState/Hunter/OnPlayerFire.h"
#include "GameFramework/Character.h"


#include "Runtime/Engine/Public/TimerManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"

OnPlayerFire::OnPlayerFire()
{
	ShootingRange = 700.0f;
	FireIntervalTime = 0.2f;
}

OnPlayerFire::~OnPlayerFire()
{
}

void OnPlayerFire::Begin(ACharacter* Player)
{
	if (WeaponMeshComp)
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
	PlayerInterface->SetFireWeaponLoc(StartPoint, ForwardVector);  //Passing Value By On Ref 
	//Since EndPoint Return  Only Controller Forward Vector
	EndPoint = StartPoint + (ForwardVector * ShootingRange);

	/*Weapon Animation Need To Be Added*/
	//WeaponMeshComp->PlayAnimation()

	Player->GetWorld()->LineTraceSingleByChannel(HitResult, StartPoint, EndPoint, ECC_Visibility, TraceCollision);

	//DrawDebugLine(Player->GetWorld(), StartPoint, EndPoint, FColor::Green);
	DrawDebugCylinder(Player->GetWorld(), StartPoint, EndPoint, 10, 12, FColor::Green, false, 1.0f);
	
	UKismetSystemLibrary::PrintString(Player->GetWorld(), TEXT("Fired"), true, true, FLinearColor::Green);

	//Niagara Hit Effect Need To Add
}
