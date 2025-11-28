// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_TimeButton.h"
#include "GameFramework/Actor.h"
#include "CPP_TimePlatform.generated.h"

UCLASS()
class ADAMI_THEGAUNTLET_API ACPP_TimePlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_TimePlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool IsActive = false;
	float TimeElapsed = 0;

	FTimerHandle TimerHandle_Platform;

public:	
	// Called every frame
	// virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable, Category = "TimePlatform")
	void ActivatePlatform();

	UFUNCTION(BlueprintCallable, Category = "TimePlatform")
	void DeactivatePlatform();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimePlatform")
	float TimeDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimePlatform")
	ACPP_TimeButton* LinkedButton;
};
