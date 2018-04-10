#ifdef _WIN32
#define IRENDER_API __declspec(dllexport)
#else
#define IRENDER_API 
#endif

namespace IRender {

  /// <summary>
  /// Produces a rendering context and connects it to the provided window context.
  /// </summary>
  /// <param name = "idx">The index of the window being validated.</param>
  /// <param name = "ctx">The pointer to the platform's display context.</param>
  IRENDER_API void CreateContext(const int, void* const);
  
  IRENDER_API void SwapBuffer(const int, void* const);
}