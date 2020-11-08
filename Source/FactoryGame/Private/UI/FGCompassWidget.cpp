// This file has been automatically generated by the Unreal Header Implementation tool

#include "FGCompassWidget.h"

UFGCompassWidget::UFGCompassWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) { }
void UFGCompassWidget::NativeConstruct(){ }
void UFGCompassWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime){ }
void UFGCompassWidget::Destruct(){ }
void UFGCompassWidget::BindActorRepresentationManager( AFGActorRepresentationManager* representationManager){ }
UFGCompassObjectWidget* UFGCompassWidget::AddCompassObjectForRepresentation(TSubclassOf<class UFGCompassObjectWidget> compassObjectTemplate,  UFGActorRepresentation* actorRepresentation){ return nullptr; }
void UFGCompassWidget::RemoveCompassObjectForRepresentation( UFGActorRepresentation* actorRepresentation){ }
void UFGCompassWidget::AddAllCompassRepresentations( AFGActorRepresentationManager* representationManager){ }
void UFGCompassWidget::RemoveAllCompassRepresentations(){ }
UFGCompassObjectWidget* UFGCompassWidget::CreateCompassObject(TSubclassOf<class UFGCompassObjectWidget> compassObjectTemplate,  UFGActorRepresentation* actorRepresentation){ return nullptr; }
UFGCompassObjectWidget* UFGCompassWidget::CreatePrimitiveCompassObject(TSubclassOf<class UFGCompassObjectWidget> compassObjectTemplate,  UTexture2D* texture){ return nullptr; }
void UFGCompassWidget::AddAllCardinalDirections(TSubclassOf<UFGCompassObjectWidget> compassObjectTemplate, UTexture2D* northTex, UTexture2D* eastTex, UTexture2D* southTex, UTexture2D* westTex,
			UTexture2D* northWestTex, UTexture2D* southEastTex, UTexture2D* southWestText, UTexture2D* northEastTex){ }
FVector2D UFGCompassWidget::GetCompassLineOffset_Implementation(){ return FVector2D(); }
void UFGCompassWidget::AddToCompassPanel( UFGCompassObjectWidget* compassObject){ }
void UFGCompassWidget::RemoveFromCompassPanel( UFGCompassObjectWidget* compassObject){ }
void UFGCompassWidget::OnActorRepresentationAdded( UFGActorRepresentation* actorRepresentation){ }
void UFGCompassWidget::OnActorRepresentationRemoved( UFGActorRepresentation* actorRepresentation){ }
void UFGCompassWidget::OnActorRepresentationUpdated( UFGActorRepresentation* actorRepresentation){ }
void UFGCompassWidget::OnActorRepresentationFiltered(ERepresentationType type, bool visible){ }
bool UFGCompassWidget::IsPawnLocalPlayerControlled(APawn* pawn){ return bool(); }
void UFGCompassWidget::CalculateCenteredResourceObjects(){ }
void UFGCompassWidget::CalculateCenteredObject(){ }
