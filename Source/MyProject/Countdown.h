// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "GameFramework/Actor.h"
#include "Countdown.generated.h"

UCLASS()
class MYPROJECT_API ACountdown : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACountdown();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//倒计时运行市场，单位秒
	UPROPERTY(EditAnywhere)
	int32 _count_down_time;

	UTextRenderComponent* _count_down_text;
	FTimerHandle _count_down_timer_handle;

	//可由策划进行函数覆盖
	UFUNCTION(BlueprintNativeEvent)
	void CountdownHasFinished();

	void UpdateTimerDisplay();
	void AdvanceTimer();
};
