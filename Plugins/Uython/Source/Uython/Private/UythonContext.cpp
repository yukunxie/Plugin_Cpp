// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "UythonContext.h"

#include "CoreGlobals.h"
#include "CoreUObject.h"

#include "Python/Python.h"

#if WITH_EDITOR
#include "Editor.h"
#endif

NS_UYTHON_BEGIN

static PyObject * print_info(PyObject *self, PyObject *args){
    const char* content = nullptr;
    if (!PyArg_ParseTuple(args, "s", &content))
        return NULL;
    if (content && (strlen(content) != 0))
    {
        UE_LOG(LogTemp, Log, TEXT("Uython-log: %s"), *FString(content));
    }
    return Py_None;
}

static PyObject * print_error(PyObject *self, PyObject *args){
    const char* content = nullptr;
    if (!PyArg_ParseTuple(args, "s", &content))
        return NULL;
    if (content && (strlen(content) != 0))
    {
        UE_LOG(LogTemp, Error, TEXT("Uython-error: %s"), *FString(content));
    }
    return Py_None;
}

static PyMethodDef sGlobalMethods[] = {
    {"print_info", print_info, METH_VARARGS},
    {"print_error", print_error, METH_VARARGS},
    {NULL, NULL}
};

static struct PyModuleDef sGlobalModule = {
    PyModuleDef_HEAD_INIT,
    "Uython", /*module name*/
    "Uython Global Mehtods.\n", /* module documentation, may be NULL */
    -1, /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
    sGlobalMethods
};

PyMODINIT_FUNC PyInit_UythonModule(void){ return PyModule_Create(&sGlobalModule);}

UythonContext* UythonContext::sUythonContextInstance = nullptr;

UythonContext::UythonContext()
{
#if WITH_EDITOR
    // delegates for PIE
    FEditorDelegates::PreBeginPIE.AddRaw(this, &UythonContext::PreBeginPIE);
    FEditorDelegates::BeginPIE.AddRaw(this, &UythonContext::BeginPIE);
    FEditorDelegates::PostPIEStarted.AddRaw(this, &UythonContext::PostPIEStarted);
    FEditorDelegates::PrePIEEnded.AddRaw(this, &UythonContext::PrePIEEnded);
    FEditorDelegates::EndPIE.AddRaw(this, &UythonContext::EndPIE);
    //    FGameDelegates::Get().GetEndPlayMapDelegate().AddRaw(GLuaCxt, &UythonContext::OnEndPlayMap);
#endif
    
}

void UythonContext::Initialize()
{
    if (Initialized_)
    {
        return;
    }

    GUObjectArray.AddUObjectCreateListener(this);    // add listener for creating UObject
    GUObjectArray.AddUObjectDeleteListener(this);

    
    Py_UnbufferedStdioFlag = 1;
    
    // 全局模块需要在Py_Initialize之前调用
    RegisterGlobalPythonMethod();
    
    Py_Initialize();
    
    // 输出重定向
    {
        const char* redirectCode = "import sys\n"
        "import Uython\n"
        "\n"
        "class Logger(object):\n"
        "    def __init__(self, outputFunc):\n"
        "       self._lines = []\n"
        "       self._outputFunc = outputFunc\n"
        "\n"
        "    def write(self, message):\n"
        "        self._lines.append(message)\n"
        "\n"
        "    def flush(self):\n"
        "        self._outputFunc(''.join(self._lines))\n"
        "        self._lines = []\n"
        "\n"
        "sys.stderr = Logger(Uython.print_error)\n"
        "sys.stdout = Logger(Uython.print_info)\n"
        "\n"
        "workbenchPath='%s'\n"
        "print('Uython Script Path:', workbenchPath, flush=True)\n"
        "sys.path.append(workbenchPath+'lib')\n"
        "sys.path.append(workbenchPath+'sdk')\n"
        "sys.path.append(workbenchPath+'src')\n";
        
        FString scriptRelativePath = TEXT("Uython/");
        FString scriptFullPath = FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir() + scriptRelativePath);

        char buffer[2048];
        snprintf(buffer, sizeof(buffer) - 1, redirectCode, TCHAR_TO_UTF8(*scriptFullPath));
                 
        PyRun_SimpleString(buffer);
        PyRun_SimpleString("print('********* test python stdout redirect to UE4', flush=True)");
    }
    
    // 加载main.py
    {
        auto mainModuleName = PyUnicode_FromString("main");
        PyObject* mainModule = PyImport_Import(mainModuleName);
        if (!mainModule)
        {
            UE_LOG(LogTemp, Error, TEXT("Uython: Load main.py module fail."));
            Py_Finalize();
            return;
        }
    }
    
    Initialized_ = true;
}

void UythonContext::RegisterGlobalPythonMethod()
{
    if (PyImport_AppendInittab("Uython", PyInit_UythonModule) == -1) {
        UE_LOG(LogTemp, Error, TEXT("UythonContext::RegisterGlobalPythonMethod Fail."));
        exit(1);
    }
}

UythonContext* UythonContext::Create()
{
    if (!sUythonContextInstance)
    {
        sUythonContextInstance = new UythonContext();
    }
    return sUythonContextInstance;
}

#if WITH_EDITOR
void UythonContext::PreBeginPIE(bool bIsSimulating)
{
    UE_LOG(LogTemp, Warning, TEXT("Uython: PreBeginPIE"));
    Initialize();
}

void UythonContext::BeginPIE(bool bIsSimulating)
{
    
}

void UythonContext::PostPIEStarted(bool bIsSimulating)
{
}

void UythonContext::PrePIEEnded(bool bIsSimulating)
{
    
}

void UythonContext::EndPIE(bool bIsSimulating)
{
    if(!Initialized_)
    {
        return ;
    }
    Initialized_ = false;
    Py_Finalize();
}

#endif

void UythonContext::NotifyUObjectCreated(const class UObjectBase *Object, int32 Index)
{
    UE_LOG(LogTemp, Warning, TEXT("Uython: UythonContext::NotifyUObjectCreated"));
}

void UythonContext::NotifyUObjectDeleted(const class UObjectBase *Object, int32 Index)
{
    UE_LOG(LogTemp, Warning, TEXT("Uython: UythonContext::NotifyUObjectDeleted"));
}

void UythonContext::OnUObjectArrayShutdown()
{
    UE_LOG(LogTemp, Warning, TEXT("Uython: UythonContext::OnUObjectArrayShutdown"));
}

NS_UYTHON_END
