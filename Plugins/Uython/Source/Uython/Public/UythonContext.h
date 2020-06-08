// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "UythonDefines.h"

#include "Engine/World.h"
#include "GenericPlatform/GenericApplication.h"
#include "Runtime/Launch/Resources/Version.h"
#include "UObject/UObjectArray.h"

NS_UYTHON_BEGIN

class UythonContext : public FUObjectArray::FUObjectCreateListener,
public FUObjectArray::FUObjectDeleteListener
{
public:
    static UythonContext *Create();

    virtual void NotifyUObjectCreated(const class UObjectBase *Object,
                                      int32 Index) override;
    
    virtual void NotifyUObjectDeleted(const class UObjectBase *Object, int32 Index) override;
    
    virtual void OnUObjectArrayShutdown() override;
    
#if WITH_EDITOR
    void PreBeginPIE(bool bIsSimulating);
    void BeginPIE(bool bIsSimulating);
    void PostPIEStarted(bool bIsSimulating);
    void PrePIEEnded(bool bIsSimulating);
    void EndPIE(bool bIsSimulating);
#endif
    
protected:
    UythonContext();
    
    void Initialize();
    
    void RegisterGlobalPythonMethod();
    
private:
    static UythonContext *sUythonContextInstance;
    
    bool Initialized_ = false;
};

NS_UYTHON_END
