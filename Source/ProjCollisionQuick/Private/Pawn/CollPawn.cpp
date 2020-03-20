#include "CollPawn.h"
#include "../CollPlayerController.h"
#include "../CollConfig.h"

#include "Util/Core/Phys/PhysUtilLib.h"

#include "GameFramework/FloatingPawnMovement.h"

#include "Components/PrimitiveComponent.h" // To make casts work properly

#include "Engine/World.h"
#include "CollisionQueryParams.h"

#include "DrawDebugHelpers.h"

/**
* TODO Fix: Movement
* 1. Floating pawn movement: does it work by default (seems like not)?
*/

namespace
{
	namespace Config
	{
		constexpr float MAX_SPEED = 100.0F;
		constexpr float ACCELERATION = 0.0F;
		constexpr float DECELERATION = 0.0F;


		namespace Trace
		{
			constexpr float DISTANCE = 700.0F;
		} // Trace

		namespace Mov
		{
			constexpr float SPEED = 100.0F;

			constexpr float FORCE = 1000.0F;
			constexpr float VEL_CHANGE = 100.0F;
		} // Mov
	} // Config


	void AddComponentForce_Logged(UPrimitiveComponent* Component, const FVector& InForce, const FName& InBoneName, bool bVelChange = false)
	{
		M_LOGFUNC_MSG(TEXT("Component->AddForce"))
		ULogUtilLib::LogKeyedNameClassSafeC(TEXT("Component"), Component);
		if(Component)
		{
			ULogUtilLib::LogKeyedNameClassSafeC(TEXT("Component->GetOwner()"), Component->GetOwner());
		}
		ULogUtilLib::LogVectorC(TEXT("Force"), InForce);
		ULogUtilLib::LogNameC(TEXT("BoneName"), InBoneName);
		ULogUtilLib::LogYesNoC(TEXT("bVelChange"), bVelChange);
		if(Component)
		{
			Component->AddForce(InForce, InBoneName, bVelChange);
		}
	}
	void GetLookDirection(APawn* InstigatorPawn, FVector& OutLocation, FRotator& OutRotation)
	{
		check(InstigatorPawn);

		if( APlayerController* PC = Cast<APlayerController>(InstigatorPawn->Controller) )
		{
			return PC->GetPlayerViewPoint(OutLocation, OutRotation);
		}
		else
		{
			InstigatorPawn->GetActorEyesViewPoint(OutLocation, OutRotation);
		}
	}
	void AddForceInLookDirection(AActor* InstigatorActor, AActor* Actor, float InMagnitude, bool bVelChange = false, FHitResult* pOutHitResult = nullptr, ETeleportType Teleport = ETeleportType::None)
	{
		M_LOGFUNC();

		if(InstigatorActor == nullptr)
		{
			M_LOG(TEXT("InstigatorActor is nullptr"));
			return;
		}

		if(Actor == nullptr)
		{
			M_LOG(TEXT("Actor is nullptr"));
			return;
		}

		UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
		if(Component == nullptr)
		{
			Component = Actor->FindComponentByClass<UPrimitiveComponent>();
		}
		else
		{
			M_LOG(TEXT("Using first found RootComponent (it's primitive component)"));
		}
		if(Component == nullptr)
		{
			M_LOG(TEXT("No UPrimitiveComponent in the actor"));
			return;
		}
		else
		{
			M_LOG(TEXT("Using first found PrimitiveComponent"));
		}

		FVector EyeLocation;
		FRotator EyeRotation;
		GetLookDirection(Cast<APawn>(InstigatorActor), EyeLocation, EyeRotation);

		FName const BoneName = NAME_None;
		FVector const Force = EyeRotation.Vector() * InMagnitude;
		AddComponentForce_Logged(Component, Force, BoneName, bVelChange);
	}
	void AddActorWorldOffset_Logged(AActor* Actor, const FVector& InOffset, bool bSweep = true, FHitResult* pOutHitResult = nullptr, ETeleportType Teleport = ETeleportType::None)
	{
		M_LOGFUNC_MSG(TEXT("AddActorWorldOffset"));
		ULogUtilLib::LogKeyedNameClassSafeC(TEXT("Actor"), Actor);
		ULogUtilLib::LogVectorC(TEXT("Offset"), InOffset);
		ULogUtilLib::LogYesNoC(TEXT("bSweep"), bSweep);
		if(Actor)
		{
			FHitResult TempHit;
			FHitResult* Hit = pOutHitResult ? pOutHitResult : &TempHit;
			Actor->AddActorWorldOffset(InOffset, bSweep, Hit, Teleport);
			UPhysUtilLib::LogHitResult(*Hit);
		}
	}
	void AddActorOffsetInLookDirection(AActor* InstigatorActor, AActor* Actor, float InSpeed, bool bSweep = true, FHitResult* pOutHitResult = nullptr, ETeleportType Teleport = ETeleportType::None)
	{
		M_LOGFUNC();

		if(InstigatorActor == nullptr)
		{
			M_LOG(TEXT("InstigatorActor is nullptr"));
			return;
		}

		if(Actor == nullptr)
		{
			M_LOG(TEXT("Actor is nullptr"));
			return;
		}

		FVector EyeLocation;
		FRotator EyeRotation;
		GetLookDirection(Cast<APawn>(InstigatorActor), EyeLocation, EyeRotation);

		FVector const Offset = EyeRotation.Vector() * InSpeed;
		AddActorWorldOffset_Logged(Actor, Offset, bSweep, pOutHitResult, Teleport);
	}
} // anonymous

