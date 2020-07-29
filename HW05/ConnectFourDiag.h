/*
	HW05 Emire Korkmaz

	 This class is derived from ConnectFourAbstract class. It plays very
	similar to regular Connect Four but it only accepts diagonally
	connected cells as the goal of the game. It overwrote
	whoWon() function.

*/
#ifndef CONNECTFOURDIAG_H
#define CONNECTFOURDIAG_H

#include "ConnectFourAbstract.h"
#include <string>

using namespace std;

namespace Korkmaz{
	class ConnectFourDiag : public ConnectFourAbstract {
		public:
			ConnectFourDiag(): ConnectFourAbstract(){
			}
		private:
			virtual bool whoWon();
	};
}
#endif