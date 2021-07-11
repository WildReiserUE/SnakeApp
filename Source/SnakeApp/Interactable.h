// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SNAKEAPP_API IInteractable
{
	GENERATED_BODY()

	// Добавьте в этот класс интерфейсные функции. Это класс, который будет унаследован для реализации этого интерфейса.
public:
	virtual void Interact(AActor* Interactor, bool bIsHead);
};
