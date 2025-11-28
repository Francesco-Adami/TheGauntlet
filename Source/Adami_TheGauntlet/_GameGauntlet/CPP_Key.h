// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Collectible.h"
#include "GameFramework/Actor.h"
#include "CPP_Key.generated.h"

UCLASS()
class ADAMI_THEGAUNTLET_API ACPP_Key : public AActor, public ICollectible
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_Key();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnCollect_Implementation(AAdami_TheGauntletCharacter* Player) override;
};
