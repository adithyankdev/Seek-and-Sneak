// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/HunterPlayerController.h"
#include "EnhancedInputComponent.h"
#include "HunterPlayer/HunterPlayer.h"
#include "EnhancedInputSubsystems.h"

#include "Kismet/KismetSystemLibrary.h"

void AHunterPlayerController::BeginPlay()
{
	//Only Applied By The LocalPlayer
	if (GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			//Setting Up The Mapping Context
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(PlayerMappingContext, 0);
		}
	

	   if (UEnhancedInputComponent* EnhancedInput = Cast <UEnhancedInputComponent>(this->InputComponent))
	   {
		  if (AHunterPlayer* HunterPlayer = Cast<AHunterPlayer>(GetPawn()))
		  {
			//Binding InputAction And The Correspoding Functions
			EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, HunterPlayer, &AHunterPlayer::MoveFunction);
			EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, HunterPlayer, &AHunterPlayer::LookFunction);

		  }
	   }
	}
}
