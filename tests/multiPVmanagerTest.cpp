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

#include "gtest/gtest.h"
#include "multiPVmanager.h"

TEST(MultiPVManager, functionalTest)
{
	std::unique_ptr<MultiPVManager> x = MultiPVManager::create(MultiPVManager::multiPv);
	PVline p;
	rootMove rm1( Move(E2,E4), p,   12, 5, 15, 124354, 143);
	rootMove rm2( Move(D2,D4), p,   15, 5, 15, 124354, 143);
	rootMove rm3( Move(G1,F3), p,    0, 5, 15, 124354, 143);
	rootMove rm4( Move(A2,A4), p, -100, 5, 15, 124354, 143);
	rootMove rm5( Move(G2,G3), p,  -20, 5, 15, 124354, 143);
	
	rootMove r(Move::NOMOVE);
	
	// initialize
	x->clean();
	x->setLinesToBeSearched(5);
	x->startNewIteration();
	
	// insert moves
	ASSERT_FALSE(x->getNextRootMove(r));
	x->insertMove(rm1);
	x->goToNextPV();
	
	ASSERT_FALSE(x->getNextRootMove(r));
	x->insertMove(rm2);
	x->goToNextPV();
	
	ASSERT_FALSE(x->getNextRootMove(r));
	x->insertMove(rm3);
	x->goToNextPV();
	
	ASSERT_FALSE(x->getNextRootMove(r));
	x->insertMove(rm4);
	x->goToNextPV();
	
	ASSERT_FALSE(x->getNextRootMove(r));
	x->insertMove(rm5);
	x->goToNextPV();
	
	// order
	auto res = x->get();
	
	// test
	ASSERT_EQ( res.size(), 5 );
	ASSERT_EQ( res[0], rm2 );
	ASSERT_EQ( res[1], rm1 );
	ASSERT_EQ( res[2], rm3 );
	ASSERT_EQ( res[3], rm5 );
	ASSERT_EQ( res[4], rm4 );
	
	// start a new iteration
	x->startNewIteration();
	
	
	rootMove rm6( Move(F2,F4), p,   18, 5, 16, 124354, 143);
	rootMove rm7( Move(D2,D4), p,   15, 5, 16, 124354, 143);
	rootMove rm8( Move(G1,F3), p,  20, 5, 16, 124354, 143);
	
	// insert some move
	ASSERT_TRUE(x->getNextRootMove(r));
	ASSERT_EQ(r, rm2);
	x->insertMove(rm6);
	x->goToNextPV();
	
	ASSERT_TRUE(x->getNextRootMove(r));
	ASSERT_EQ(r, rm2);
	x->insertMove(rm7);
	x->goToNextPV();
	
	ASSERT_TRUE(x->getNextRootMove(r));
	ASSERT_EQ(r, rm1);
	x->insertMove(rm8);
	x->goToNextPV();
	
	
	// order
	res = x->get();
	
	// test
	ASSERT_EQ( res.size(), 5 );
	ASSERT_EQ( res[0], rm8 );
	ASSERT_EQ( res[1], rm6 );
	ASSERT_EQ( res[2], rm7 );
	ASSERT_EQ( res[3], rm1 );
	ASSERT_EQ( res[4], rm5 );

	
	
	x->clean();
	x->setLinesToBeSearched(0);
	res = x->get();
	
	ASSERT_EQ( res.size(), 0 );	

}

TEST(MultiPVManager, clean)
{
	std::unique_ptr<MultiPVManager> x = MultiPVManager::create(MultiPVManager::multiPv);
	PVline p;
	rootMove rm1( Move(E2,E4), p,   12, 5, 15, 124354, 143);
	rootMove rm2( Move(D2,D4), p,   15, 5, 15, 124354, 143);
	rootMove rm3( Move(G1,F3), p,    0, 5, 15, 124354, 143);
	rootMove rm4( Move(A2,A4), p, -100, 5, 15, 124354, 143);
	rootMove rm5( Move(G2,G3), p,  -20, 5, 15, 124354, 143);
	
	// initialize
	x->clean();
	x->setLinesToBeSearched(5);
	x->startNewIteration();
	
	// insert some move
	x->insertMove(rm1);
	x->insertMove(rm2);
	x->insertMove(rm3);
	x->insertMove(rm4);
	x->insertMove(rm5);
	
	// start a new iteration
	x->startNewIteration();
	
	// insert some move
	x->insertMove(rm1);
	x->insertMove(rm2);
	x->insertMove(rm3);
	x->insertMove(rm4);
	x->insertMove(rm5);
	
	auto res = x->get();
	ASSERT_EQ( res.size(), 5 );
	x->setLinesToBeSearched(0);
	x->clean();
	res = x->get();
	
	ASSERT_EQ( res.size(), 0 );
	
}

