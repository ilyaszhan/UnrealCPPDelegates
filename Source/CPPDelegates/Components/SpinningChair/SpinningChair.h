// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../SpinningChairSpeedChanger/SpinningChairSpeedChanger.h"
#include "SpinningChair.generated.h"

UCLASS()
class CPPDELEGATES_API ASpinningChair : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpinningChair();
	
	UPROPERTY(EditAnywhere)
	float SpinSpeed;
	
	UPROPERTY(EditAnywhere)
	USceneComponent* SceneComponent;
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ChairMesh;

	UFUNCTION()
	void ChangeSpinSpeed(float AddSpeed);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
