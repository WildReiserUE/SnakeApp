// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeElementBase.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "SnakeBase.h"
#include "Components/PrimitiveComponent.h"


ASnakeElementBase::ASnakeElementBase()
{
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	RootComponent = MeshComponent;
}

void ASnakeElementBase::BeginPlay()
{
	Super::BeginPlay();
}

void ASnakeElementBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASnakeElementBase::SetFirstElementType_Implementation()
{
	//UE_LOG(LogTemp, Display, TEXT("SetFirstElementType_Implementation"));
	MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ASnakeElementBase::HandleBeginOverlap);
}

void ASnakeElementBase::Interact(AActor* Interactor, bool bIsHead)
{
	UE_LOG(LogTemp, Display, TEXT("Interact"));
	ASnakeBase* Snake = Cast<ASnakeBase>(Interactor);
	if (Snake)
	{
		Snake->Destroy();
	}
}

void ASnakeElementBase::HandleBeginOverlap(	UPrimitiveComponent* OverlappedComponent,
											AActor* OtherActor,
											UPrimitiveComponent* OtherComp,
											int32 OtherBodyIndex,
											bool bFromSweep,
											const FHitResult &SweepResult)
{
	//UE_LOG(LogTemp, Display, TEXT("HandleBeginOverlap"));
	if ((SnakeOwner))
	{
		SnakeOwner->SnakeElementOverlap(this, OtherActor);
	}
}

void ASnakeElementBase::ToggleCollision()
{
	//UE_LOG(LogTemp, Display, TEXT("ToggleCollision0000 %d"), MeshComponent->GetCollisionEnabled());
	if (MeshComponent->GetCollisionEnabled() == ECollisionEnabled::NoCollision)
	{
		//UE_LOG(LogTemp, Display, TEXT("ToggleCollision1111"));
		MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	else
	{
		//UE_LOG(LogTemp, Display, TEXT("ToggleCollision22222"));
		MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}