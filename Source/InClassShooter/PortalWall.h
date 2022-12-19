// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "PortalWall.generated.h"

UCLASS()
class INCLASSSHOOTER_API APortalWall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortalWall();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Editor)
		UBoxComponent* Box;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Editor)
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Editor)
		float wallWidth = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Editor)
		float wallHeight = 100;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	const FVector getWallSize() const { return Box->GetRelativeScale3D(); }
};
