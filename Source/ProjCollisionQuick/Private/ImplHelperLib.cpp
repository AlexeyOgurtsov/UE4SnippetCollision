#include "ImplHelperLib.h"
#include "Components/StaticMeshComponent.h"
#include "Util/Core/LogUtilLib.h"
#include "Engine/StaticMesh.h"
#include "GameFramework/Actor.h"

UMaterialInterface* UImplHelperLib::BlockAllNoCollisionMat = nullptr;
UMaterialInterface* UImplHelperLib::BlockAllMat = nullptr;
UMaterialInterface* UImplHelperLib::BlockAllDynamicMat = nullptr;
UMaterialInterface* UImplHelperLib::OverlapAllMat = nullptr;
UMaterialInterface* UImplHelperLib::OverlapAllDynamicMat = nullptr;
UMaterialInterface* UImplHelperLib::VehicleMat = nullptr;
UMaterialInterface* UImplHelperLib::PawnMat = nullptr;
UMaterialInterface* UImplHelperLib::PhysicsActorMat = nullptr;
UMaterialInterface* UImplHelperLib::DefaultProjectileMat = nullptr;
UMaterialInterface* UImplHelperLib::CustomMat = nullptr;
UMaterialInterface* UImplHelperLib::DefaultMat = nullptr;

UImplHelperLib::UImplHelperLib()
{
	{
		ConstructorHelpers::FObjectFinder<UMaterialInterface> BlockAllNoCollisionMatFinder(TEXT("Material'/Game/Helper/Mat/BlockAll_NoCollision_Mat.BlockAll_NoCollision_Mat'"));
		BlockAllNoCollisionMatFinder.Object->AddToRoot();
		BlockAllNoCollisionMat = BlockAllNoCollisionMatFinder.Object;
	}

	{
		ConstructorHelpers::FObjectFinder<UMaterialInterface> BlockAllMatFinder(TEXT("Material'/Game/Helper/Mat/Collision_BlockAll_Mat.Collision_BlockAll_Mat'"));
		BlockAllMatFinder.Object->AddToRoot();
		BlockAllMat = BlockAllMatFinder.Object;
	}

	{
		ConstructorHelpers::FObjectFinder<UMaterialInterface> BlockAllDynamicMatFinder(TEXT("Material'/Game/Helper/Mat/Collision_BlockAllDynamic_Mat.Collision_BlockAllDynamic_Mat'"));
		BlockAllDynamicMatFinder.Object->AddToRoot();
		BlockAllDynamicMat = BlockAllDynamicMatFinder.Object;
	}

	{
		ConstructorHelpers::FObjectFinder<UMaterialInterface> OverlapAllMatFinder(TEXT("Material'/Game/Helper/Mat/Collision_OverlapAll_Mat.Collision_OverlapAll_Mat'"));
		OverlapAllMatFinder.Object->AddToRoot();
		OverlapAllMat = OverlapAllMatFinder.Object;
	}

	{
		ConstructorHelpers::FObjectFinder<UMaterialInterface> OverlapAllDynamicMatFinder(TEXT("Material'/Game/Helper/Mat/Collision_OverlapAllDynamic_Mat.Collision_OverlapAllDynamic_Mat'"));
		OverlapAllDynamicMatFinder.Object->AddToRoot();
		OverlapAllDynamicMat = OverlapAllDynamicMatFinder.Object;
	}

	{
		ConstructorHelpers::FObjectFinder<UMaterialInterface> VehicleMatFinder(TEXT("Material'/Game/Helper/Mat/Collision_Vehicle_Mat.Collision_Vehicle_Mat'"));
		VehicleMatFinder.Object->AddToRoot();
		VehicleMat = VehicleMatFinder.Object;
	}

	{
		ConstructorHelpers::FObjectFinder<UMaterialInterface> PawnMatFinder(TEXT("Material'/Game/Helper/Mat/Collision_Pawn_Mat.Collision_Pawn_Mat'"));
		PawnMatFinder.Object->AddToRoot();
		PawnMat = PawnMatFinder.Object;
	}

	{
		ConstructorHelpers::FObjectFinder<UMaterialInterface> PhysicsActorMatFinder(TEXT("Material'/Game/Helper/Mat/Collision_PhysicsActor_Mat.Collision_PhysicsActor_Mat'"));
		PhysicsActorMatFinder.Object->AddToRoot();
		PhysicsActorMat = PhysicsActorMatFinder.Object;
	}

	{
		ConstructorHelpers::FObjectFinder<UMaterialInterface> DefaultProjectileMatFinder(TEXT("Material'/Game/Helper/Mat/Collision_DefaultProjectile_Mat.Collision_DefaultProjectile_Mat'"));
		DefaultProjectileMatFinder.Object->AddToRoot();
		DefaultProjectileMat = DefaultProjectileMatFinder.Object;
	}

	{
		ConstructorHelpers::FObjectFinder<UMaterialInterface> CustomMatFinder(TEXT("Material'/Game/Helper/Mat/Collision_Custom_Mat.Collision_Custom_Mat'"));
		CustomMatFinder.Object->AddToRoot();
		CustomMat = CustomMatFinder.Object;
	}

	{
		ConstructorHelpers::FObjectFinder<UMaterialInterface> DefaultMatFinder(TEXT("Material'/Game/Helper/Mat/Collision_DefaultMesh_Mat.Collision_DefaultMesh_Mat'"));
		DefaultMatFinder.Object->AddToRoot();
		DefaultMat = DefaultMatFinder.Object;
	}
}