MyPawnType::ACollPawn()
{
	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;

	InitMovement();
}
void MyPawnType::MyBeginPlay_Implementation()
{
	M_LOGFUNC();

	Super::MyBeginPlay_Implementation();
	// Custom actions here
}

void MyPawnType::InitMovement()
{
	M_LOGFUNC();
	UFloatingPawnMovement* const MyMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
	MyMovement->Acceleration = Config::ACCELERATION;
	MyMovement->Deceleration = Config::DECELERATION;
	MyMovement->MaxSpeed = Config::MAX_SPEED;
	Movement = MyMovement;
}

MyPCType* MyPawnType::GetMyPC() const
{
	return Cast<MyPCType>(GetController());
}

MyPCType* MyPawnType::GetMyPCLogged(ELogFlags InLogFlags) const
{
	MyPCType* const PC = GetMyPC();
	if(PC == nullptr)
	{
		M_LOG_ERROR_IF_FLAGS(InLogFlags, TEXT("GetMyPC() returned NULL"));
	}
	return PC;
}

MyPCType* MyPawnType::GetMyPCChecked() const
{
	MyPCType* const PC = GetMyPC();
	checkf(PC, TEXT("GetMyPawn must return non-NULL pawn!"));
	return PC;
}

void ACollPawn::ActorCustomActionThree()
{
	M_TO_BE_IMPL(TEXT("impl"));
}


void ACollPawn::ActorCustomActionTwo()
{
	M_TO_BE_IMPL(TEXT("impl"));
}


void ACollPawn::ActorCustomAction()
{
	M_TO_BE_IMPL(TEXT("impl"));
}


void ACollPawn::MoveActor()
{
	M_LOGFUNC();

	bool const bSweep = true;
	float const Speed = Config::Mov::SPEED;
	AddActorOffsetInLookDirection(this, GetSelectedActor(), Speed, bSweep);	
}


void ACollPawn::CustomMoveActor()
{
	M_LOGFUNC_MSG(TEXT("Moving actor without sweep"));
	bool const bSweep = false;
	float const Speed = Config::Mov::SPEED;
	AddActorOffsetInLookDirection(this, GetSelectedActor(), Speed, bSweep);	
}


void ACollPawn::ForceActor()
{
	bool const bVelChange = false;
	AddForceInLookDirection(this, GetSelectedActor(), Config::Mov::FORCE, bVelChange);
}


void ACollPawn::CustomForceActor()
{
	bool const bVelChange = true;
	AddForceInLookDirection(this, GetSelectedActor(), Config::Mov::VEL_CHANGE, bVelChange);
}


bool ACollPawn::CanSelectByLook() const
{
	return true;
}

void ACollPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UpdateDraggedActor();
}

void ACollPawn::UpdateDraggedActor()
{
	if((ActorDragMode == EActorDragMode::On ) && ( wpSelectedActor.Get() == nullptr ))
	{
		DisableActorDragMode();	
		return;
	}
	AActor* const DraggedActor = wpSelectedActor.Get();

	if( (ActorDragMode == EActorDragMode::On ) )
	{
		bool const bSweep = false;
		FTransform const NewTransform = ActorDragTransform * GetActorTransform();
		ULogUtilLib::LogTransformC(TEXT("NewActorTransform"), NewTransform);
		DraggedActor->SetActorTransform(NewTransform, bSweep);
	}
}

void ACollPawn::SetActorDragMode(EActorDragMode NewDragMode)
{
	M_LOGFUNC();
	if(wpSelectedActor.Get() == nullptr)
	{
		DisableActorDragMode();
	}

	ActorDragMode = NewDragMode;

	switch(ActorDragMode)
	{
	case EActorDragMode::Off:
		DisableActorDragMode();
		break;

	case EActorDragMode::On:
		EnableActorDragMode();
		break;

	default:
		M_NOT_IMPL_MSG(TEXT("Unknown EActorDragMode"));
		break;
	}

}

void ACollPawn::EnableActorDragMode()
{
	M_LOGFUNC();
	check(wpSelectedActor.Get());
	M_LOG(TEXT("DragMode: On"));
	if(ActorDragMode == EActorDragMode::On)
	{
		return;
	}
	ActorDragTransform = wpSelectedActor->GetActorTransform() * GetActorTransform().Inverse();
	ULogUtilLib::LogTransformC(TEXT("ActorDragTransform"), ActorDragTransform);
	GetMyPCChecked()->Pawn_DragActorModeChanged();
}

