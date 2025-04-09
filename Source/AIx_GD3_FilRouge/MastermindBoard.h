#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MastermindBoard.generated.h"

class AMasterMindGM;
class AMastermindRow;

UCLASS()
class AIX_GD3_FILROUGE_API AMastermindBoard : public AActor
{
	GENERATED_BODY()

public:
	AMastermindBoard();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mastermind")
	TSubclassOf<AMastermindRow> RowClass;

	UPROPERTY(EditAnywhere, Category = "Mastermind")
	int32 MaxAttempts = 8;

	UPROPERTY(EditAnywhere, Category = "Mastermind")
	FVector RowSpacing = FVector(0, 200, 0);

	UPROPERTY(EditAnywhere, Category = "Mastermind")
	AMasterMindGM* GameManager;

	UPROPERTY()
	TArray<AMastermindRow*> Rows;

	UPROPERTY()
	int32 CurrentAttempt = 0;

	UFUNCTION()
	void OnRowSubmitted(uint8 GoodPlaces, uint8 WrongPlaces);
};