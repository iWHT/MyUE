// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloatingActor.generated.h"

UCLASS()
class MYPROJECT_API AFloatingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloatingActor();
	virtual void PostInitProperties() override;
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category="Damage")
	virtual void CalculateValues();

	UFUNCTION(BlueprintImplementableEvent, Category = "Damage")
	void CalledFromCpp();

	UPROPERTY(EditAnywhere)
	float _speed;

	float _running_time;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	int32 _total_damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float damage_time_in_seconds;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Transient, Category = "Damage")
	float damage_per_second;
};
