// Fill out your copyright notice in the Description page of Project Settings.


#include "PropPlayer/PropPlayer.h"

#include "PlayerState/MotionState/PlayerMove/PlayerMove.h"
#include "PlayerState/MotionState/PlayerLook/PlayerLook.h"

#include "PlayerState/InputState/Prop/OnPropMorph.h"
#include "Kismet/KismetSystemLibrary.h"

void APropPlayer::SetPlayerMesh(UStaticMesh* NewMesh)
{
	PlayerMesh->SetStaticMesh(NewMesh);
}

// Sets default values
APropPlayer::APropPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	CameraBoom->SetupAttachment(RootComponent);

	TPSCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	TPSCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Actual Mesh"));
	PlayerMesh->SetupAttachment(GetMesh());
	
	MotinStateLibrary.Add(MotionEnum::OnMove,MakeUnique<PlayerMove>());
	MotinStateLibrary.Add(MotionEnum::OnLook,MakeUnique<PlayerLook>());

	InputStateLibrary.Add(InputStateEnum::OnPropMorph,MakeUnique<OnPropMorph>());

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
	MotinStateLibrary[MotionEnum::OnMove]->Begin(this, InputValue);
}

void APropPlayer::LookFunction(const FInputActionValue& InputValue)
{
	MotinStateLibrary[MotionEnum::OnLook]->Begin(this, InputValue);
}

void APropPlayer::MorphObjectFunction()
{
	InputStateLibrary[InputStateEnum::OnPropMorph]->OnBegin(this);

}

