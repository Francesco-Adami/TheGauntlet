// Fill out your copyright notice in the Description page of Project Settings.


#include "_GameGauntlet/CPP_FinalGate.h"

// Sets default values
ACPP_FinalGate::ACPP_FinalGate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACPP_FinalGate::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_FinalGate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPP_FinalGate::NotifyActorBeginOverlap(AActor* OtherActor)
{
	// Super::NotifyActorBeginOverlap(OtherActor);
	GEngine->AddOnScreenDebugMessage(
		-1,
		2.0f,
		FColor::Red,
		"OVERLAPPED"
	);

	for (auto active: LeversActivated)
	{
		if (!active) return;
	}

	GEngine->AddOnScreenDebugMessage(
		-1,
		2.0f,
		FColor::Green,
		"YOU WON"
	);
}

