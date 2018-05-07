// Fill out your copyright notice in the Description page of Project Settings.

#include "FloatingActor.h"


// Sets default values
AFloatingActor::AFloatingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_total_damage = 200;
	damage_time_in_seconds = 1.0f;
}

// Called when the game starts or when spawned
void AFloatingActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFloatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector new_location = GetActorLocation();
	float delta_height = (FMath::Sin(_running_time + DeltaTime) - FMath::Sin(_running_time));
	new_location.Z += delta_height * _speed;
	_running_time += DeltaTime;
	SetActorLocation(new_location);
}

void AFloatingActor::PostInitProperties()
{
	Super::PostInitProperties();
	CalculateValues();
}

#if WITH_EDITOR
void AFloatingActor::PostEditChangeProperty(FPropertyChangedEvent& evt)
{
	Super::PostEditChangeProperty(evt);
	CalculateValues();
}

#endif

void AFloatingActor::CalculateValues()
{
	damage_per_second = _total_damage / damage_time_in_seconds;
}



