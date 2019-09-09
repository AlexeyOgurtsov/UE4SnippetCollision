#pragma once

/**
* To be copied to the destination and changed.
*/

#include "Util/TestUtil/TUActor.h"
#include "CollActor.generated.h"

class USphereComponent;

UCLASS()
class ACollActor : public ATUActor
{
	GENERATED_BODY()

public:
	ACollActor();

	virtual void BeginPlay() override;

	/** GetSphereComponent*/
	UFUNCTION(BlueprintPure, Category=Sphere)
	USphereComponent* GetSphereComponent() const
	{
		return SphereComponent;
	}
	
private:
	// ~ Sphere Begin
	// ~ Sphere End
	/** SphereComponent*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(AllowPrivateAccess=true), Category=Sphere)
	USphereComponent* SphereComponent = nullptr;
	/** InitSphere*/
	UFUNCTION(BlueprintCallable, Category=Sphere)
	USphereComponent* InitSphere(UActorComponent* InParent);
	
	
};

// ~ RightHere_ACollActor Begin


// Adhoc impl lines (WARNING! move to .cpp file, otherwise will fail to compile!)
// ~ RightHere_ACollActor End
