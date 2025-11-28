// Fill out your copyright notice in the Description page of Project Settings.


#include "_GameGauntlet/CPP_TimeButton.h"

// Sets default values
ACPP_TimeButton::ACPP_TimeButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACPP_TimeButton::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_TimeButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPP_TimeButton::Interact_Implementation(AActor* Interactor)
{
	GEngine->AddOnScreenDebugMessage(
		-1,
		2.0f,
		FColor::Blue,
		"Button Interact"
	);
	
	if (OnPressedDynamic.IsBound())
	{
		OnPressedDynamic.Broadcast();
	}
}