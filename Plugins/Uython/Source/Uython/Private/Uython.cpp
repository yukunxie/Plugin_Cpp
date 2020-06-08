// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "Uython.h"
#include "CoreGlobals.h"
#include "CoreUObject.h"

#include "UythonContext.h"

#include "Python/Python.h"

NS_UYTHON_BEGIN

#define LOCTEXT_NAMESPACE "FUythonModule"

void FUythonModule::StartupModule()
{
	UythonContext::Create();
}

void FUythonModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FUythonModule, Uython)

