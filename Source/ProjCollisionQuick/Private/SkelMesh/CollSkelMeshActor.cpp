#include "CollSkelMeshActor.h"
#include "ImplHelperLib.h"
#include "Util/TestUtil/VisibleActorConfig.h"
#include "Util/Core/LogUtilLib.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"

#include "UObject/ConstructorHelpers.h"

using namespace VisibleActorConfig;

constexpr const TCHAR* SKEL_MESH_PATH = TEXT("SkeletalMesh'/Game/SkelMesh/Turret/SkelAnimTurret.SkelAnimTurret'");

ACollSkelMeshActor::ACollSkelMeshActor()
{
	InitMesh(nullptr);
	RootComponent = Mesh;
	InitProxSphere(Mesh);
	InitCameraAndSpringArm(RootSceneComponent);
}


void ACollSkelMeshActor::BeginPlay()
{
	Super::BeginPlay();
	UImplHelperLib::ColorByCollisionProfile(Mesh);
}

void ACollSkelMeshActor::InitCameraAndSpringArm(USceneComponent* InAttachTo)
{
	//checkf(InAttachTo, TEXT("When calling %s component to attach to must be non-NULL pointer"), TEXT(__FUNCTION__));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->TargetArmLength = Default::SPRINGARM_TARGET_ARM_LENGTH;
	SpringArm->SetRelativeRotation(Default::SPRINGARM_RELATIVE_ROTATION);
	SpringArm->SetRelativeLocation(Default::SPRINGARM_RELATIVE_LOCATION);
	SpringArm->bEnableCameraLag = Default::SPRINGARM_ENABLE_CAMERA_LAG;
	SpringArm->CameraLagSpeed = Default::SPRINGARM_CAMERA_LAG_SPEED;
	SpringArm->SetupAttachment(InAttachTo);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->bUsePawnControlRotation = true;
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}

void ACollSkelMeshActor::InitMesh(USceneComponent* InAttachTo)
{
	static ConstructorHelpers::FObjectFinderOptional<USkeletalMesh> MeshFinder { SKEL_MESH_PATH };
	M_LOG_ERROR_IF( ! MeshFinder.Succeeded(), TEXT("Default mesh (\"%s\") NOT found"), Default::MESH_ASSET_PATH);

	{
		Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));

		if(MeshFinder.Succeeded())
		{
			M_LOG(TEXT("Default mesh (\"%s\") found, setting it up"), Default::MESH_ASSET_PATH);
			Mesh->SetSkeletalMesh(MeshFinder.Get(), /*bReInitPose*/true);
		}

		if(InAttachTo)
		{
			Mesh->SetupAttachment(InAttachTo);
		}
	}
}

void ACollSkelMeshActor::InitProxSphere(USceneComponent* InAttachTo)
{
	ProxSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	ProxSphere->InitSphereRadius(Default::PROX_SPHERE_RADIUS);
	ProxSphere->SetRelativeLocation(Default::MESH_REAL_CENTER_ACTOR_SPACE_LOCATION);
	if(InAttachTo)
	{
		ProxSphere->SetupAttachment(InAttachTo);
	}
}
