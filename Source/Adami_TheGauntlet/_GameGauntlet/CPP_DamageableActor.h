// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Damageable.h"
#include "GameFramework/Actor.h"
#include "CPP_DamageableActor.generated.h"

UCLASS()
class ADAMI_THEGAUNTLET_API ACPP_DamageableActor : public AActor, public IDamageable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_DamageableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DamageableActor")
	float MaxHealth = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DamageableActor")
	float CurrentHealth;

	virtual void TakeDamage_Implementation(float DamageAmount) override;

};
