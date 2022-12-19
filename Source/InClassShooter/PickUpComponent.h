// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerChar.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"
#include "PickUpComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPickUp, APlayerChar*, pickUpTarget);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INCLASSSHOOTER_API UPickUpComponent : public USphereComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPickUpComponent();

	UPROPERTY(BlueprintAssignable, Category = Interaction)
		FOnPickUp evOnPickUp;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
		
};
