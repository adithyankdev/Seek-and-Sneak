// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerState/InputState/InputStateAbstract.h"

/**
 * 
 */
class SEEKANDSNEAK_3D_API OnPropMorph : public InputStateAbstract
{
public:
	OnPropMorph();
	~OnPropMorph();

	void Begin(ACharacter* Player)override;
	void End(ACharacter* Player)override;
};