TEST(MultiPVManager, getNextRootMove)
{
	std::unique_ptr<MultiPVManager> x = MultiPVManager::create(MultiPVManager::multiPv);
	PVline p;
	rootMove rm1( Move(E2,E4), p,   12, 5, 15, 124354, 143);
	rootMove rm2( Move(D2,D4), p,   15, 5, 15, 124354, 143);
	rootMove rm3( Move(G1,F3), p,    0, 5, 15, 124354, 143);
	rootMove rm4( Move(A2,A4), p, -100, 5, 15, 124354, 143);
	rootMove rm5( Move(G2,G3), p,  -20, 5, 15, 124354, 143);
	
	// initialize
	x->clean();
	x->setLinesToBeSearched(5);
	x->startNewIteration();
	
	// insert some move
	x->insertMove(rm1);
	x->insertMove(rm2);
	x->insertMove(rm3);
	x->insertMove(rm4);
	x->insertMove(rm5);
	
	x->get();
	
	// start a new iteration
	x->startNewIteration();

	rootMove rm (Move::NOMOVE);
	bool found = x->getNextRootMove(rm);
	ASSERT_EQ( found, true );
	ASSERT_EQ( rm, rm2 );
	
	x->goToNextPV();
	
	found = x->getNextRootMove(rm);
	ASSERT_EQ( found, true );
	ASSERT_EQ( rm, rm1 );
	
	x->goToNextPV();
	
	found = x->getNextRootMove(rm);
	ASSERT_EQ( found, true );
	ASSERT_EQ( rm, rm3 );
	
	x->goToNextPV();
	
	found = x->getNextRootMove(rm);
	ASSERT_EQ( found, true );
	ASSERT_EQ( rm, rm5 );
	
	x->goToNextPV();
	
	found = x->getNextRootMove(rm);
	ASSERT_EQ( found, true );
	ASSERT_EQ( rm, rm4 );
	
	x->goToNextPV();
	
	rootMove rmNull(Move::NOMOVE);
	found = x->getNextRootMove(rmNull);
	ASSERT_EQ( found, false );
	ASSERT_EQ( rmNull, rootMove(Move::NOMOVE) );
}


TEST(MultiPVManager, getLinesToBeSearched)
{
	std::unique_ptr<MultiPVManager> x = MultiPVManager::create(MultiPVManager::multiPv);
	
	x->setLinesToBeSearched(5);
	ASSERT_EQ( x->getLinesToBeSearched(), 5 );
	
	x->setLinesToBeSearched(120);
	ASSERT_EQ( x->getLinesToBeSearched(), 120 );
}

TEST(MultiPVManager, thereArePvToBeSearched)
{
	std::unique_ptr<MultiPVManager> x = MultiPVManager::create(MultiPVManager::multiPv);
	
	x->setLinesToBeSearched(5);
	x->startNewIteration();
	
	ASSERT_EQ(x->getPVNumber() ,0 );
	ASSERT_TRUE(x->thereArePvToBeSearched());
	x->goToNextPV();
	
	ASSERT_EQ(x->getPVNumber() ,1 );
	ASSERT_TRUE(x->thereArePvToBeSearched());
	x->goToNextPV();
	
	ASSERT_EQ(x->getPVNumber() ,2 );
	ASSERT_TRUE(x->thereArePvToBeSearched());
	x->goToNextPV();
	
	ASSERT_EQ(x->getPVNumber() ,3 );
	ASSERT_TRUE(x->thereArePvToBeSearched());
	x->goToNextPV();
	
	ASSERT_EQ(x->getPVNumber() ,4 );
	ASSERT_TRUE(x->thereArePvToBeSearched());
	x->goToNextPV();
	
	ASSERT_EQ(x->getPVNumber() ,5 );
	ASSERT_FALSE(x->thereArePvToBeSearched());

	

}