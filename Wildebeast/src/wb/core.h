#pragma once

// On Windows, handle DLL import/export
#ifdef WB_PLATFORM_WINDOWS

	// if building DLL (on build of Engine), export DLL decls
	#ifdef WB_BUILD_DLL

		#define WB_API __declspec(dllexport)

	// otherwise the headers are imported, so import DLL decls
	#else

		#define WB_API __declspec(dllimport)

	#endif

#else

	#error "Wildebeast onyl supports Windows atm..."

#endif