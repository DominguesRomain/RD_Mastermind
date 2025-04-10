#pragma once

#include "CoreMinimal.h"
#include "MasterMindGM.h"
#include "Components/ActorComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "MastermindSphere.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class AIX_GD3_FILROUGE_API UMastermindSphere : public UActorComponent
{
	GENERATED_BODY()

public:
	UMastermindSphere();

	UPROPERTY(EditAnywhere)
	AMasterMindGM* Manager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;

	UPROPERTY()
	UMaterialInstanceDynamic* DynamicMat;

	UPROPERTY(EditAnywhere)
	uint8 ActualColorNumber = 0;

	UPROPERTY(EditAnywhere)
	FLinearColor BlockedColor = FLinearColor::Black;

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Clicked(UPrimitiveComponent* ClickedComp, FKey ButtonPressed);

	UFUNCTION(BlueprintCallable)
	void Unblock();

	UFUNCTION(BlueprintCallable)
	void Block();

	UFUNCTION(BlueprintCallable)
	void ChangeColor(FLinearColor NewColor);

	UFUNCTION(BlueprintCallable)
	int GetSphereColor();
};