UMaterialInterface* UImplHelperLib::GetMaterialForCollisionProfile(const FName InProfile)
{
	if(InProfile == UCollisionProfile::NoCollision_ProfileName)
	{
		return BlockAllNoCollisionMat;
	}

	else if(InProfile == UCollisionProfile::BlockAll_ProfileName)
	{
		return BlockAllMat;
	}
	
	else if(InProfile == UCollisionProfile::BlockAllDynamic_ProfileName)
	{
		return BlockAllDynamicMat;
	}

	else if(InProfile == UCollisionProfile::CustomCollisionProfileName)
	{
		return CustomMat;
	}

	else if(InProfile == UCollisionProfile::DefaultProjectile_ProfileName)
	{
		return DefaultProjectileMat;
	}

	else if(InProfile == UCollisionProfile::Pawn_ProfileName)
	{
		return PawnMat;
	}

	else if(InProfile == UCollisionProfile::Vehicle_ProfileName)
	{
		return VehicleMat;
	}

	else if(InProfile == UCollisionProfile::PhysicsActor_ProfileName)
	{
		return PhysicsActorMat;
	}

	else if(InProfile == FName(TEXT("OverlapAll")))
	{
		return OverlapAllMat;
	}
	
	else if(InProfile == FName(TEXT("OverlapAllDynamic")))
	{
		return OverlapAllDynamicMat;
	}

	checkf(false, TEXT("Unknown profile"));
	return nullptr;
}

void UImplHelperLib::SetAllUsedMaterialsTo(UPrimitiveComponent* const InComponent, UMaterialInterface* const InMaterial)
{
	for(int32 MaterialIndex = 0; MaterialIndex < InComponent->GetNumMaterials(); ++MaterialIndex)
	{
		InComponent->SetMaterial(MaterialIndex, InMaterial);
	}
}

UStaticMeshComponent* UImplHelperLib::CreateSM_WithProfile(ConstructorHelpers::FObjectFinderOptional<UStaticMesh>& MeshFinder, const FName Profile, USceneComponent* const InAttachTo, UObject* const InOwner)
{
	UStaticMeshComponent* Mesh = nullptr;
	{
		Mesh = InOwner->CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

		if(MeshFinder.Succeeded())
		{
			M_LOG(TEXT("Default mesh (\"%s\") found, setting it up"), *MeshFinder.GetReferencerName());
			Mesh->SetStaticMesh(MeshFinder.Get());
		}

		if(InAttachTo)
		{
			Mesh->SetupAttachment(InAttachTo);
		}
	}

	SetDemoSMCollisionProfile(Mesh, Profile);
	return Mesh;
}

void UImplHelperLib::SetDemoSMCollisionProfile(UStaticMeshComponent* const Mesh, const FName Profile)
{
	Mesh->SetCollisionProfileName(Profile);
	SetAllUsedMaterialsTo(Mesh, GetMaterialForCollisionProfile(Profile));
}

void UImplHelperLib::ColorAsDefault(UPrimitiveComponent* const Comp)
{
	SetAllUsedMaterialsTo(Comp, DefaultMat);

}
void UImplHelperLib::ColorByCollisionProfile(UPrimitiveComponent* const Comp)
{
	M_LOGFUNC();
	if(Comp)
	{
		M_LOG(TEXT("Component: \"%s\" of class \"%s\""), *Comp->GetName(), *Comp->GetClass()->GetName());
		const FName CollisionProfileName = Comp->GetCollisionProfileName();
		M_LOG(TEXT("Profile name: %s"), *CollisionProfileName.ToString());
		SetAllUsedMaterialsTo(Comp, GetMaterialForCollisionProfile(CollisionProfileName));
	}
}
