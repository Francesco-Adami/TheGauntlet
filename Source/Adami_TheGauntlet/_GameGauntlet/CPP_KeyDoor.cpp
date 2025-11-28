// Fill out your copyright notice in the Description page of Project Settings.


#include "_GameGauntlet/CPP_KeyDoor.h"

#include "Adami_TheGauntletCharacter.h"

// Sets default values
ACPP_KeyDoor::ACPP_KeyDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACPP_KeyDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_KeyDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPP_KeyDoor::Interact_Implementation(AActor* Interactor)
{
	// Immagino che solo il player possa interagire con la porta
	AAdami_TheGauntletCharacter* Player = Cast<AAdami_TheGauntletCharacter>(Interactor);
	if (!Player) return;

	if (Player->HasKey)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			3.5f,
			FColor::Green,
			TEXT("- Door Opened!"));
		Destroy();
	}
	
}

