#include "CollPawn.h"
#include "CollPlayerController.h"
#include "CollConfig.h"

#include "Util/Core/Phys/PhysUtilLib.h"
#include "Util/Core/LogUtilLib.h"

#include "GameFramework/FloatingPawnMovement.h"

#include "Engine/World.h"
#include "CollisionQueryParams.h"

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
			constexpr float DISTANCE = 500.0F;
		} // Trace

		namespace Mov
		{
			constexpr float SPEED = 100.0F;
		} // Mov
	} // Config

	void AddActorWorldOffset_Logged(AActor* Actor, const FVector& InOffset, bool bSweep = true, FHitResult* pOutHitResult = nullptr, ETeleportType Teleport = ETeleportType::None)
	{
		M_LOGFUNC_MSG(TEXT("AddActorWorldOffset"))
		ULogUtilLib::LogKeyedNameClassSafeC(TEXT("Actor"), Actor);
		ULogUtilLib::LogVectorC(TEXT("Offset"), InOffset);
		ULogUtilLib::LogYesNoC(TEXT("bSweep"), bSweep);
		if(Actor)
		{
			Actor->AddActorWorldOffset(InOffset, bSweep, pOutHitResult, Teleport);
			FHitResult TempHit;
			FHitResult* Hit = pOutHitResult ? pOutHitResult : &TempHit;
			UPhysUtilLib::LogHitResult(*Hit);
		}
	}
	void AddActorOffsetInLookDirection(AActor* Actor, float InSpeed, bool bSweep = true, FHitResult* pOutHitResult = nullptr, ETeleportType Teleport = ETeleportType::None)
	{
		M_LOGFUNC();

		if(Actor == nullptr)
		{
			M_LOG(TEXT("Actor is nullptr"));
			return;
		}

		FVector EyeLocation;
		FRotator EyeRotation;
		Actor->GetActorEyesViewPoint(EyeLocation, EyeRotation);

		FVector const Offset = EyeRotation.Vector() * InSpeed;
		AddActorWorldOffset_Logged(Actor, Offset, bSweep, pOutHitResult, Teleport);
	}
} // anonymous

MyPawnType::ACollPawn()
{
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
	AddActorOffsetInLookDirection(this, Speed, bSweep);	
}


void ACollPawn::CustomMoveActor()
{
	M_TO_BE_IMPL(TEXT("CustomMoveActor"));
}


void ACollPawn::ForceActor()
{
	M_TO_BE_IMPL(TEXT("ForceActor"));
}


void ACollPawn::CustomForceActor()
{
	M_TO_BE_IMPL(TEXT("CustomForceActor"));
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
	if( (ActorDragMode == EActorDragMode::On ) && SelectedActor != nullptr)
	{
		bool const bSweep = false;
		FTransform const NewTransform = ActorDragTransform * GetActorTransform();
		ULogUtilLib::LogTransformC(TEXT("NewActorTransform"), NewTransform);
		SelectedActor->SetActorTransform(NewTransform, bSweep);
	}
}

void ACollPawn::SetActorDragMode(EActorDragMode NewDragMode)
{
	M_LOGFUNC();
	if(SelectedActor == nullptr)
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
	check(SelectedActor);
	M_LOG(TEXT("DragMode: On"));
	if(ActorDragMode == EActorDragMode::On)
	{
		return;
	}
	ActorDragTransform = SelectedActor->GetActorTransform() * GetActorTransform().Inverse();
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
	if(SelectedActor == nullptr)
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
	SelectByLook(ECollisionChannel::ECC_WorldDynamic);
}


void ACollPawn::SelectByLook_WorldStatic()
{
	SelectByLook(ECollisionChannel::ECC_WorldStatic);
}


void ACollPawn::SelectByLook_Camera()
{
	SelectByLook(ECollisionChannel::ECC_Camera);
}


void ACollPawn::SelectByLook_PhysicsBody()
{
	SelectByLook(ECollisionChannel::ECC_PhysicsBody);
}


void ACollPawn::SelectByLook_VisibilityChannel()
{
	SelectByLook(ECollisionChannel::ECC_Visibility);
}


void ACollPawn::SelectActor(AActor* Actor)
{
	SelectedActor = Actor;
	GetMyPCChecked()->Pawn_SelectedActorChanged();
}


AActor* ACollPawn::TraceByLook(ECollisionChannel InChannel)
{
	M_LOGFUNC();

	FVector EyeLocation;
	FRotator EyeRotation;
	GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FHitResult Hit;
	FVector const LineStart = EyeLocation;
	FVector const Direction = EyeRotation.Vector();
	FVector const LineEnd = LineStart + Config::Trace::DISTANCE * Direction;

	bool const bTraceComplex = false;
	AActor* const IgnoreActor = this;
	FCollisionQueryParams QueryParams { TEXT("TraceTag"), bTraceComplex, IgnoreActor };
	FCollisionResponseParams ResponseParams { ECollisionResponse::ECR_Block };

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

