#include "CollActor.h"
#include "Components/SphereComponent.h"
#include "Util/Core/LogUtilLib.h"

ACollActor::ACollActor()
{
	RootComponent = InitSphere(nullptr);
}

void ACollActor::BeginPlay()
{
	M_LOGFUNC();
	Super::BeginPlay();
}

USphereComponent* ACollActor::InitSphere(UActorComponent* InParent)
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SphereComponent->InitSphereRadius(100.0f);
	return SphereComponent;
}
