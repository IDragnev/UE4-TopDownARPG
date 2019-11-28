// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Ability.h"
#include "AreaSlowDownAbility.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNARPG_API UAreaSlowDownAbility : public UAbility
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, meta=(ClampMin="1.0"))
	float DistanceFromSourceCoefficient = 100.0f;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ASlowDownArea> SlowDownAreaClass;

public:
	void Activate(AActor* Source) override;
};
