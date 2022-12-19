// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerChar.h"
#include "Components/ActorComponent.h"
#include "WeaponComp.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INCLASSSHOOTER_API UWeaponComp : public UActorComponent{
	
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponComp();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:
	APlayerChar* selfActor;
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
		FVector shootPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Proyectile)
		bool bUseRaycast;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Proyectile)
		float shootSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Proyectile)
		TSubclassOf<class APortalComponent> portalBP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		APlayerChar* player;

public:
	UFUNCTION(BlueprintCallable, Category=Gameplay)
		void AttachToPlayer(APlayerChar* target);

	UFUNCTION(BlueprintCallable, Category=Gameplay)
		void Fire(bool leftClick);

	FVector TryAddPortal(FHitResult* Hit);
	float ConstraintToWallY(float PortalY, FHitResult* Hit);
	float ConstraintToWallZ(float PortalZ, FHitResult* Hit);
	float ClampPointToWall(float Point, float WallSize, float PortalRadius);
};
