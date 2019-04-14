/*
	This file is part of Vajolet.

    Vajolet is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Vajolet is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Vajolet.  If not, see <http://www.gnu.org/licenses/>
*/

#ifndef MULTIPVMANAGER_H_
#define MULTIPVMANAGER_H_

#include <algorithm>
#include <cassert>
#include <memory>
#include <vector>

#include "rootMove.h"

class MultiPVManager
{
public:

	/* factory method */
	enum type
	{
		multiPv,		// standard multiPV
		standardSearch	// no output
	};
	
	static std::unique_ptr<MultiPVManager> create(const MultiPVManager::type t  = MultiPVManager::standardSearch);
	
	virtual ~MultiPVManager(){};
	
	void clean();
	void startNewIteration();
	void goToNextPV();
	virtual void insertMove(const rootMove& m) = 0;
	void setLinesToBeSearched(const unsigned int l);
	bool thereArePvToBeSearched() const;
	
	
	bool getNextRootMove(rootMove& rm) const;
	
	unsigned int getLinesToBeSearched() const;
	unsigned int getPVNumber() const;
	
	std::vector<rootMove> get() const;
	
protected:
	std::vector<rootMove> _res;
	std::vector<rootMove> _previousRes;
	unsigned int _linesToBeSearched;
	unsigned int _multiPvCounter;
};


#endif