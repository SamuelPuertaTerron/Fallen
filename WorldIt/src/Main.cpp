#include "WorldItGlobals.h"
#include "WorldIt/WorldIt.h"

namespace WorldIt
{
	static int Main()
	{
		auto worldIt = std::make_shared<WorldIt>();
		Engine::GetInstance().CreateAndRun(worldIt);
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
		//Anything But Windows will use the default int main()
		int main()
		{
			return WorldIt::Main();
		}
	#endif // Other Platforms
#endif //FR_RELEASE
