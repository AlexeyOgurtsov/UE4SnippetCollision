#pragma once

#include "GameFramework/Pawn.h"
#include "TestPawn_MeshIsRoot_BlockAll.generated.h"

class UPrimitiveComponent;
class UStaticMeshComponent;
class USphereComponent;

UCLASS(BlueprintType)
class ATestPawn_MeshIsRoot_BlockAll : public APawn
{
	GENERATED_BODY()

public:
	ATestPawn_MeshIsRoot_BlockAll();	

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	UStaticMeshComponent* Mesh = nullptr;

	UPROPERTY()
	USphereComponent* ProxSphere = nullptr;

	void InitMesh(USceneComponent* InAttachTo);
	void InitProxSphere(USceneComponent* InAttachTo);
};

