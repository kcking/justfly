// This file has been automatically generated by the Unreal Header Implementation tool

#include "FGPipelinePumpHologram.h"

FPumpHeadLiftLocationPath::FPumpHeadLiftLocationPath(){ }
void FPumpHeadLiftLocationPath::SetData(const FPumpHeadLiftLocationPath& Other){ }
void FPumpHeadLiftLocationPath::SetData(const  USplineComponent* pSpline, float StartOffset, float EndOffset, bool ReverseDirection){ }
TArray<FTransform> FPumpHeadLiftLocationPath::GetTransformsAtDistance(float Distance) const{ return TArray<FTransform>(); }
float FPumpHeadLiftLocationPath::GetLongestPathLength() const{ return float(); }
void FPumpHeadLiftLocationPath::Clear(){ }
FPumpHeadLiftLocationPath& FPumpHeadLiftLocationPath::AddNextPath(const FPumpHeadLiftLocationPath& NextPath){ return *(this); }
FPumpHeadLiftLocationPath& FPumpHeadLiftLocationPath::AddNextPath(const  USplineComponent* pSpline, float StartOffset, float EndOffset, bool ReverseDirection){ return *(this); }
AFGPipelinePumpHologram::AFGPipelinePumpHologram(){ }
void AFGPipelinePumpHologram::Tick(float dt){ }
bool AFGPipelinePumpHologram::TrySnapToActor(const FHitResult& hitResult){ return bool(); }
float AFGPipelinePumpHologram::GetHeadLiftPathLength(const FPumpHeadLiftLocationPath& Path){ return float(); }
TArray<FTransform> AFGPipelinePumpHologram::GetTransformsAtDistanceAlongPath(const FPumpHeadLiftLocationPath& Path, float Distance){ return TArray<FTransform>(); }
TArray<FTransform> AFGPipelinePumpHologram::GetTransformsAtNormalizedDistanceAlongPath(const FPumpHeadLiftLocationPath& Path, float Distance){ return TArray<FTransform>(); }
void AFGPipelinePumpHologram::FindHeadLiftSnappingLocations( AFGBuildablePipeline* StartPipeline, TMap<AFGBuildablePipeline*, float>& OutResults, TArray<FPumpHeadLiftLocationPath>& OutPaths) const{ }
void AFGPipelinePumpHologram::FindLocationsWithHeightDifferenceOnPipeline(TMap<AFGBuildablePipeline*, float>& OutResults, FPumpHeadLiftLocationPath& OutPath,  AFGBuildablePipeline* pPipeline, const FVector& StartLocation,
		const float HeightDifference, bool ReverseDirection, const int32 RecursionLevel, float TotalDistanceTraversed) const{ }
