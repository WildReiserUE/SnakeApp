// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SnakeBase.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFoundFood, int, Food);

class ASnakeElementBase;

UENUM()
enum class EMovementDirection
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

UCLASS()
class SNAKEAPP_API ASnakeBase : public AActor
{
	GENERATED_BODY()

public:
	ASnakeBase();

	FOnFoundFood FoundFood;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ASnakeElementBase> SnakeElementClass;

	UPROPERTY(EditDefaultsOnly)
	float ElementSize = 50.f;

	UPROPERTY(EditDefaultsOnly)
	float MovementSpeed = 1.f;

	UPROPERTY(EditDefaultsOnly)
	int ElementsStart = 1;

	UPROPERTY()
	bool InputAllow = true;

	UPROPERTY()
	TArray<ASnakeElementBase*> SnakeElements;

	UPROPERTY()
	EMovementDirection LastMoveDirection = EMovementDirection::UP;

	UFUNCTION(BlueprintCallable)
	int GetSnakeLenght();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	int32 ElemIndex = 0;
	UFUNCTION()
	void AddElement(int Elements);

	void Move();
	bool QueueExist();
	int BlockToAdd = 0;
	FTimerDelegate SnakeTimerDelegate;
	FTimerHandle SnakeTimerHandle;

	UFUNCTION()
	void SnakeElementOverlap(ASnakeElementBase* OverlappedElement, AActor* Other);

	UFUNCTION(BlueprintNativeEvent)
	void GetScore();
	void GetScore_Implementation();
};
