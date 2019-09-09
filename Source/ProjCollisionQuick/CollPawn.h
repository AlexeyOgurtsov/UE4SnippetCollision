#pragma once

/**
* To be copied to the destination and changed.
*/

#include "Util/TestUtil/TUPawn.h"
#include "Util/Core/Log/MyLoggingTypes.h"
#include "CollPawn.generated.h"

/** EActorDragMode*/
UENUM(BlueprintType, Category=Misc)
enum class EActorDragMode : uint8
{
	/** Off*/
	Off UMETA(DisplayName="Off")
	
	/** On*/
	, On UMETA(DisplayName="On")
};

UCLASS()
class ACollPawn : public ATUPawn
{
	GENERATED_BODY()

	virtual void Tick(float DeltaSeconds) override;

	// ~Framework Begin
	virtual void MyBeginPlay_Implementation() override;
	// ~Framework End

	// ~Access helpers Begin
	UFUNCTION(BlueprintPure, Category = Controller)
	ACollPlayerController* GetMyPC() const;

	UFUNCTION(BlueprintPure, Category = Controller)
	ACollPlayerController* GetMyPCLogged(ELogFlags InLogFlags = ELogFlags::None) const;

	/**
	* Checks that the given pawn NOT null.
	*/
	UFUNCTION(BlueprintPure, Category = Controller)
	ACollPlayerController* GetMyPCChecked() const;
	// ~Access helpers End

public:
	ACollPawn();
	
	// ~ Trace Begin
	/** SelectByLook_WorldDynamic*/
	UFUNCTION(BlueprintCallable, Category=Selection)
	void SelectByLook_WorldDynamic();
	
	/** SelectByLook_WorldStatic*/
	UFUNCTION(BlueprintCallable, Category=Selection)
	void SelectByLook_WorldStatic();
	
	/** SelectByLook_Camera*/
	UFUNCTION(BlueprintCallable, Category=Selection)
	void SelectByLook_Camera();
	
	/** SelectByLook_VisibilityChannel*/
	UFUNCTION(BlueprintCallable, Category=Selection)
	void SelectByLook_VisibilityChannel();
	
	/** SelectByLook_PhysicsBody*/
	UFUNCTION(BlueprintCallable, Category=Selection)
	void SelectByLook_PhysicsBody();
	
	/** SelectByLookCustom*/
	UFUNCTION(BlueprintCallable, Category=Selection)
	void SelectByLookCustom();
	
	/** SelectByLook*/
	UFUNCTION(BlueprintCallable, Category=Selection)
	void SelectByLook(ECollisionChannel InChannel);
	
	/** CanSelectByLook*/
	UFUNCTION(BlueprintCallable, Category=Selection)
	bool CanSelectByLook() const;
	
	/** TraceByLook*/
	UFUNCTION(BlueprintCallable, Category=Trace)
	AActor* TraceByLook(ECollisionChannel InChannel);
	
	// ~ Trace End

	/** GetSelectedActor*/
	UFUNCTION(BlueprintPure, Category=Selection)
	AActor* GetSelectedActor() const
	{
		return SelectedActor;
	}
	
	// ~ ActorDrag Begin
	/** GetActorDragMode*/
	UFUNCTION(BlueprintPure, Category=ActorDrag)
	EActorDragMode GetActorDragMode() const
	{
		return ActorDragMode;
	}
	
	/** GetActorDragTransform*/
	UFUNCTION(BlueprintPure, Category=ActorDrag)
	FTransform GetActorDragTransform() const
	{
		return ActorDragTransform;
	}
	
	/** SetActorDragMode*/
	UFUNCTION(BlueprintCallable, Category=ActorDrag)
	void SetActorDragMode(EActorDragMode NewDragMode);
	
	/** ToggleDrag*/
	UFUNCTION(BlueprintCallable, Category=ActorDrag)
	void ToggleDrag();
	
	/** CanDrag*/
	UFUNCTION(BlueprintCallable, Category=ActorDrag)
	bool CanDrag() const;
	
	/** UpdateDraggedActor*/
	UFUNCTION(BlueprintCallable, Category=ActorDrag)
	void UpdateDraggedActor();
	
	// ~ ActorDrag End

	// ~ ActorMove Begin
	/** CustomForceActor*/
	UFUNCTION(BlueprintCallable, Category=ActorMove)
	void CustomForceActor();
	
	/** ForceActor*/
	UFUNCTION(BlueprintCallable, Category=ActorMove)
	void ForceActor();
	
	/** CustomMoveActor*/
	UFUNCTION(BlueprintCallable, Category=ActorMove)
	void CustomMoveActor();
	
	/** MoveActor*/
	UFUNCTION(BlueprintCallable, Category=ActorMove)
	void MoveActor();
	
	// ~ ActorMove End
	
	// ~ CustomAction Begin
	/** ActorCustomAction*/
	UFUNCTION(BlueprintCallable, Category=Misc)
	void ActorCustomAction();
	
	/** ActorCustomActionTwo*/
	UFUNCTION(BlueprintCallable, Category=Misc)
	void ActorCustomActionTwo();
	
	/** ActorCustomActionThree*/
	UFUNCTION(BlueprintCallable, Category=Misc)
	void ActorCustomActionThree();
	
	// ~ CustomAction End

private:
	// ~Motion Begin
	void InitMovement();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Motion, Meta=(AllowPrivateAccess = true))
	UPawnMovementComponent *Movement = nullptr;
	// ~Motion End
	
	// ~ Selection Begin
	/** SelectedActor*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(AllowPrivateAccess=true), Category=Selection)
	AActor* SelectedActor = nullptr;
	
	// ~ Selection End
	/** SelectActor*/
	UFUNCTION(BlueprintCallable, Category=Selection)
	void SelectActor(AActor* Actor);
	
	// ~ ActorDrag Begin
	/** EnableActorDragMode*/
	UFUNCTION(BlueprintCallable, Category=ActorDrag)
	void EnableActorDragMode();

	/** DisableActorDragMode*/
	UFUNCTION(BlueprintCallable, Category=ActorDrag)
	void DisableActorDragMode();
	
	
	/** ActorDragMode*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(AllowPrivateAccess=true), Category=ActorDrag)
	EActorDragMode ActorDragMode = EActorDragMode::Off;

	/** ActorDragTransform
	 *Transform of the dragged actor in the coordinate space of the pawn*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(AllowPrivateAccess=true), Category=ActorDrag)
	FTransform ActorDragTransform;
	// ~ ActorDrag End
};

// ~ RightHere_ACollPawn Begin





// Adhoc impl lines (WARNING! move to .cpp file, otherwise will fail to compile!)
// ~ RightHere_ACollPawn End
