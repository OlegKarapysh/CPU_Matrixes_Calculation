#include "SysInf.h"

    std::string SysInf::getOsName()
    {
#ifdef _WIN64
        return "Windows 64-bit";
#elif _WIN32
        return "Windows 32-bit";
#elif __APPLE__ || __MACH__
        return "Mac OSX";
#elif __linux__
        return "Linux";
#elif __FreeBSD__
        return "FreeBSD";
#elif __unix || __unix__
        return "Unix";
#else
        return "Unknown";
#endif
    }

    std::string SysInf::getProcArch(SYSTEM_INFO sysinfo)
    {
        switch (sysinfo.wProcessorArchitecture)
        {
            case PROCESSOR_ARCHITECTURE_AMD64:
                return "x64";

            case PROCESSOR_ARCHITECTURE_INTEL:
                return "x86";

            case PROCESSOR_ARCHITECTURE_ARM:
                return "ARM";

            case PROCESSOR_ARCHITECTURE_ARM64:
                return "ARM64";
            
            case PROCESSOR_ARCHITECTURE_IA64:
                return "Intel Itanium-based";

            default: return "Unknown";
        }
    }

    SysInf::SysInf()
	{
		SYSTEM_INFO sysinfo;
		GetSystemInfo(&sysinfo);
		_numCores = sysinfo.dwNumberOfProcessors;
        _procArch = getProcArch(sysinfo);
        _opSys = getOsName();
	}

    int SysInf::GetNumCores()
    {
        return _numCores;
    }

    std::string SysInf::GetProcArch()
    {
        return _procArch;
    }

    std::string SysInf::GetOpSys()
    {
        return _opSys;
    }
