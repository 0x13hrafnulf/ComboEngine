#ifdef ENABLE_ASSERTS
  #define COMBO_ASSERT(x, ...) { if(!(x)) {COMBO_ERROR_LOG("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
  #define ASSERT(x, ...) { if(!(x)) {CLIENT_ERROR_LOG("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
  #define COMBO_ASSERT(x, ...)
  #define ASSERT(x, ...)
#endif
