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

#include "multiPVmanager.h"

class OrderedMultiPVManager: public MultiPVManager {
public:
	void insertMove(const rootMove& m);
	std::vector<rootMove> get() const;
};

void OrderedMultiPVManager::insertMove(const rootMove& m) {_res.push_back(m); std::stable_sort(_res.begin(), _res.end());}

class UnorderedMultiPVManager: public MultiPVManager {
public:
	void insertMove(const rootMove& m);
	std::vector<rootMove> get() const;
};

void UnorderedMultiPVManager::insertMove( const rootMove& m ) {_res.push_back(m);}


/*****************************
uci output factory method implementation
******************************/
std::unique_ptr<MultiPVManager> MultiPVManager::create(const MultiPVManager::type t)
{
	// todo create new type
	if(t == multiPv)
	{
		return std::make_unique<OrderedMultiPVManager>();
	}
	else// if(t == UnorderedMultiPVManager)
	{
		return std::make_unique<OrderedMultiPVManager>();
	}
}



void MultiPVManager::clean(){ _res.clear(); _previousRes.clear();}
void MultiPVManager::startNewIteration(){ _previousRes = _res; _res.clear(); _multiPvCounter = 0;}
void MultiPVManager::goToNextPV(){ ++_multiPvCounter; }
//void MultiPVManager::insertMove( const rootMove& m ){ _res.push_back(m); std::stable_sort(_res.begin(), _res.end());}
void MultiPVManager::setLinesToBeSearched( const unsigned int l ){ _linesToBeSearched = l;}
bool MultiPVManager::thereArePvToBeSearched() const { return _multiPvCounter < _linesToBeSearched; }


bool MultiPVManager::getNextRootMove(rootMove& rm) const
{
	auto list = get();
	
	if ( _multiPvCounter < list.size())
	{
		rm = list[_multiPvCounter];
		return true;
	}
	return false;
}

unsigned int MultiPVManager::getLinesToBeSearched() const { return _linesToBeSearched; }
unsigned int MultiPVManager::getPVNumber() const { return _multiPvCounter;}

std::vector<rootMove> MultiPVManager::get() const
{	
	// Sort the PV lines searched so far and update the GUI	
	std::vector<rootMove> _multiPVprint = _res;

	// always send all the moves toghether in multiPV
	int missingLines = _linesToBeSearched - _multiPVprint.size();
	if( missingLines > 0 )
	{
		// add result from the previous iteration
		// try adding the missing lines (  uciParameters::multiPVLines - _multiPVprint.size() ) , but not more than previousIterationResults.size() 
		int addedLines = 0;
		for( const auto& m: _previousRes )
		{
			if( std::find(_multiPVprint.begin(), _multiPVprint.end(), m) == _multiPVprint.end() )
			{
				_multiPVprint.push_back(m);
				++addedLines;
				if( addedLines >= missingLines )
				{
					break;
				}
			}
		}
	}
	//assert(_multiPVprint.size() == _linesToBeSearched);
	
	return _multiPVprint;
}
