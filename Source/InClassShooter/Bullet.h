// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Bullet.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class INCLASSSHOOTER_API ABullet : public AActor
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	UPROPERTY(VisibleDefaultsOnly, Category=Bullet)
		USphereComponent* collComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Bullet)
		UProjectileMovementComponent* projMove;

public:
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& Hit);

	USphereComponent* GetCollComp() const { return collComp; }
	UProjectileMovementComponent* GetProjMove() const { return projMove; }
	

};
