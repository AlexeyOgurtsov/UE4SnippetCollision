#pragma once

#include "ImplHelperLib.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "UObject/ConstructorHelpers.h"
#include "Engine/CollisionProfile.h"

#include "ImplHelperLib.generated.h"

class UStaticMeshComponent;
class UPrimitiveComponent;
class UMaterialInterface;

UCLASS()
class UImplHelperLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UImplHelperLib();

	static UStaticMeshComponent* CreateSM_WithProfile(ConstructorHelpers::FObjectFinderOptional<UStaticMesh>& MeshFinder, FName Profile, USceneComponent* InAttachTo, UObject* InOwner);
	static void SetDemoSMCollisionProfile(UStaticMeshComponent* Mesh, FName Profile);
	static void ColorByCollisionProfile(UPrimitiveComponent* Comp);

private:
	static void SetAllUsedMaterialsTo(UPrimitiveComponent* InComponent, UMaterialInterface* InMaterial);
	static UMaterialInterface* GetMaterialForCollisionProfile(FName InProfile);
	static void ColorAsDefault(UPrimitiveComponent* Comp);

	static UMaterialInterface* BlockAllNoCollisionMat;
	static UMaterialInterface* BlockAllMat;
	static UMaterialInterface* BlockAllDynamicMat;
	static UMaterialInterface* OverlapAllMat;
	static UMaterialInterface* OverlapAllDynamicMat;
	static UMaterialInterface* VehicleMat;
	static UMaterialInterface* PawnMat;
	static UMaterialInterface* PhysicsActorMat;
	static UMaterialInterface* DefaultProjectileMat;
	static UMaterialInterface* CustomMat;
	static UMaterialInterface* DefaultMat;
};

		  
