// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "InputActionValue.h"

#include "PlayerState/MotionState/MotionStateAbstract.h"
#include "PlayerState/InputState/InputStateAbstract.h"

#include "Interface/Player/HunterPlayerInterface.h"
#include "HunterPlayer.generated.h"


UCLASS()
class SEEKANDSNEAK_3D_API AHunterPlayer : public ACharacter , public IHunterPlayerInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHunterPlayer();

	// Interface Functions
	bool CanRun()override;
	USkeletalMeshComponent* GetWeaponMeshComp() override;
	void SetFireWeaponLoc(FVector& StartPoint, FVector& ControlFrowardVector) override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifeTimeProps)const override;

private:

	TMap<MotionEnum, TUniquePtr<MotionStateAbstract>>MotionStateLibrary;

	TMap<InputStateEnum, TUniquePtr<InputStateAbstract>>InputStateLibrary;

	UPROPERTY(Replicated);
	bool IsPlayerRunning;

	float WeaponBulletCount;
	float MaxBulletCount;

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

//--------------------------------->>>>> Sprint Function
	void StartSprintFunction();
	void StopSprintFunction();

	UFUNCTION(Server,Reliable)
	void Sprint_OnServer(float WalkSpeed,bool CanSprint);

	UFUNCTION(NetMulticast,Reliable)
	void Sprint_OnMulticast(float WalkSpeed,bool CanSprint);
//-------------------------------->>>>> Sprint Function

//-------------------------------->>>>> Weapon Fire Function

	FTimerHandle FireWeaponTimer;

	void StartFiringWeapon();
	void FiringWeapon();
	void StopFiringWeapon();

	UFUNCTION(Server,Reliable)
	void FireWeapon_OnServer(bool Firing);
 
	UFUNCTION(NetMulticast,Reliable)
	void FireWeapon_OnMulticast(bool Firing);

};
