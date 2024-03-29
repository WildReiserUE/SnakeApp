// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "SnakeElementBase.generated.h"

class UStaticMeshComponent;
class ASnakeBase;

UCLASS()
class SNAKEAPP_API ASnakeElementBase : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	ASnakeElementBase();

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly)
	UStaticMeshComponent* MeshComponent = nullptr;

	UPROPERTY()
	ASnakeBase* SnakeOwner = nullptr;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent)
	void SetFirstElementType();
	void SetFirstElementType_Implementation();

	UFUNCTION()
	void HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent,
							AActor* OtherActor,
							UPrimitiveComponent* OtherComp,
							int32 OtherBodyIndex,
							bool bFromSweep,
							const FHitResult &SweepResult);

	UFUNCTION()
	void ToggleCollision();

	virtual void Interact(AActor* Interactor, bool bIsHead) override;
};
