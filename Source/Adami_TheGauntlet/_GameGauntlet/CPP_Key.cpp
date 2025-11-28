// Fill out your copyright notice in the Description page of Project Settings.


#include "_GameGauntlet/CPP_Key.h"

#include "Adami_TheGauntletCharacter.h"

// Sets default values
ACPP_Key::ACPP_Key()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACPP_Key::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_Key::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPP_Key::OnCollect_Implementation(AAdami_TheGauntletCharacter* Player)
{
	GEngine->AddOnScreenDebugMessage(
		-1,
		2.0f,
		FColor::Yellow,
		TEXT("Collected KEY")
	);
	
	// dico al character che ho raccolto la chiave
	Player->HasKey = true;

	// distruggo l'oggetto
	Destroy();
}

