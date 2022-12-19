// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PortalComponent.generated.h"

UCLASS()
class INCLASSSHOOTER_API APortalComponent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortalComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Editor)
		UStaticMeshComponent* InternalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Editor)
		UStaticMeshComponent* BorderMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Editor)
		UMaterialInterface* MaterialLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Editor)
		UMaterialInterface* MaterialRight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		bool isLeftPortal = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void Prepare();
};
