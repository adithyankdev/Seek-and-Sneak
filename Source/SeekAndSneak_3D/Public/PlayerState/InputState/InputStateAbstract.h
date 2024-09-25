// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class ACharacter;

enum class InputStateEnum
{
	OnPropMorph,
};

/**
 * 
 */
class SEEKANDSNEAK_3D_API InputStateAbstract
{
public:
	InputStateAbstract();
	virtual ~InputStateAbstract();

	virtual void OnBegin(ACharacter* Player) = 0;
	virtual void OnEnd(ACharacter* Player) = 0;
};
