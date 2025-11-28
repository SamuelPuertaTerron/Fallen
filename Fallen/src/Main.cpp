#include "FallenGlobals.h"
#include "Game/Fallen.h"

namespace Fallen
{
	static int Main()
	{
		auto fallenGame = std::make_shared<Fallen>();
		Engine::GetInstance().CreateAndRun(fallenGame);
		return 0;
	}
}//namespace Fallen

#ifdef FE_DEBUG
int main()
{
	return Fallen::Main();
}
#elif FE_RELEASE //FR_DEBUG 
	#ifdef FE_PLATFORM_WINDOWS
		#include <Windows.h>
		int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
		{
			return Fallen::Main();
		}
	#else //FE_PLATFORM_WINDOWS
		//Anything But Windows will use the default int main()
		int main()
		{
			return Fallen::Main();
		}
	#endif//FE_PLATFORM_NOT_WINDOWS 
#endif //FR_RELEASE
