#include "Engine\Core/CoreEngine.h"
#include "Game\Game1.h"
#undef main
// IT DOESN'T MATTER WHICH "/" OR "\" YOU USE! FOR INCLUDES ONLY :O 


int main(int argc, char* argv[]) {
	CoreEngine::GetInstance()->SetGameInterface(new Game1);

	if (!CoreEngine::GetInstance()->OnCreate("Jairo's Engine", 800, 600)) {
		return 0;
	}

	CoreEngine::GetInstance()->Run();

	return 0;
}
