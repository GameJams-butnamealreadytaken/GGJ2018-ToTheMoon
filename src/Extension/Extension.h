#pragma once

#if defined(_WIN32)
#	if defined(ExtGGJ2018_EXPORTS)
#		define EXTENSION_EXPORT __declspec(dllexport)
#	else
#		define EXTENSION_EXPORT __declspec(dllimport)
#	endif // Extension_EXPORTS
#else // defined(_WIN32)
#	define EXTENSION_EXPORT
#endif

class CShIdentifier;

extern "C"
{
	EXTENSION_EXPORT void	ExtensionInitialize			(void);
	EXTENSION_EXPORT void	ExtensionRelease			(void);

	EXTENSION_EXPORT void	ExtensionOnPluginStarted	(const CShIdentifier & levelIdentifier);
	EXTENSION_EXPORT void	ExtensionOnPluginStopped	(const CShIdentifier & levelIdentifier);
}
