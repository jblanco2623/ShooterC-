// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PortalComponent.h"
#include "Camera/CameraComponent.h"
#include "PlayerChar.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUseItem, bool, leftClick);

UCLASS()
class INCLASSSHOOTER_API APlayerChar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerChar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerVals)
		UCameraComponent* cam;
	UPROPERTY(EditAnywhere, Category = PlayerVals)
		float moveSpeed = 5;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerVals)
		UStaticMeshComponent* hingeMesh;

	UPROPERTY(BlueprintAssignable, Category = PlayerVals)
		FOnUseItem evOnUseItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerVals)
		TSubclassOf<class APortalComponent> portalBP;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerVals)
		APortalComponent* lPortal;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerVals)
		APortalComponent* rPortal;

	bool onCooldown;

protected:
	void MoveForward(float vel);

	void MoveRight(float vel);

	void OnUseItem(float leftClick);

public:
	UStaticMeshComponent* GetWeaponPoint() const { return hingeMesh ; };
	UCameraComponent* GetCam() const { return cam; }; 
};
