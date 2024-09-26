// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameWidget.generated.h"

class UImage;

/**
 * 
 */
UCLASS()
class SEEKANDSNEAK_3D_API UInGameWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void NativeConstruct() override;

protected:

	UPROPERTY(meta = (BindWidget))
	UImage* Corsshairpng;
};
