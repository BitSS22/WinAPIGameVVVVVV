#include <assert.h>

#ifdef _DEBUG
#define MSGASSERT(VALUE) {string ErrorText = VALUE; MessageBoxA(nullptr, ErrorText.c_str(), "ERROR", MB_OK); assert(nullptr);}
#else
#define MSGASSERT(VALUE) (VALUE);
#endif // _DEBUG

