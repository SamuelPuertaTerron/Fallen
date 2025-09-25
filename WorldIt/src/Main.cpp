#include "WorldItGlobals.h"
#include "WorldIt/WorldIt.h"

namespace WorldIt
{
	static int Main()
	{
		auto fallenGame = std::make_shared<WorldIt>();
		Engine::GetInstance().CreateAndRun(fallenGame);
		return 0;
	}
}//namespace Fallen

#ifdef FE_DEBUG
int main()
{
	return WorldIt::Main();
}
#elif FE_RELEASE //FR_DEBUG 

	#ifdef FE_PLATFORM_WINDOWS
		#include <Windows.h>
		int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
		{
			return WorldIt::Main();
		}
	#else //FE_PLATFORM_WINDOWS
		int main()
		{
			return WorldIt::Main();
		}
	#endif //Anything But Windows will use the default int main()
#endif //FR_RELEASE
