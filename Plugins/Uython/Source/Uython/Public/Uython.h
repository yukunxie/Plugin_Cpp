// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "UythonDefines.h"
#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

NS_UYTHON_BEGIN

class FUythonModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

NS_UYTHON_END

