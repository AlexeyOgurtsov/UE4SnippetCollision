#include "DefaultMeshActor.h"

#include "ImplHelperLib.h"

#include "Util/TestUtil/VisibleActorConfig.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Components/SphereComponent.h"


// WARNING!!! Very important (already included by the impl helper)
//#include "Engine/CollisionProfile.h"


ADefaultMeshActor::ADefaultMeshActor()
{
	InitMesh(nullptr);
	RootComponent = Mesh;
	InitCameraAndSpringArm(Mesh);
	InitProxSphere(Mesh);
}

void ADefaultMeshActor::BeginPlay()
{
	Super::BeginPlay();
	UImplHelperLib::ColorByCollisionProfile(Mesh);
}

void ADefaultMeshActor::InitCameraAndSpringArm(USceneComponent* InAttachTo)
{
	checkf(InAttachTo, TEXT("When calling %s component to attach to must be non-NULL pointer"), TEXT(__FUNCTION__));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->TargetArmLength = CollisionActorConfig::Default::SPRINGARM_TARGET_ARM_LENGTH;
	SpringArm->SetRelativeRotation(CollisionActorConfig::Default::SPRINGARM_RELATIVE_ROTATION);
	SpringArm->SetRelativeLocation(CollisionActorConfig::Default::SPRINGARM_RELATIVE_LOCATION);
	SpringArm->bEnableCameraLag = CollisionActorConfig::Default::SPRINGARM_ENABLE_CAMERA_LAG;
	SpringArm->CameraLagSpeed = CollisionActorConfig::Default::SPRINGARM_CAMERA_LAG_SPEED;
	SpringArm->SetupAttachment(InAttachTo);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->bUsePawnControlRotation = true;
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}

void ADefaultMeshActor::InitMesh(USceneComponent* InAttachTo)
{
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

void ADefaultMeshActor::InitProxSphere(USceneComponent* InAttachTo)
{
	checkf(InAttachTo, TEXT("When calling %s component to attach to must be non-NULL pointer"), TEXT(__FUNCTION__));

	ProxSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	ProxSphere->InitSphereRadius(CollisionActorConfig::Default::PROX_SPHERE_RADIUS);
	ProxSphere->SetRelativeLocation(CollisionActorConfig::Default::MESH_REAL_CENTER_ACTOR_SPACE_LOCATION);
	ProxSphere->SetupAttachment(InAttachTo);
}
