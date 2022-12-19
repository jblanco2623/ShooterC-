
#include "PortalComponent.h"
#include "Components/StaticMeshComponent.h"

APortalComponent::APortalComponent()
{
	PrimaryActorTick.bCanEverTick = true;
	InternalMesh = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("PortalMesh"));
	BorderMesh = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("PortalBorderMesh"));
	BorderMesh->SetupAttachment(InternalMesh);
	BorderMesh->SetWorldRotation(FRotator(0, 0, 0));

	MaterialLeft = CreateDefaultSubobject<UMaterialInterface>("MaterialLeft");
	MaterialRight = CreateDefaultSubobject<UMaterialInterface>("MaterialRight");

}

void APortalComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APortalComponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APortalComponent::Prepare()
{
	BorderMesh->SetMaterial(0, isLeftPortal ? MaterialLeft : MaterialRight);
}

