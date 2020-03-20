#pragma once

/**
* Actor that has collision and mesh.
*/

#include "Util/TestUtil/TUActor.h"
#include "CollSkelMeshActor.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USceneComponent;
class USkeletalMeshComponent;
class USphereComponent;

UCLASS()
class ACollSkelMeshActor : public ATUActor
{
	GENERATED_BODY()

public:
	ACollSkelMeshActor();

	UFUNCTION(BlueprintPure, Category = Components)
	USceneComponent* GetRootSceneComponent() const { return RootSceneComponent; }

	UFUNCTION(BlueprintPure, Category = Camera)
	UCameraComponent* GetCamera() const { return Camera; }

	UFUNCTION(BlueprintPure, Category = Visual)
	USkeletalMeshComponent* GetMesh() const { return Mesh; }

	UFUNCTION(BlueprintPure, Category = Collision)
	USphereComponent* GetProxSphere() const { return ProxSphere; }

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Components, Meta=(AllowPrivateAccess = true))
	USceneComponent* RootSceneComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Camera, Meta=(AllowPrivateAccess = true))
	UCameraComponent* Camera = nullptr;
	void InitCameraAndSpringArm(USceneComponent* InAttachTo);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Camera, Meta=(AllowPrivateAccess = true))
	USpringArmComponent* SpringArm = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Visual, Meta=(AllowPrivateAccess = true))
	USkeletalMeshComponent* Mesh = nullptr;
	void InitMesh(USceneComponent* InAttachTo);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Collision, Meta=(AllowPrivateAccess = true))
	USphereComponent* ProxSphere = nullptr;
	void InitProxSphere(USceneComponent* InAttachTo);
};
