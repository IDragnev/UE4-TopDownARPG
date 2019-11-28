// Fill out your copyright notice in the Description page of Project Settings.


#include "AreaSlowDownAbility.h"
#include "Components/SphereComponent.h"
#include "TopDownARPG.h"
#include "Engine/World.h"
#include "Triggers/SlowDownArea.h"

void UAreaSlowDownAbility::Activate(AActor* Source)
{
	Super::Activate(Source);

	auto* World = GetWorld();
	if (!IsValid(World))
	{
		UE_LOG(LogTopDownARPG, Error, TEXT("In UAreaSlowDownAbility::Activate - failed to access World"));
		return;
	}

	const auto SpawnParameters = [] {
		auto Params = FActorSpawnParameters{};
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		return Params;
	} ();
	const auto SpawnLocation = Source->GetActorLocation() + Source->GetActorForwardVector() * DistanceFromSourceCoefficient;
	const auto SpawnRotation = Source->GetActorRotation();
	const auto* SlowDownArea = World->SpawnActor<AActor>(SlowDownAreaClass, SpawnLocation, SpawnRotation, SpawnParameters);
	
	if (!IsValid(SlowDownArea))
	{
		UE_LOG(LogTopDownARPG, Error, TEXT("In UAreaSlowDownAbility::Activate - failed to spawn the slow down area actor"));
		return;
	}
}
