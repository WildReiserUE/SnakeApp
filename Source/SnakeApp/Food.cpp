// Fill out your copyright notice in the Description page of Project Settings.


#include "Food.h"
#include "SnakeBase.h"
#include "Components/PrimitiveComponent.h"

// Sets default values
AFood::AFood()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFood::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFood::Interact(AActor* Interactor, bool bIsHead)
{
	//UE_LOG(LogTemp, Display, TEXT("FoodInteract"));
	if (bIsHead)
	{
		auto  Snake = Cast<ASnakeBase>(Interactor);
		if (IsValid(Snake))
		{
			Snake->BlockToAdd += Bonuses;
			Snake->AddSKElement();
			Destroy();
		}
	}
}

