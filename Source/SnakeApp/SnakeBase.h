// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SnakeBase.generated.h"

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
	// Sets default values for this actor's properties
	ASnakeBase();

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<ASnakeElementBase> SnakeElementClass;

	UPROPERTY(EditDefaultsOnly)
		float ElementSize;

	UPROPERTY(EditDefaultsOnly)
		float MovementSpeed;

	UPROPERTY(EditDefaultsOnly)
		int ElementsStart;

	UPROPERTY()
		bool InputAllow;

	UPROPERTY()
		TArray<ASnakeElementBase*> SnakeElements;

	UPROPERTY()
		EMovementDirection LastMoveDirection;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int SnakeTotallLenght;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void AddSnakeElement(int ElementsNum = 1);

	UFUNCTION(BlueprintCallable)
	void Move();

	UFUNCTION()
	void SnakeElementOverlap(ASnakeElementBase* OverlappedElement, AActor* Other);

	UFUNCTION(BlueprintNativeEvent)
		///int GetScore();
	void GetScore();
	void GetScore_Implementation();
};
