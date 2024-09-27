// Fill out your copyright notice in the Description page of Project Settings.


#include "PropPlayer/PropPlayer.h"

#include "PlayerState/MotionState/PlayerMove/PlayerMove.h"
#include "PlayerState/MotionState/PlayerLook/PlayerLook.h"

#include "PlayerState/InputState/Prop/OnPropMorph.h"
#include "PlayerState/InputState/Prop/OnPropClone.h"

#include "Runtime/Engine/Public/TimerManager.h"
#include "Kismet/KismetSystemLibrary.h"

void APropPlayer::SetPlayerMesh(UStaticMesh* NewMesh)
{
	PlayerMesh->SetStaticMesh(NewMesh);
}

UStaticMesh* APropPlayer::GetPlayerMesh()
{
	return PlayerMesh->GetStaticMesh();
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
	InputStateLibrary.Add(InputStateEnum::OnPropClone, MakeUnique<OnPropClone>());

}


// Called when the game starts or when spawned
void APropPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	MorphMaxCoolDownTime = 15.0f;
	TotalCloneCount = 5.0f;
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

//---------------------------------------------------------------------------------------------->>>>> ( Prop Morph Function )
void APropPlayer::MorphObjectFunction()
{
	if (MorphCoolDownTime == 0)
	{
		if (HasAuthority())
		{
			MorphObject_Multicast();
		}
		else
		{
			MorphObject_Server();
		}
		MorphCoolDownTime = MorphMaxCoolDownTime;
		GetWorld()->GetTimerManager().SetTimer(MorphCoolDownTimer, this, &APropPlayer::UpdateMorphCoolDownTime, 1, true);
	}
}

void APropPlayer::MorphObject_Server_Implementation()
{
	MorphObject_Multicast();
}

void APropPlayer::MorphObject_Multicast_Implementation()
{
	InputStateLibrary[InputStateEnum::OnPropMorph]->Begin(this);
}

void APropPlayer::UpdateMorphCoolDownTime()
{
	MorphCoolDownTime--;
	if (MorphCoolDownTime == 0)GetWorld()->GetTimerManager().ClearTimer(MorphCoolDownTimer);
}

//----------------------------------------------------------------------------------------------->>>>>

//----------------------------------------------------------------------------------------------->>>>> ( Prop Clone Function )
void APropPlayer::PropCloneFunction()
{
	if (ClonedCount <= TotalCloneCount)
	{
		if (HasAuthority())
		{
			PropClone_Multicast();
		}
		else
		{
			PropClone_Server();
		}
		ClonedCount++;
	}
}

void APropPlayer::PropClone_Server_Implementation()
{
	PropClone_Multicast();
}
void APropPlayer::PropClone_Multicast_Implementation()
{
	InputStateLibrary[InputStateEnum::OnPropClone]->Begin(this);
}
//---------------------------------------------------------------------------------------------->>>>>