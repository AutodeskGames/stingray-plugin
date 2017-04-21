#pragma once

#if (defined(WINDOWSPC) || defined(XBOXONE)) && defined(DEVELOPMENT)

	#include <float.h>

	namespace stingray_plugin_foundation {

		// Disable FPU exceptions in scope and restore on exit.
		struct FpuUnsafeScope {
			unsigned _initial_control_word;

			FpuUnsafeScope() {
				_initial_control_word = _controlfp(0,0);
				_controlfp(~0U, _MCW_EM);
			}

			~FpuUnsafeScope() {
				_clearfp();
				_controlfp(_initial_control_word, _MCW_EM);
			}
		};
	}
#else
	namespace stingray_plugin_foundation {

		struct FpuUnsafeScope {
			FpuUnsafeScope() {}
			~FpuUnsafeScope() {}
		};

	}
#endif
