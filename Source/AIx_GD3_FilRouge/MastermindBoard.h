#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MasterMindGM.h"
#include "MastermindBoard.generated.h"

class AMastermindRow;

UCLASS()
class AIX_GD3_FILROUGE_API AMastermindBoard : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMastermindBoard();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AMastermindRow> RowClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RowCount = 8;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RowSpacing = 120.f;

	UPROPERTY(BlueprintReadOnly)
	TArray<AMastermindRow*> Rows;

	UPROPERTY()
	int32 CurrentRowIndex = 0;

	UPROPERTY()
	AMasterMindGM* Manager;

	UFUNCTION()
	void OnRowSubmitted(uint8 GoodPlaces, uint8 WrongPlaces);

	UFUNCTION()
	void HandleSolutionChecked(int32 Correct, int32 Misplaced);
};