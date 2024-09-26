// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "InputActionValue.h"
#include "PlayerState/MotionState/MotionStateAbstract.h"
#include "Interface/Player/HunterPlayerInterface.h"
#include "HunterPlayer.generated.h"


UCLASS()
class SEEKANDSNEAK_3D_API AHunterPlayer : public ACharacter , public IHunterPlayerInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHunterPlayer();

	bool CanRun()override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifeTimeProps)const override;

private:

	TMap<MotionEnum, TUniquePtr<MotionStateAbstract>>MotionStateLibrary;

	UPROPERTY(Replicated);
	bool IsPlayerRunning;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UCameraComponent* FPSCamera;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Movement Function
	void PlayerJogFunction(const FInputActionValue& InputValue);
	void LookFunction(const FInputActionValue& InputValue);
	void StartSprintFunction();
	void StopSprintFunction();

	UFUNCTION(Server,Reliable)
	void CallSprintOnServer(float WalkSpeed,bool CanSprint);

	UFUNCTION(NetMulticast,Reliable)
	void CallSprintOnMulticast(float WalkSpeed,bool CanSprint);
};
