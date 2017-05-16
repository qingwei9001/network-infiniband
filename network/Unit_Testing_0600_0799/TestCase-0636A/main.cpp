#include <windows.h>
#include "NetworkInterface.h"
#include "common\CommonInterface.h"

//FUNCTION: detect the memory leak in DEBUG mode
void installMemoryLeakDeteor()
{
	// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	//_CRTDBG_LEAK_CHECK_DF: Perform automatic leak checking at program exit through a call to _CrtDumpMemoryLeaks and generate an error 
	//report if the application failed to free all the memory it allocated. OFF: Do not automatically perform leak checking at program exit.
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//the following statement is used to trigger a breakpoint when memory leak happens
	//comment it out if there is no memory leak report;
	//_crtBreakAlloc = 3017;
#endif 
}

int main(int, char**)
{
	installMemoryLeakDeteor();
	hiveCommon::hiveLoadTestingDLLs();

	try
	{
		if (hiveNetworkCommon::initNetwork("NetworkEnvSource.cfg"))
		{
			hiveCommon::hiveOutputEvent("Network has been initialized successfully", hiveCommon::WARNING_LEVEL);
		}
		else
		{
			hiveCommon::hiveOutputEvent("Network fails to initialize", hiveCommon::WARNING_LEVEL);
		}
		Sleep(1000);
		hiveNetworkCommon::hiveStopNetwork();
		std::cout << "1.txt" << " (MD5) : " << hiveCommon::hiveComputeMD5(std::string("1.txt")) << std::endl;
	}
	catch (...)
	{
		hiveCommon::hiveOutputWarning(__EXCEPTION_SITE__, "The program is terminated due to unexpected Error");
	}
	return 0;
}