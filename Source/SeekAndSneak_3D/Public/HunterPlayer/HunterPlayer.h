// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "InputActionValue.h"
#include "PlayerState/MotionState/MotionStateAbstract.h"
#include "HunterPlayer.generated.h"


UCLASS()
class SEEKANDSNEAK_3D_API AHunterPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHunterPlayer();

private:

	TMap<MotionEnum, TUniquePtr<MotionStateAbstract>>MotionStateLibrary;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UCameraComponent* FPSCamera;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Movement Function
	void MoveFunction(const FInputActionValue& InputValue);
	void LookFunction(const FInputActionValue& InputValue);

};
