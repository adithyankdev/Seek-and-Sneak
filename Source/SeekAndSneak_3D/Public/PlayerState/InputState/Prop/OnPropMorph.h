// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerState/InputState/InputStateAbstract.h"
#include "Interface/Player/PropPlayerInterface.h"

/**
 * 
 */
class SEEKANDSNEAK_3D_API OnPropMorph : public InputStateAbstract
{
public:
	OnPropMorph();
	~OnPropMorph();

	void OnBegin(ACharacter* Player)override;
	void OnEnd(ACharacter* Player)override;

private:

	//Caching The Interface
	TScriptInterface<IPropPlayerInterface>PlayerInterface;

	//Trace Variables
	bool IsTraceHit;
	float TraceRadius;
	FVector Start;
	FVector End;
	FHitResult TraceHitResult;
	FCollisionQueryParams TraceCollisionParams;

};
