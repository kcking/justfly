// This file has been automatically generated by the Unreal Header Implementation tool

#include "FGBuildableSplitterSmart.h"
#include "FGAttachmentSplitterHologram.h"

AFGBuildableSplitterSmart::AFGBuildableSplitterSmart() : Super() {
	this->mMaxNumSortRules = 64;
	this->mCurrentOutputIndex = -1;
	this->mPowerConsumptionExponent = 1.60000002384186;
	this->mMinimumProducingTime = -1;
	this->mMinimumStoppedTime = -1;
	this->mNumCyclesForProductivity = 20;
	this->mCurrentPotential = 1;
	this->mPendingPotential = 1;
	this->mMinPotential = 0.00999999977648258;
	this->mMaxPotential = 1;
	this->mMaxPotentialIncreasePerCrystal = 0.5;
	this->mFluidStackSizeDefault = EStackSize::SS_FLUID;
	this->mSignificanceRange = 18000;
	this->mHologramClass = AFGAttachmentSplitterHologram::StaticClass();
	this->MaxRenderDistance = -1;
	this->mFactoryTickFunction.TickGroup = TG_PrePhysics; this->mFactoryTickFunction.EndTickGroup = TG_PrePhysics; this->mFactoryTickFunction.bTickEvenWhenPaused = false; this->mFactoryTickFunction.bCanEverTick = true; this->mFactoryTickFunction.bStartWithTickEnabled = true; this->mFactoryTickFunction.bAllowTickOnDedicatedServer = true; this->mFactoryTickFunction.TickInterval = 0;
	this->mPrimaryColor.R = -1; this->mPrimaryColor.G = -1; this->mPrimaryColor.B = -1; this->mPrimaryColor.A = 1;
	this->mSecondaryColor.R = -1; this->mSecondaryColor.G = -1; this->mSecondaryColor.B = -1; this->mSecondaryColor.A = 1;
	this->mDismantleEffectClassName = FSoftClassPath("/Game/FactoryGame/Buildable/Factory/-Shared/BP_MaterialEffect_Dismantle.BP_MaterialEffect_Dismantle_C");
	this->mBuildEffectClassName = FSoftClassPath("/Game/FactoryGame/Buildable/Factory/-Shared/BP_MaterialEffect_Build.BP_MaterialEffect_Build_C");
	this->mHighlightParticleClassName = FSoftClassPath("/Game/FactoryGame/Buildable/-Shared/Particle/NewBuildingPing.NewBuildingPing_C");
	this->bReplicates = true;
	this->NetCullDistanceSquared = 5624999936;
}
void AFGBuildableSplitterSmart::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const{ }
void AFGBuildableSplitterSmart::PostLoadGame_Implementation(int32 saveVersion, int32 gameVersion){ }
FSplitterSortRule AFGBuildableSplitterSmart::GetSortRuleAt(int32 index) const{ return FSplitterSortRule(); }
void AFGBuildableSplitterSmart::AddSortRule(FSplitterSortRule rule){ }
void AFGBuildableSplitterSmart::RemoveSortRuleAt(int32 index){ }
void AFGBuildableSplitterSmart::SetSortRuleAt(int32 index, FSplitterSortRule rule){ }
bool AFGBuildableSplitterSmart::Factory_GrabOutput_Implementation( UFGFactoryConnectionComponent* connection, FInventoryItem& out_item, float& out_OffsetBeyond, TSubclassOf< UFGItemDescriptor > type){ return bool(); }
void AFGBuildableSplitterSmart::FillDistributionTable(float deltaTime){ }
void AFGBuildableSplitterSmart::OnRep_SortRules(){ }
TArray<UFGFactoryConnectionComponent*> AFGBuildableSplitterSmart::GetAllOutputConnectionsForItem(const FInventoryItem& item, float deltaTime) const{ return TArray<UFGFactoryConnectionComponent*>(); }
