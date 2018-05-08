// Fill out your copyright notice in the Description page of Project Settings.

#include "Countdown.h"


// Sets default values
ACountdown::ACountdown()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	_count_down_text = CreateDefaultSubobject<UTextRenderComponent>(TEXT("CountdownNumber"));
	_count_down_text->SetHorizontalAlignment(EHTA_Center);
	_count_down_text->SetWorldSize(150.0f);
	RootComponent = _count_down_text;

	_count_down_time = 3;
}

// Called when the game starts or when spawned
void ACountdown::BeginPlay()
{
	Super::BeginPlay();
	UpdateTimerDisplay();
	GetWorldTimerManager().SetTimer(_count_down_timer_handle, this, &ACountdown::AdvanceTimer, 1.0f, true);
}

// Called every frame
void ACountdown::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACountdown::UpdateTimerDisplay()
{
	_count_down_text->SetText(FString::FromInt(FMath::Max(_count_down_time, 0)));
}

void ACountdown::AdvanceTimer()
{
	--_count_down_time;
	UpdateTimerDisplay();
	if (_count_down_time < 1)
	{
		GetWorldTimerManager().ClearTimer(_count_down_timer_handle);
		CountdownHasFinished();

	}
}

void ACountdown::CountdownHasFinished_Implementation()
{
	_count_down_text->SetText(TEXT("GO!"));
}

