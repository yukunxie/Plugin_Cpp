// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "PluginDemo.h"
#include "CoreGlobals.h"
#include "CoreUObject.h"

#define LOCTEXT_NAMESPACE "FPluginDemoModule"

struct Temp {
    Temp() {
//        FCoreUObjectDelegates::PreLoadMap.AddRaw(this, &Temp::PreLoadMap);
    }
    
    void PreLoadMap(const FString &MapName)
    {
        UE_LOG(LogTemp, Warning, TEXT("xxxxxx PreLoadMap: %s"), *MapName);
    }
};

static Temp temp;

void FPluginDemoModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
    UE_LOG(LogTemp, Warning, TEXT("xxxxxx"));
    FCoreUObjectDelegates::PreLoadMap.AddRaw(&temp, &Temp::PreLoadMap);
}

void FPluginDemoModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FPluginDemoModule, PluginDemo)
