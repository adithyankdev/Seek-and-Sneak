// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "PlayerState/MotionState/MotionStateAbstract.h"
#include "PropPlayer.generated.h"

UCLASS()
class SEEKANDSNEAK_3D_API APropPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APropPlayer();

private:

	//Smart Pointer For Handle The Memory Management
	TMap<MotionEnum, TUniquePtr<MotionStateAbstract>>MotinStateLibrary;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	USpringArmComponent* CameraBoom;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UCameraComponent* TPSCamera;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Movement Function
	void MoveFunction(const FInputActionValue& InputValue);
	void LookFunction(const FInputActionValue& InputValue);


};
