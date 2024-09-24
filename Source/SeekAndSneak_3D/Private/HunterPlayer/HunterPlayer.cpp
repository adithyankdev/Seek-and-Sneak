// Fill out your copyright notice in the Description page of Project Settings.


#include "HunterPlayer/HunterPlayer.h"


// Sets default values
AHunterPlayer::AHunterPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	FPSCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	FPSCamera->SetupAttachment(GetMesh(), TEXT("head"));

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
	FVector2D MoveValue = InputValue.Get<FVector2D>();
	AddMovementInput(GetActorForwardVector(), MoveValue.X);
	AddMovementInput(GetActorRightVector(), MoveValue.Y);
}

void AHunterPlayer::LookFunction(const FInputActionValue& InputValue)
{
	FVector2D MoveValue = InputValue.Get<FVector2D>();
	AddControllerYawInput(MoveValue.X);
	AddControllerPitchInput(MoveValue.Y);
}