void ACollPawn::DisableActorDragMode()
{
	M_LOGFUNC();
	M_LOG(TEXT("DragMode: Off"));
	if(ActorDragMode == EActorDragMode::Off)
	{
		return;
	}
	ActorDragMode = EActorDragMode::Off;
	GetMyPCChecked()->Pawn_DragActorModeChanged();
}

bool ACollPawn::CanDrag() const
{
	if(wpSelectedActor == nullptr)
	{
		M_LOG(TEXT("Cannot drag: selected actor is nullptr"));
		return false;
	}

	return true;
}


void ACollPawn::ToggleDrag()
{
	M_LOGFUNC_MSG(TEXT("Toggling DRAG mode"));
	EActorDragMode const NewDragMode = (EActorDragMode::On == ActorDragMode) ? EActorDragMode::Off : EActorDragMode::On;
	if( ( NewDragMode == EActorDragMode::On ) && ! CanDrag() )
	{
		M_LOG_WARN(TEXT("Toggling drag mode skipped"));
		return;
	}
	SetActorDragMode(NewDragMode);
}


void ACollPawn::SelectByLookCustom()
{
	M_TO_BE_IMPL(TEXT("SelectByLookCustom"))
}

void ACollPawn::SelectByLook_WorldDynamic()
{
	M_LOG(TEXT("SelectByLook_WorldDynamic"));
	SelectByLook(ECollisionChannel::ECC_WorldDynamic);
}


void ACollPawn::SelectByLook_WorldStatic()
{
	M_LOG(TEXT("SelectByLook_WorldStatic"));
	SelectByLook(ECollisionChannel::ECC_WorldStatic);
}


void ACollPawn::SelectByLook_Camera()
{
	M_LOG(TEXT("SelectByLook_Camera"));
	SelectByLook(ECollisionChannel::ECC_Camera);
}


void ACollPawn::SelectByLook_PhysicsBody()
{
	M_LOG(TEXT("SelectByLook_PhysicsBody"));
	SelectByLook(ECollisionChannel::ECC_PhysicsBody);
}


void ACollPawn::SelectByLook_VisibilityChannel()
{
	M_LOG(TEXT("SelectByLook_VisibilityChannel"));
	SelectByLook(ECollisionChannel::ECC_Visibility);
}


void ACollPawn::SelectActor(AActor* Actor)
{
	wpSelectedActor = Actor;
	GetMyPCChecked()->Pawn_SelectedActorChanged();
}


AActor* ACollPawn::TraceByLook(ECollisionChannel InChannel)
{
	M_LOGFUNC();

	FVector EyeLocation;
	FRotator EyeRotation;
	GetLookDirection(this, EyeLocation, EyeRotation);

	M_LOG(TEXT("Trace mode: %s"), bTraceComplex ? TEXT("YES (Tracing complex)") : TEXT("false (simple tracing)"));

	ULogUtilLib::LogVectorC(TEXT("EyeLocation"), EyeLocation);
	ULogUtilLib::LogRotatorC(TEXT("EyeRotation"), EyeRotation);
	ULogUtilLib::LogVectorC(TEXT("EyeRotation.Vector()"), EyeRotation.Vector());

	FHitResult Hit;
	FVector const LineStart = EyeLocation;
	FVector const Direction = EyeRotation.Vector();
	FVector const LineEnd = LineStart + Config::Trace::DISTANCE * Direction;
	ULogUtilLib::LogVectorC(TEXT("LineStart"), LineStart);
	ULogUtilLib::LogVectorC(TEXT("LineEnd"), LineEnd);
	ULogUtilLib::LogVectorC(TEXT("Direction"), Direction);

	AActor* const IgnoreActor = this;
	FCollisionQueryParams QueryParams { TEXT("TraceTag"), bTraceComplex, IgnoreActor };
	FCollisionResponseParams ResponseParams { ECollisionResponse::ECR_Block };

	bool const bPersistentLines = false;
	float const LineLifetime = 5.0F;
	uint8 const LineDepthPriority = 0;
	float const LineThickness = 10.0F;
	DrawDebugLine(GetWorld(), LineStart, LineEnd, FColor(255, 0.0F, 0.0F), bPersistentLines, LineLifetime, LineDepthPriority, LineThickness);

	bool bBlockingHitFound = GetWorld()->LineTraceSingleByChannel
	(
	 	Hit,
		LineStart, LineEnd,
		InChannel,
		QueryParams,
		ResponseParams
	);
	ULogUtilLib::LogYesNoC(TEXT("bBlockingHitFound"), bBlockingHitFound);
	UPhysUtilLib::LogHitResult(Hit);
	if( ! bBlockingHitFound )
	{
		return nullptr;
	}
	else
	{
		return Hit.Actor.Get();
	}
}


void ACollPawn::SelectByLook(ECollisionChannel InChannel)
{
	AActor* const TracedActor = TraceByLook(InChannel);
	SelectActor(TracedActor);
}

void ACollPawn::ToggleTraceComplex()
{
	M_LOGFUNC();

	bTraceComplex = ! bTraceComplex;
	M_LOG(TEXT("Toggled trace mode to: %s"), bTraceComplex ? TEXT("YES (Tracing complex)") : TEXT("false (simple tracing)"));
}
