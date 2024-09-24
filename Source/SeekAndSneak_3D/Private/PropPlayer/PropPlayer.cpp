// Fill out your copyright notice in the Description page of Project Settings.


#include "PropPlayer/PropPlayer.h"

// Sets default values
APropPlayer::APropPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	CameraBoom->SetupAttachment(RootComponent);

	TPSCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	TPSCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

}

// Called when the game starts or when spawned
void APropPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APropPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APropPlayer::MoveFunction(const FInputActionValue& InputValue)
{
	FVector2D MoveValue = InputValue.Get<FVector2D>();

	FRotator Rotation = Controller->GetControlRotation();
	FRotator YawRotation = FRotator(0, Rotation.Yaw, 0);

	FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	

	AddMovementInput(ForwardDirection, MoveValue.X);
	AddMovementInput(RightDirection, MoveValue.Y);
}

void APropPlayer::LookFunction(const FInputActionValue& InputValue)
{
	FVector2D MoveValue = InputValue.Get<FVector2D>();
	AddControllerYawInput(MoveValue.X);
	AddControllerPitchInput(MoveValue.Y);
}

