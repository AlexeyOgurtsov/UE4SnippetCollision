#include "DefaultMeshActor_NoProxPrim.h"
#include "ImplHelperLib.h"
#include "../CollisionActorConfig.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Components/SphereComponent.h"

using namespace CollisionActorConfig;

ADefaultMeshActor_NoProxPrim::ADefaultMeshActor_NoProxPrim()
{
	// WARNING!!! Wrong!!! Never make the SceneComponent as the ROOT,
	// otherwise will be NO collision!
	// The collision component must be at the ROOT!!!
	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));

	InitMesh(nullptr);
	RootComponent = Mesh;
	RootSceneComponent->SetupAttachment(RootComponent);
	InitCameraAndSpringArm(RootComponent);
}

void ADefaultMeshActor_NoProxPrim::BeginPlay()
{
	Super::BeginPlay();
	UImplHelperLib::ColorByCollisionProfile(Mesh);
}

void ADefaultMeshActor_NoProxPrim::InitCameraAndSpringArm(USceneComponent* InAttachTo)
{
	//checkf(InAttachTo, TEXT("When calling %s component to attach to must be non-NULL pointer"), TEXT(__FUNCTION__));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->TargetArmLength = CollisionActorConfig::Default::SPRINGARM_TARGET_ARM_LENGTH;
	SpringArm->SetRelativeRotation(CollisionActorConfig::Default::SPRINGARM_RELATIVE_ROTATION);
	SpringArm->SetRelativeLocation(CollisionActorConfig::Default::SPRINGARM_RELATIVE_LOCATION);
	SpringArm->bEnableCameraLag = CollisionActorConfig::Default::SPRINGARM_ENABLE_CAMERA_LAG;
	SpringArm->CameraLagSpeed = CollisionActorConfig::Default::SPRINGARM_CAMERA_LAG_SPEED;

	if(InAttachTo)
	{
		SpringArm->SetupAttachment(InAttachTo);
	}

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->bUsePawnControlRotation = true;
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}

void ADefaultMeshActor_NoProxPrim::InitMesh(USceneComponent* InAttachTo)
{
	//checkf(InAttachTo, TEXT("When calling %s component to attach to must be non-NULL pointer"), TEXT(__FUNCTION__));

	static ConstructorHelpers::FObjectFinderOptional<UStaticMesh> MeshFinder { CollisionActorConfig::Default::MESH_ASSET_PATH };
	M_LOG_ERROR_IF( ! MeshFinder.Succeeded(), TEXT("CollisionActorConfig::Default mesh (\"%s\") NOT found"), CollisionActorConfig::Default::MESH_ASSET_PATH);

	{
		Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

		if(MeshFinder.Succeeded())
		{
			M_LOG(TEXT("CollisionActorConfig::Default mesh (\"%s\") found, setting it up"), CollisionActorConfig::Default::MESH_ASSET_PATH);
			Mesh->SetStaticMesh(MeshFinder.Get());
		}

		if(InAttachTo)
		{
			Mesh->SetupAttachment(InAttachTo);
		}
	}
}
