// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "GameFramework/Actor.h"
#include "CPP_TimeButton.generated.h"

// Dichiarazione Dynamic Multicast Delegate (Esposto a Blueprint, serializzabile)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPressedDynamicSignature);

UCLASS()
class ADAMI_THEGAUNTLET_API ACPP_TimeButton : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_TimeButton();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact_Implementation(AActor* Interactor) override;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnPressedDynamicSignature OnPressedDynamic;
};
