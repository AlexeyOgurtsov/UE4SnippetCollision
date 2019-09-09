#include "CollPlayerController.h"
#include "CollPawn.h"
#include "CollConfig.h"

#include "Util/Core/LogUtilLib.h"

MyPCType::ACollPlayerController()
{
}
 
void MyPCType::BeginPlay()
{
	M_LOGFUNC();

	Super::BeginPlay();
}


MyPawnType* MyPCType::GetMyPawn() const
{
	return Cast<MyPawnType>(GetPawn());
}

MyPawnType* MyPCType::GetMyPawnLogged(ELogFlags InLogFlags) const
{
	MyPawnType* const P = GetMyPawn();
	if(P == nullptr)
	{
		M_LOG_ERROR_IF_FLAGS(InLogFlags, TEXT("GetMyPawn() returned NULL"));
	}
	return P;
}

MyPawnType* MyPCType::GetMyPawnChecked() const
{
	MyPawnType* const P = GetMyPawn();
	checkf(P, TEXT("GetMyPawn must return non-NULL pawn!"));
	return P;
}

void MyPCType::Pawn_DragActorModeChanged()
{
	M_TO_BE_IMPL(TEXT("TODO"));
}


void MyPCType::Pawn_SelectedActorChanged()
{
	M_TO_BE_IMPL(TEXT("TODO"));
}
void MyPCType::Action_DebugOne()
{
	GetMyPawnChecked()->ActorCustomAction();
}

void MyPCType::Action_DebugTwo()
{
	GetMyPawnChecked()->ActorCustomActionTwo();
}

void MyPCType::Action_DebugThree()
{
	GetMyPawnChecked()->ActorCustomActionThree();
}

void MyPCType::Action_Use()
{
	GetMyPawnChecked()->ToggleDrag();
}

void MyPCType::Action_UseTwo()
{
	GetMyPawnChecked()->CustomForceActor();
}

void MyPCType::Action_UseThree()
{
	GetMyPawnChecked()->CustomMoveActor();
}

void MyPCType::Action_Fire()
{
	GetMyPawnChecked()->SelectByLookCustom();
}

void MyPCType::Action_FireTwo()
{
	GetMyPawnChecked()->ForceActor();
}

void MyPCType::Action_FireThree()
{
	GetMyPawnChecked()->MoveActor();
}
void MyPCType::Action_SelectZero()
{
	GetMyPawnChecked()->SelectByLookCustom();
}
void MyPCType::Action_SelectOne()
{
	GetMyPawnChecked()->SelectByLook_WorldDynamic();
}

void MyPCType::Action_SelectTwo()
{
	GetMyPawnChecked()->SelectByLook_WorldStatic();
}

void MyPCType::Action_SelectThree()
{
	GetMyPawnChecked()->SelectByLook_Camera();
}

void MyPCType::Action_SelectFour()
{
	GetMyPawnChecked()->SelectByLook_VisibilityChannel();
}

void MyPCType::Action_SelectFive()
{
	GetMyPawnChecked()->SelectByLook_PhysicsBody();
}

void MyPCType::Action_SelectSix()
{
	Super::Action_SelectSix();
}

void MyPCType::Action_SelectSeven()
{
	Super::Action_SelectSeven();
}

void MyPCType::Action_SelectEight()
{
	Super::Action_SelectEight();
}

void MyPCType::Action_SelectNine()
{
	Super::Action_SelectNine();
}
