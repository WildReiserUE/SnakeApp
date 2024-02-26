// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeBase.h"
#include "SnakeElementBase.h"

ASnakeBase::ASnakeBase()
{
	PrimaryActorTick.bCanEverTick = true;
	ElementSize = 80.f;
	MovementSpeed = 0.5f;
	ElementsStart = 3;
	LastMoveDirection = EMovementDirection::DOWN;
}

int ASnakeBase::GetSnakeLenght()
{
	return SnakeElements.Num();
}

void ASnakeBase::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickInterval(MovementSpeed);
	BlockToAdd = ElementsStart;
	MakeFirstSnake();
	AddSKElement();
}

void ASnakeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	InputAllow = true;
	Move();
}

void ASnakeBase::AddSKElement()
{
	if(QueueExist())
	{
		if(!GetWorld()->GetTimerManager().IsTimerActive(SnakeTimerHandle))
		{
			GetWorld()->GetTimerManager().SetTimer(SnakeTimerHandle, this, &ASnakeBase::AddSKElement, MovementSpeed, true, MovementSpeed);
		}
		else
		{
			FVector NewLocation(0);
			if(SnakeElements.Num() > 0)
				NewLocation = SnakeElements[SnakeElements.Num()-1]->GetActorLocation();
			FTransform NewTransform(NewLocation);
			ASnakeElementBase* NewSnakeElement = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass, NewTransform);
			NewSnakeElement->SnakeOwner = this;
			ElemIndex = SnakeElements.Add(NewSnakeElement);
			NewSnakeElement->ToggleCollision();
			BlockToAdd--;
			ElementsStart++;
			FoundFood.Broadcast(ElementsStart);
			UE_LOG(LogTemp, Warning, TEXT("Snake.ELEMENTS === %i"), BlockToAdd);
		}
	}
	else
	{
		if (GetWorld()->GetTimerManager().IsTimerActive(SnakeTimerHandle))
			GetWorld()->GetTimerManager().ClearTimer(SnakeTimerHandle);
	}

	GetScore();
}

void ASnakeBase::MakeFirstSnake()
{
	for(int i = 0; i < ElementsStart; i++ )
	{
		FVector NewLocation(SnakeElements.Num() * ElementSize, 0, 30);
		FTransform NewTransform(NewLocation);
		ASnakeElementBase* NewSnakeElement = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass, NewTransform);
		NewSnakeElement->SnakeOwner = this;
		ElemIndex = SnakeElements.Add(NewSnakeElement);

		if (ElemIndex == 0)
		{
			NewSnakeElement->SetFirstElementType();
		}
		BlockToAdd--;
		UE_LOG(LogTemp, Warning, TEXT("Snake.FIRST_ELEMENTS === %i"), BlockToAdd);
	}
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

	if(SnakeElements.Num() > 0)
	{
		SnakeElements[0]->ToggleCollision();

		for (int i = SnakeElements.Num() - 1; i > 0; i--)
		{
			auto CurrentElement = SnakeElements[i];
			auto PrevElement = SnakeElements[i - 1];
			FVector PrevLocation = PrevElement->GetActorLocation();
			CurrentElement->SetActorLocation(PrevLocation);
		}
		SnakeElements[0]->AddActorWorldOffset(MovementVector);
		SnakeElements[0]->ToggleCollision();
	}
}

bool ASnakeBase::QueueExist()
{
	UE_LOG(LogTemp, Warning, TEXT("Snake.QUEUE  === %i"), BlockToAdd);
	return BlockToAdd > 0;
}

void ASnakeBase::SnakeElementOverlap(ASnakeElementBase* OverlappedElement, AActor* Other)
{
	//UE_LOG(LogTemp, Display, TEXT("SnakeElementOverlap"));
	if (OverlappedElement)
	{
		SnakeElements.Find(OverlappedElement, ElemIndex);
		bool bIsFirst = ElemIndex == 0;
		IInteractable* InteractableInterface = Cast<IInteractable>(Other);
		if (InteractableInterface)
		{
			InteractableInterface->Interact(this, bIsFirst);
		}
	}
}

void ASnakeBase::GetScore_Implementation()
{
}
