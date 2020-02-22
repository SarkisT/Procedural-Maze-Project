// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicFloor.h"
#include "Engine.h"
#include "Kismet/GameplayStatics.h"
#include "TileIndexWidget.h"


// Sets default values
ABasicFloor::ABasicFloor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FloorTile = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor"));
	FloorTile->SetupAttachment(RootComponent);

	//WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	//WComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	//WComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	//ABasicFloor MyActor = GetActor

	//AActor* MyActor = Cast<AActor>(ABasicFloor);

	//auto MyActor = this;
	//TArray<UStaticMeshComponent> StaticComps;
	//MyActor->GetComponents<UStaticMeshComponent>(StaticComps);
	
	
	//FTransform Root = FloorTile->GetComponentTransform();
	
	//NWall = AddComponent(FName("WALL"), false, Root, UStaticMeshComponent);//CreateSubobject<UStaticMeshComponent>(TEXT("Wall"));
	//AddComponent("Wall", true, Root, UStaticMeshComponent);
	

	//EWall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall"));
	//EWall->SetupAttachment(FloorTile);

	//WWall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall"));
	//WWall->SetupAttachment(FloorTile);

	//SWall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall"));
	//SWall->SetupAttachment(FloorTile);

	//FloorTile = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Mesh"));
	//RootComponent = FloorTile;

	//FloorTile->SetWorldScale3D(FVector(1.0, 1.0, 0.2f));
	

}

// Called when the game starts or when spawned
void ABasicFloor::BeginPlay()
{
//NORTH = 1
//SOUTH = 2
//EAST = 3
//WEST = 4
	Super::BeginPlay();
	this->GetComponents(StaticComps);
	//AActor* owner = GetOwner();
	//if (owner) {
//
	//}
	//Cast<UTileIndexWidget>(WComponent->GetUserWidgetObject())->BasicFloor = this;
	FloorTile->SetWorldScale3D(FVector(7.0, 7.0, 0.25));
	//GEngine->AddOnScreenDebugMessage(-1, 30, FColor::Blue, FString::Printf(TEXT(" %i "), HP));//Seems good.
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Emerald, FloorTile->GetComponentScale().ToString());
}

// Called every frame
void ABasicFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	
	//auto camera = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	//WComponent->SetWorldRotation(camera->GetCameraRotation());
	//WComponent->AddLocalRotation(FRotator(0, 180, 0));

}

void ABasicFloor::DestroyWalls(int n)
{
	switch (n) {
	case 1:
		if (N == true) {
			StaticComps[1]->DestroyComponent();
			N = false;
		}
		break;
	case 2:
		if (S == true) {
			StaticComps[2]->DestroyComponent();
			S = false;

		}
		break;
	case 3:
		if (E == true) {
			StaticComps[3]->DestroyComponent();		
			E = false;

		}
		break;
	case 4:
		if (W == true) {
			StaticComps[4]->DestroyComponent();			
			W = false;
		}
		break;
	}

}

