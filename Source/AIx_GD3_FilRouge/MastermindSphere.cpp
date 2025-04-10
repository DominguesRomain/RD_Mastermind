#include "MastermindSphere.h"
#include "Components/StaticMeshComponent.h"

UMastermindSphere::UMastermindSphere()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UMastermindSphere::BeginPlay()
{
	Super::BeginPlay();

	if (Mesh)
	{
		Mesh->OnClicked.AddDynamic(this, &UMastermindSphere::Clicked);
		UMaterialInterface* BaseMat = Mesh->GetMaterial(0);
		DynamicMat = UMaterialInstanceDynamic::Create(BaseMat, this);
		Mesh->SetMaterial(0, DynamicMat);
	}
	ChangeColor(BlockedColor);
}

void UMastermindSphere::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UMastermindSphere::Clicked(UPrimitiveComponent* ClickedComp, FKey ButtonPressed)
{
	UE_LOG(LogTemp, Warning, TEXT("Composant cliqué !"));
	ActualColorNumber++;
	if (ActualColorNumber >= 6)
	{
		ActualColorNumber = 0;
	}
	if (Manager)
	{
		ChangeColor(Manager->GetColor(ActualColorNumber));
	}
}

void UMastermindSphere::Unblock() {}
void UMastermindSphere::Block() {}

void UMastermindSphere::ChangeColor(FLinearColor NewColor)
{
	if (DynamicMat)
	{
		DynamicMat->SetVectorParameterValue("Color", NewColor);
	}
}

int UMastermindSphere::GetSphereColor()
{
	return ActualColorNumber;
}