#include "TestPawn_SphereIsRoot_BlockAll.h"

#include "ImplHelperLib.h"

#include "Util/TestUtil/I/ITUController.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Components/SphereComponent.h"

ATestPawn_SphereIsRoot_BlockAll::ATestPawn_SphereIsRoot_BlockAll()
{
	InitProxSphere(ProxSphere);
	RootComponent = ProxSphere;
	InitMesh(RootComponent);
}

void ATestPawn_SphereIsRoot_BlockAll::BeginPlay()
{
	Super::BeginPlay();
	UImplHelperLib::ColorByCollisionProfile(Mesh);
}

void ATestPawn_SphereIsRoot_BlockAll::InitMesh(USceneComponent* InAttachTo)
{
	static ConstructorHelpers::FObjectFinderOptional<UStaticMesh> MeshFinder { VisibleActorConfig::Default::MESH_ASSET_PATH };
	M_LOG_ERROR_IF( ! MeshFinder.Succeeded(), TEXT("Default mesh (\"%s\") NOT found"), VisibleActorConfig::Default::MESH_ASSET_PATH);

	Mesh = UImplHelperLib::CreateSM_WithProfile(MeshFinder, UCollisionProfile::BlockAll_ProfileName, InAttachTo, this);
}

void ATestPawn_SphereIsRoot_BlockAll::InitProxSphere(USceneComponent* InAttachTo)
{
	ProxSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	ProxSphere->InitSphereRadius(VisibleActorConfig::Default::PROX_SPHERE_RADIUS);
	ProxSphere->SetRelativeLocation(VisibleActorConfig::Default::MESH_REAL_CENTER_ACTOR_SPACE_LOCATION);
	if(InAttachTo)
	{
		ProxSphere->SetupAttachment(InAttachTo);
	}
}
