// Fill out your copyright notice in the Description page of Project Settings.


#include "SpinningChairSpeedChanger.h"

// Sets default values
ASpinningChairSpeedChanger::ASpinningChairSpeedChanger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Scene
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	RootComponent = SceneComponent;

	// Plane
	PlaneComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("PlaneComponent"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> PlaneComponentObject(TEXT("/Engine/BasicShapes/Plane.Plane"));

	if(PlaneComponentObject.Object)
	{
		PlaneComponent->SetStaticMesh(PlaneComponentObject.Object);
	}

	PlaneComponent->SetRelativeLocation(FVector(0, 0, 1));
	PlaneComponent->AttachToComponent(SceneComponent, FAttachmentTransformRules::KeepRelativeTransform);

	// Collider
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->SetupAttachment(RootComponent);
	Collider->SetGenerateOverlapEvents(true);
	Collider->SetBoxExtent(FVector(50.f, 50.f, 100.f), false);
	Collider->SetCollisionProfileName(TEXT("Trigger"), false);
	
	// Materials
	if(!MinusMaterial)
	{
		static ConstructorHelpers::FObjectFinder<UMaterial> GetMaterial(TEXT("/Game/Materials/M_Red.M_Red"));

		if(GetMaterial.Object)
		{
			MinusMaterial = GetMaterial.Object;
		}
	}

	if(!PlusMaterial)
	{
		static ConstructorHelpers::FObjectFinder<UMaterial> GetMaterial(TEXT("/Game/Materials/M_Green.M_Green"));

		if(GetMaterial.Object)
		{
			PlusMaterial = GetMaterial.Object;
		}
	}
}

// Overlap
void ASpinningChairSpeedChanger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACPPDelegatesCharacter* OverlappedCharacter = Cast<ACPPDelegatesCharacter>(OtherActor);
	
	if(OverlappedCharacter->IsValidLowLevel())
	{
		SpeedChange.Broadcast(Speed);
	}
}

// Called when the game starts or when spawned
void ASpinningChairSpeedChanger::BeginPlay()
{
	Super::BeginPlay();
	
	PlaneComponent->SetMaterial(0, Speed > 0 ? PlusMaterial : MinusMaterial);

	Collider->OnComponentBeginOverlap.AddDynamic(this, &ASpinningChairSpeedChanger::OnOverlapBegin);
}

// Called every frame
void ASpinningChairSpeedChanger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

