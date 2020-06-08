// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/Interface.h"
#include "UythonModuleInterface.generated.h"

/**
 *
 */
UINTERFACE()
class UYTHON_API UUythonModuleInterface : public UInterface
{
    GENERATED_BODY()
};

class UYTHON_API IUythonModuleInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent)
    FString GetUythonModuleFullName() const;
};