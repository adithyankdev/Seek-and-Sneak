// Fill out your copyright notice in the Description page of Project Settings.


#include "HunterPlayer/HunterPlayer.h"
#include "Net/UnrealNetwork.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/CharacterMovementReplication.h"

#include "PlayerState/MotionState/PlayerMove/PlayerMove.h"
#include "PlayerState/MotionState/PlayerLook/PlayerLook.h"

#include "PlayerState/InputState/Hunter/OnPlayerFire.h"

#include "Runtime/Engine/Public/TimerManager.h"

#include "Kismet/KismetSystemLibrary.h"

#include "GameFramework/PlayerController.h"

bool AHunterPlayer::CanRun()
{
	return IsPlayerRunning;
}

USkeletalMeshComponent* AHunterPlayer::GetWeaponMeshComp()
{
	return nullptr;
}

void AHunterPlayer::SetFireWeaponLoc(FVector& StartPoint, FVector& ControlFrowardVector)
{
	StartPoint = FPSCamera->GetComponentLocation();
	ControlFrowardVector = FPSCamera->GetComponentRotation().Vector();
}

void AHunterPlayer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AHunterPlayer, IsPlayerRunning);
}

// Sets default values
AHunterPlayer::AHunterPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SetReplicateMovement(true);

	FPSCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	FPSCamera->SetupAttachment(GetMesh(), TEXT("head"));

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SKMesh"));
	WeaponMesh->SetupAttachment(GetMesh(), TEXT("WeaponHoldPosition"));

	MotionStateLibrary.Add(MotionEnum::OnMove, MakeUnique<PlayerMove>());
	MotionStateLibrary.Add(MotionEnum::OnLook, MakeUnique<PlayerLook>());

	InputStateLibrary.Add(InputStateEnum::OnHunterFire, MakeUnique<OnPlayerFire>());

	MaxBulletCount = 30;
	WeaponBulletCount = MaxBulletCount;
}



// Called when the game starts or when spawned
void AHunterPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHunterPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHunterPlayer::PlayerJogFunction(const FInputActionValue& InputValue)
{
	MotionStateLibrary[MotionEnum::OnMove]->Begin(this, InputValue);
}

void AHunterPlayer::LookFunction(const FInputActionValue& InputValue)
{
	MotionStateLibrary[MotionEnum::OnLook]->Begin(this, InputValue);
}

//---------------------------------------------------------------------------------------->>>>>> ( Sprint Function )
void AHunterPlayer::StartSprintFunction()
{
	if (GetVelocity().Size() != 0)
	{
		if (HasAuthority())Sprint_OnMulticast(500.0f, true);
		else Sprint_OnServer(500.0f, true);
	}
}

void AHunterPlayer::StopSprintFunction()
{
	if (HasAuthority())Sprint_OnMulticast(250.0f, false);
	else Sprint_OnServer(200.0f, false);
}

void AHunterPlayer::Sprint_OnServer_Implementation(float WalkSpeed,bool CanSprint)         /*Server*/
{
	Sprint_OnMulticast(WalkSpeed, CanSprint);
}

void AHunterPlayer::Sprint_OnMulticast_Implementation(float WalkSpeed,bool CanSprint)      /*Multicast*/
{
	IsPlayerRunning = CanSprint;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}
//------------------------------------------------------------------------------------------>>>>>


//------------------------------------------------------------------------------------------>>>>> ( Firing Weapon )
void AHunterPlayer::StartFiringWeapon()
{
	if (WeaponBulletCount > 0)
	{
		//GetWorldTimerManager().SetTimer(FireWeaponTimer, this, &AHunterPlayer::FiringWeapon, 0.5, true);
		if (HasAuthority())
		{
			FireWeapon_OnMulticast(true);
		}
		else
		{
			FireWeapon_OnServer(true);
		}
		WeaponBulletCount--;
	}
}

void AHunterPlayer::FiringWeapon()
{
	if (HasAuthority())
	{
		FireWeapon_OnMulticast(true);
	}
	else
	{
		FireWeapon_OnServer(true);
	}
	
}

void AHunterPlayer::StopFiringWeapon()
{
	//GetWorldTimerManager().ClearTimer(FireWeaponTimer);
	if (HasAuthority())
	{
		FireWeapon_OnMulticast(false);
	}
	else
	{
		FireWeapon_OnServer(false);
	}
	
}
void AHunterPlayer::FireWeapon_OnServer_Implementation(bool Firing)
{
	FireWeapon_OnMulticast(Firing);
}
void AHunterPlayer::FireWeapon_OnMulticast_Implementation(bool Firing)
{	
	if (Firing) InputStateLibrary[InputStateEnum::OnHunterFire]->Begin(this);
	else InputStateLibrary[InputStateEnum::OnHunterFire]->End(this);
}
