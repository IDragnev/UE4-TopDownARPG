#include "SlowDownArea.h"
#include "Components/SphereComponent.h"
#include "TopDownARPG.h"
#include "TopDownARPGCharacter.h"

ASlowDownArea::ASlowDownArea()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	SphereComponent = [area = this] {
		auto* Sphere = area->CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
		Sphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		Sphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
		Sphere->OnComponentBeginOverlap.AddUniqueDynamic(area, &ASlowDownArea::OnBeginOverlap);
		Sphere->OnComponentEndOverlap.AddUniqueDynamic(area, &ASlowDownArea::OnEndOverlap);
		return Sphere;
	} ();

	RootComponent = SphereComponent;
}

void ASlowDownArea::BeginPlay()
{
	Super::BeginPlay();
	
	const auto* World = GetWorld();
	if (!IsValid(World))
	{
		UE_LOG(LogTopDownARPG, Error, TEXT("In ASlowDownArea::BeginPlay - failed to access World"));
		return;
	}

	TimerManager = &World->GetTimerManager();
	TimerManager->SetTimer(LifeTimeTimerHandle, this, &ASlowDownArea::OnLifeTimeExpired, Lifetime);
}

void ASlowDownArea::OnLifeTimeExpired()
{
	const auto destroyed = Destroy();
	if (!destroyed)
	{
		UE_LOG(LogTopDownARPG, Error, TEXT("ASlowDownArea is indestructible"));
	}
}

void ASlowDownArea::BeginDestroy()
{
	if (TimerManager)
	{
		TimerManager->ClearTimer(LifeTimeTimerHandle);
		TimerManager = nullptr;
	}
	Super::BeginDestroy();
}

void ASlowDownArea::OnBeginOverlap(UPrimitiveComponent*, AActor* Other, UPrimitiveComponent*, int32, bool, const FHitResult&)
{
	if (IsValid(Other))
	{
		Other->CustomTimeDilation = TimeDilationOnEnter;
	}
}

void ASlowDownArea::OnEndOverlap(UPrimitiveComponent*, AActor* Other, UPrimitiveComponent*, int32)
{
	if (IsValid(Other))
	{
		Other->CustomTimeDilation = TimeDilationOnExit;
	}
}