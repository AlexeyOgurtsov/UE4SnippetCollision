#include "CollMeshActor_BlockAll_PrimAtRoot.h"

#include "ImplHelperLib.h"
#include "Util/TestUtil/VisibleActorConfig.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Components/SphereComponent.h"


// WARNING!! Otherwise UCollisionProfile is NOT available by default!
// (already included by the impl helper)
//#include "Engine/CollisionProfile.h"

using namespace VisibleActorConfig;

ACollMeshActor_BlockAll_PrimAtRoot::ACollMeshActor_BlockAll_PrimAtRoot()
{
	InitProxSphere(nullptr);
	RootComponent = ProxSphere;
	InitMesh(ProxSphere);
	InitCameraAndSpringArm(ProxSphere);
}

void ACollMeshActor_BlockAll_PrimAtRoot::BeginPlay()
{
	Super::BeginPlay();
	UImplHelperLib::ColorByCollisionProfile(Mesh);
}

void ACollMeshActor_BlockAll_PrimAtRoot::InitCameraAndSpringArm(USceneComponent* InAttachTo)
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

void ACollMeshActor_BlockAll_PrimAtRoot::InitMesh(USceneComponent* InAttachTo)
{
	//checkf(InAttachTo, TEXT("When calling %s component to attach to must be non-NULL pointer"), TEXT(__FUNCTION__));


	static ConstructorHelpers::FObjectFinderOptional<UStaticMesh> MeshFinder { Default::MESH_ASSET_PATH };
	M_LOG_ERROR_IF( ! MeshFinder.Succeeded(), TEXT("Default mesh (\"%s\") NOT found"), Default::MESH_ASSET_PATH);

	Mesh = UImplHelperLib::CreateSM_WithProfile(MeshFinder, UCollisionProfile::BlockAll_ProfileName, InAttachTo, this);

}

void ACollMeshActor_BlockAll_PrimAtRoot::InitProxSphere(USceneComponent* InAttachTo)
{
	//checkf(InAttachTo, TEXT("When calling %s component to attach to must be non-NULL pointer"), TEXT(__FUNCTION__));

	ProxSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	ProxSphere->InitSphereRadius(Default::PROX_SPHERE_RADIUS);
	ProxSphere->SetRelativeLocation(Default::MESH_REAL_CENTER_ACTOR_SPACE_LOCATION);
	if(InAttachTo)
	{
		ProxSphere->SetupAttachment(InAttachTo);
	}
}
