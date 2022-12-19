// Fill out your copyright notice in the Description page of Project Settings.


#include "PortalWall.h"
#include "Kismet/KismetMathLibrary.h"
#include "GenericPlatform/GenericPlatformMath.h"

// Sets default values
APortalWall::APortalWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Mesh = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("Mesh"));

	Mesh->SetupAttachment(Box);
	Box->SetWorldScale3D(FVector(1, wallWidth / 100, wallHeight / 100));

}

// Called when the game starts or when spawned
void APortalWall::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void APortalWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
