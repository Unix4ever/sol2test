#ifdef _WIN32
#ifdef _EXPORT
#define COMMON_API __declspec(dllexport)
#else
#define COMMON_API __declspec(dllimport)
#endif

#ifdef _EXPORT_LIBRARY
#define LIBRARY_API __declspec(dllexport)
#else
#define LIBRARY_API __declspec(dllimport)
#endif
#else
#define COMMON_API
#define LIBRARY_API
#endif
