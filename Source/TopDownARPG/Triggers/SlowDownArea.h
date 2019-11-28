// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "SlowDownArea.generated.h"

UCLASS()
class TOPDOWNARPG_API ASlowDownArea : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, meta=(ClampMin="0.1", ClampMax="1.0"))
	float TimeDilationOnEnter = 1.0f;
	
	UPROPERTY(EditDefaultsOnly, meta=(ClampMin="0.1"))
	float TimeDilationOnExit = 1.0f;
	
	UPROPERTY(EditDefaultsOnly, meta=(ClampMin="1.0"))
	float Lifetime = 5.0f;
	
	UPROPERTY(VisibleAnywhere, Category = Gameplay)
	class USphereComponent* SphereComponent;

public:	
	ASlowDownArea();

private:
	void BeginPlay() override;
	void BeginDestroy() override;

	void OnLifeTimeExpired();

private:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp,
						AActor* Other,
						UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex,
						bool bFromSweep,
						const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComp, 
				      AActor* OtherActor, 
				      UPrimitiveComponent* OtherComp, 
				      int32 OtherBodyIndex);

private:
	FTimerManager* TimerManager = nullptr;
	FTimerHandle LifeTimeTimerHandle;
};
