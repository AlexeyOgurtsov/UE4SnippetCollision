#include "CollGameMode.h"
#include "CollPlayerController.h"
#include "CollPawn.h"
#include "CollConfig.h"
#include "Util/Core/LogUtilLib.h"

MyGameModeType::ACollGameMode()
{
	DefaultPawnClass = MyPawnType::StaticClass();
	PlayerControllerClass = MyPCType::StaticClass();
}
