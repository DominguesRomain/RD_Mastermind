#include "MastermindBoard.h"
#include "MastermindRow.h"
#include "MasterMindGM.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

AMastermindBoard::AMastermindBoard()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AMastermindBoard::BeginPlay()
{
	Super::BeginPlay();

	if (!GameManager)
	{
		GameManager = Cast<AMasterMindGM>(UGameplayStatics::GetActorOfClass(GetWorld(), AMasterMindGM::StaticClass()));
	}

	if (!RowClass || !GameManager) return;

	for (int32 i = 0; i < MaxAttempts; i++)
	{
		FVector SpawnLocation = GetActorLocation() + RowSpacing * i;
		FRotator Rotation = GetActorRotation();
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;

		AMastermindRow* NewRow = GetWorld()->SpawnActor<AMastermindRow>(RowClass, SpawnLocation, Rotation, SpawnParams);
		if (NewRow)
		{
			NewRow->Manager = GameManager;
			GameManager->OnSolutionChecked.AddDynamic(NewRow, &AMastermindRow::ApplySolution);
			Rows.Add(NewRow);
		}
	}
}

void AMastermindBoard::OnRowSubmitted(uint8 GoodPlaces, uint8 WrongPlaces)
{
	CurrentAttempt++;
}