using System;
using System.IO;
using UnrealBuildTool;

public class Python3 : ModuleRules
{
    public Python3(ReadOnlyTargetRules Target) : base(Target)
    {
        Type = ModuleType.External;

        if (Target.Platform == UnrealTargetPlatform.Win64 || Target.Platform == UnrealTargetPlatform.Mac ||
            Target.Platform == UnrealTargetPlatform.IOS || Target.Platform == UnrealTargetPlatform.Android)
        {
            string PythonDynLibName = "";
            string PythonDynamicLibPath = "";

            if (Target.Platform == UnrealTargetPlatform.Win64)
            {
                PythonDynLibName = "python39.dll";
                PythonDynamicLibPath = Path.Combine(ModuleDirectory, "Binaries/Win64", PythonDynLibName);

                //PublicDefinitions.Add("MS_WINDOWS=1");
                //PublicDefinitions.Add("_WIN64=1");
                //PublicDefinitions.Add("MS_WIN64=1");
                //PublicDefinitions.Add("NT_THREADS=1");

                {
                    string Format = Path.Combine(ModuleDirectory, "{0}/Win64/python39.lib");
                    PublicAdditionalLibraries.Add(String.Format(Format, Target.bBuildEditor == true ? "Binaries" : "Lib"));
                }

            }
            else if (Target.Platform == UnrealTargetPlatform.Mac)
            {
                PythonDynLibName = Path.Combine(ModuleDirectory, "Binaries/Mac/libpython3.10d.a");
                PythonDynamicLibPath = PythonDynLibName;

                // if (!Target.bBuildEditor)
                // {
                //     PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "lib/Mac/libPython.a"));
                // }
            }
            else if (Target.Platform == UnrealTargetPlatform.IOS)
            {
                // PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "lib/IOS/libPython.a"));
            }
            else        // UnrealTargetPlatform.Android
            {
                // //PublicLibraryPaths.Add(Path.Combine(ModuleDirectory, "lib/Android/ARMv7"));
                // //PublicLibraryPaths.Add(Path.Combine(ModuleDirectory, "lib/Android/ARM64"));
                // //PublicAdditionalLibraries.Add("Python");
                // PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "lib/Android/ARMv7/libPython.a"));
                // PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "lib/Android/ARM64/libPython.a"));
            }

            if (Target.bBuildEditor == true)
            {
                //PublicDelayLoadDLLs.Add(PythonDynLibName);
                RuntimeDependencies.Add(PythonDynamicLibPath);
            }

            PublicSystemIncludePaths.Add(Path.Combine(ModuleDirectory, "Include"));
            PublicSystemIncludePaths.Add(Path.Combine(ModuleDirectory, "Include/Python"));
        }
    }
}