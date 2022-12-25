#pragma once
#include <string>
#include <windows.h>

class SysInf
{
private:
    int _numCores;
    std::string _procArch;
    std::string _opSys;

    std::string getProcArch(SYSTEM_INFO);
    std::string getOsName();

public:
    SysInf();
    int GetNumCores();
    std::string GetProcArch();
    std::string GetOpSys();
};

