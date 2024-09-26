// Fill out your copyright notice in the Description page of Project Settings.


#include "HunterPlayer/HunterPlayer.h"
#include "Net/UnrealNetwork.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/CharacterMovementReplication.h"

#include "PlayerState/MotionState/PlayerMove/PlayerMove.h"
#include "PlayerState/MotionState/PlayerLook/PlayerLook.h"

#include "Kismet/KismetSystemLibrary.h"

bool AHunterPlayer::CanRun()
{
	return IsPlayerRunning;
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

	MotionStateLibrary.Add(MotionEnum::OnMove, MakeUnique<PlayerMove>());
	MotionStateLibrary.Add(MotionEnum::OnLook, MakeUnique<PlayerLook>());
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

void AHunterPlayer::StartSprintFunction()
{
	if (HasAuthority())CallSprintOnMulticast(500.0f,true);
	else CallSprintOnServer(500.0f,true);
}

void AHunterPlayer::StopSprintFunction()
{
	if (HasAuthority())CallSprintOnMulticast(250.0f, false);
	else CallSprintOnServer(200.0f, false);
}

void AHunterPlayer::CallSprintOnServer_Implementation(float WalkSpeed,bool CanSprint)
{
	CallSprintOnMulticast(WalkSpeed, CanSprint);
}

void AHunterPlayer::CallSprintOnMulticast_Implementation(float WalkSpeed,bool CanSprint)
{
	IsPlayerRunning = CanSprint;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

