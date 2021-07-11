// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeBase.h"
#include "SnakeElementBase.h"

// Sets default values
ASnakeBase::ASnakeBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ElementSize = 80.f;
	MovementSpeed = 10.f;
	ElementsStart = 3;
	LastMoveDirection = EMovementDirection::DOWN;
	SnakeTotallLenght = 0;
}

// Called when the game starts or when spawned
void ASnakeBase::BeginPlay()
{
	Super::BeginPlay();	
	SetActorTickInterval(MovementSpeed);
	AddSnakeElement(ElementsStart);
}

// Called every frame
void ASnakeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	InputAllow = true;
	Move();
}

void ASnakeBase::AddSnakeElement(int ElementsNum)
{
	int32 ElemIndex = 0;
	for (int i = 0; i < ElementsNum; ++i)
	{
		FVector NewLocation(SnakeElements.Num() * ElementSize, 0, 0);
		FTransform NewTransform(NewLocation);
		ASnakeElementBase* NewSnakeElement = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass, NewTransform);
		NewSnakeElement->SnakeOwner = this;
		ElemIndex = SnakeElements.Add(NewSnakeElement);

		NewSnakeElement->MeshComponent->SetVisibility(false);
	
		if (ElemIndex == 0)
		{
			NewSnakeElement->SetFirstElementType();
		}

		//UE_LOG(LogTemp, Display, TEXT("AddSnakeElement %d"), ElemIndex);
	}

	SnakeTotallLenght = ElemIndex - ElementsStart + 1;
	GetScore();

}

void ASnakeBase::Move()
{
	//UE_LOG(LogTemp, Display, TEXT("Snake.Move"));
	FVector MovementVector(ForceInitToZero);

	switch (LastMoveDirection)
	{
	case EMovementDirection::UP:
		MovementVector.X += ElementSize;
		break;
	case EMovementDirection::DOWN:
		MovementVector.X -= ElementSize;
		break;
	case EMovementDirection::LEFT:
		MovementVector.Y -= ElementSize;
		break;
	case EMovementDirection::RIGHT:
		MovementVector.Y += ElementSize;
		break;
	}

	if (!SnakeElements[0]->MeshComponent->GetVisibleFlag())
	{
		SnakeElements[0]->MeshComponent->SetVisibility(true);
	}

	SnakeElements[0]->ToggleCollision();

	for (int i = SnakeElements.Num() - 1; i > 0; i--)
	{
		auto CurrentElement = SnakeElements[i];
		auto PrevElement = SnakeElements[i - 1];
		FVector PrevLocation = PrevElement->GetActorLocation();
		CurrentElement->SetActorLocation(PrevLocation);

		if (!CurrentElement->MeshComponent->GetVisibleFlag())
		{
			CurrentElement->MeshComponent->SetVisibility(true);
		}

	}
	SnakeElements[0]->AddActorWorldOffset(MovementVector);
	SnakeElements[0]->ToggleCollision();	
}

void ASnakeBase::SnakeElementOverlap(ASnakeElementBase* OverlappedElement, AActor* Other)
{
	//UE_LOG(LogTemp, Display, TEXT("SnakeElementOverlap"));
	if ((OverlappedElement))
	{
		int32 ElemIndex;
		SnakeElements.Find(OverlappedElement, ElemIndex);
		bool bIsFirst = ElemIndex == 0;
		IInteractable* InteractableInterface = Cast<IInteractable>(Other);
		if (InteractableInterface)
		{
			InteractableInterface->Interact(this, bIsFirst);
		}
	}
}

//void ASnakeBase::GetScore()
//{
//	//return SnakeTotallLenght;
//}

void ASnakeBase::GetScore_Implementation()
{
	//UE_LOG(LogTemp, Display, TEXT("GetScore_Implementation"));
	//return int SnakeTotallLenght;
}
