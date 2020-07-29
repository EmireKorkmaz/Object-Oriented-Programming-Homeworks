/*
	HW05 Emire Korkmaz

	 This class is derived from ConnectFourAbstract class. It plays very
	similar to regular Connect Four but it only accepts horizontally or
	vertically connected cells as the goal of the game. It overwrote
	whoWon() function.

*/
#ifndef CONNECTFOURPLUS_H
#define CONNECTFOURPLUS_H

#include "ConnectFourAbstract.h"
using namespace std;
namespace Korkmaz{

	class ConnectFourPlus : public ConnectFourAbstract {
		public:
			ConnectFourPlus(): ConnectFourAbstract(){
				
			}
		protected:
			virtual bool whoWon();
	};
}

#endif