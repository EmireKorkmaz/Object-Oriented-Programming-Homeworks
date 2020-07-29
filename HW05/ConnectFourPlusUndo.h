/*
	HW05 Emire Korkmaz

	 This class is derived from ConnectFourPlus class. It plays very
	similar to ConnectFourPlus but it also has UNDO feature. It can
	undo the moves of the user or the computer until the beginning
	of the game. It overwrote play(string m) function.

*/
#ifndef ConnectFourPlusUndo_H
#define ConnectFourPlusUndo_H

#include "ConnectFourPlus.h"
namespace Korkmaz{
	class ConnectFourPlusUndo : public ConnectFourPlus{
		public:
			ConnectFourPlusUndo();
			int play(string m);	
		private:
			void undo(int index);
	};
}
#endif