// Fill out your copyright notice in the Description page of Project Settings.


#include "HunterPlayer/HunterPlayer.h"

#include "PlayerState/MotionState/PlayerMove/PlayerMove.h"
#include "PlayerState/MotionState/PlayerLook/PlayerLook.h"

// Sets default values
AHunterPlayer::AHunterPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

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

void AHunterPlayer::MoveFunction(const FInputActionValue& InputValue)
{
	MotionStateLibrary[MotionEnum::OnMove]->Begin(this, InputValue);
}

void AHunterPlayer::LookFunction(const FInputActionValue& InputValue)
{
	MotionStateLibrary[MotionEnum::OnLook]->Begin(this, InputValue);
}

