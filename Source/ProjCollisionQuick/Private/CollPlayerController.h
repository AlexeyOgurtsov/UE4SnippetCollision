#pragma once

/**
* To be copied to the destination and changed.
*/

#include "Util/TestUtil/TUPlayerController.h"
#include "Util/Core/Log/MyLoggingTypes.h"
#include "CollPlayerController.generated.h"

class ACollPawn;

UCLASS()
class ACollPlayerController : public ATUPlayerController
{
	GENERATED_BODY()

public:
	ACollPlayerController();

	// ~AActor Begin
	virtual void BeginPlay() override;
	// ~AActor End

	// ~Access helpers Begin
	UFUNCTION(BlueprintPure, Category = Pawn)
	ACollPawn* GetMyPawn() const;

	UFUNCTION(BlueprintPure, Category = Pawn)
	ACollPawn* GetMyPawnLogged(ELogFlags InLogFlags = ELogFlags::None) const;

	/**
	* Checks that the given pawn NOT null.
	*/
	UFUNCTION(BlueprintPure, Category = Pawn)
	ACollPawn* GetMyPawnChecked() const;

	/** Pawn_SelectedActorChanged*/
	UFUNCTION(BlueprintCallable, Category=Misc)
	void Pawn_SelectedActorChanged();
	
	/** Pawn_DragActorModeChanged*/
	UFUNCTION(BlueprintCallable, Category=Misc)
	void Pawn_DragActorModeChanged();
	
protected:
	// ~Access helpers End
	virtual void Action_DebugOne() override;

	virtual void Action_DebugTwo() override;

	virtual void Action_DebugThree() override;

	virtual void Action_Use() override;

	virtual void Action_UseTwo() override;

	virtual void Action_UseThree() override;

	virtual void Action_Fire() override;

	virtual void Action_FireTwo() override;

	virtual void Action_FireThree() override;

	virtual void Action_SelectZero() override;

	virtual void Action_SelectOne() override;

	virtual void Action_SelectTwo() override;

	virtual void Action_SelectThree() override;

	virtual void Action_SelectFour() override;

	virtual void Action_SelectFive() override;

	virtual void Action_SelectSix() override;

	virtual void Action_SelectSeven() override;

	virtual void Action_SelectEight() override;

	virtual void Action_SelectNine() override;
private:
};

// ~ RightHere_ACollPlayerController Begin

// Adhoc impl lines (WARNING! move to .cpp file, otherwise will fail to compile!)
// ~ RightHere_ACollPlayerController End
