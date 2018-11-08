#include <vector>
#include "gtest/gtest.h"
#include "./../timeManagement.h"


TEST(timeManagement, infiniteSearch)
{	
	SearchLimits s;
	s.infinite = true;

	timeManagement tm( s );

	tm.initNewSearch( Position::whiteTurn );

	ASSERT_EQ( tm.getResolution(), 100 );

	long long int t = 0;
	unsigned long long n = 0;

	for( int i = 0; i < 100000; ++i)
	{
		t += 100;
		n += 800;

		if( i % 17 == 0 )tm.notifyIterationHasBeenFinished();
		if( i % 23 == 0 )tm.notifyFailOver();
		if( i % 29 == 0 )tm.notifyFailLow();

		ASSERT_EQ( tm.stateMachineStep( t, n ), false );

		ASSERT_EQ( tm.isSearchFinished(), false );
	}

	tm.stop();
	for( int i = 0; i < 10000; ++i)
	{
		t += 100;
		n += 800;

		tm.notifyIterationHasBeenFinished();
		ASSERT_EQ( tm.stateMachineStep( t, n ), true );
		ASSERT_EQ( tm.isSearchFinished(), true );
	}
}

TEST(timeManagement, NodesSearchStop)
{
	SearchLimits s;
	s.nodes = 100000000;
	s.checkInfiniteSearch();

	timeManagement tm( s );

	tm.initNewSearch( Position::whiteTurn );

	ASSERT_EQ( tm.getResolution(), 100 );

	long long int t = 0;
	unsigned long long n = 0;

	for( int i = 0; i < 100000; ++i)
	{
		t += 100;
		n += 800;

		if( i % 17 == 0 )tm.notifyIterationHasBeenFinished();
		if( i % 23 == 0 )tm.notifyFailOver();
		if( i % 29 == 0 )tm.notifyFailLow();

		ASSERT_EQ( tm.stateMachineStep( t, n ), false );
		ASSERT_EQ( tm.isSearchFinished(), false );
	}

	tm.stop();

	for( int i = 0; i < 10000; ++i)
	{
		t += 100;
		n += 800;

		tm.notifyIterationHasBeenFinished();
		ASSERT_EQ( tm.stateMachineStep( t, n ), true );
		ASSERT_EQ( tm.isSearchFinished(), true );
	}
}

TEST(timeManagement, NodesSearch)
{

	SearchLimits s;
	s.nodes = 1000000;
	s.checkInfiniteSearch();

	timeManagement tm( s );

	tm.initNewSearch( Position::whiteTurn );

	ASSERT_EQ( tm.getResolution(), 100 );

	long long int t = 0;
	unsigned long long n = 0;

	for( int i = 0; i < 100000; ++i)
	{
		t += 100;
		n += 800;

		if( i % 17 == 0 )tm.notifyIterationHasBeenFinished();
		if( i % 23 == 0 )tm.notifyFailOver();
		if( i % 29 == 0 )tm.notifyFailLow();

		ASSERT_EQ( tm.stateMachineStep( t, n ), n >= s.nodes ? true: false );
		ASSERT_EQ( tm.isSearchFinished(), n >= s.nodes ? true: false );
	}
}

TEST(timeManagement, moveTimeSearchStop)
{
	SearchLimits s;
	s.moveTime = 100000000;
	s.checkInfiniteSearch();

	timeManagement tm( s );

	tm.initNewSearch( Position::whiteTurn );

	ASSERT_EQ( tm.getResolution(), 100 );

	long long int t = 0;
	unsigned long long n = 0;

	for( int i = 0; i < 100000; ++i)
	{
		t += 100;
		n += 800;

		if( i % 17 == 0 )tm.notifyIterationHasBeenFinished();
		if( i % 23 == 0 )tm.notifyFailOver();
		if( i % 29 == 0 )tm.notifyFailLow();

		ASSERT_EQ( tm.stateMachineStep( t, n ), false );
		ASSERT_EQ( tm.isSearchFinished(), false );
	}

	tm.stop();

	for( int i = 0; i < 10000; ++i)
	{
		t += 100;
		n += 800;

		tm.notifyIterationHasBeenFinished();
		ASSERT_EQ( tm.stateMachineStep( t, n ), true );
		ASSERT_EQ( tm.isSearchFinished(), true );
	}
}

TEST(timeManagement, moveTimeSearch)
{

	SearchLimits s;
	s.moveTime = 1000000;
	s.checkInfiniteSearch();

	timeManagement tm( s );

	tm.initNewSearch( Position::whiteTurn );

	ASSERT_EQ( tm.getResolution(), 100 );

	long long int t = 0;
	unsigned long long n = 0;

	for( int i = 0; i < 100000; ++i)
	{
		t += 100;
		n += 800;

		if( i % 17 == 0 )tm.notifyIterationHasBeenFinished();
		if( i % 23 == 0 )tm.notifyFailOver();
		if( i % 29 == 0 )tm.notifyFailLow();

		ASSERT_EQ( tm.stateMachineStep( t, n ), t >= s.moveTime ? true: false );
		ASSERT_EQ( tm.isSearchFinished(), t >= s.moveTime ? true: false );
	}
}

TEST(timeManagement, moveTimeSearch2)
{

	SearchLimits s;
	s.moveTime = 1000;
	s.checkInfiniteSearch();

	timeManagement tm( s );

	tm.initNewSearch( Position::whiteTurn );
	ASSERT_EQ( tm.getResolution(), 10 );

	s.moveTime = 100;
	tm.initNewSearch( Position::whiteTurn );
	ASSERT_EQ( tm.getResolution(), 1 );

	s.moveTime = 100000;
	tm.initNewSearch( Position::whiteTurn );
	ASSERT_EQ( tm.getResolution(), 100);

	ASSERT_EQ( tm.stateMachineStep( 100, 10000 ), false);
	ASSERT_EQ( tm.isSearchFinished(), false );
	ASSERT_EQ( tm.stateMachineStep( 1000, 10000 ), false);
	ASSERT_EQ( tm.isSearchFinished(), false );
	ASSERT_EQ( tm.stateMachineStep( 100000000, 10000 ), false);
	ASSERT_EQ( tm.isSearchFinished(), false );

	tm.notifyIterationHasBeenFinished();

	ASSERT_EQ( tm.stateMachineStep( 100, 10000 ), false);
	ASSERT_EQ( tm.isSearchFinished(), false );
	ASSERT_EQ( tm.stateMachineStep( 99999, 10000 ), false);
	ASSERT_EQ( tm.isSearchFinished(), false );
	ASSERT_EQ( tm.stateMachineStep( 100000, 10000 ), true);
	ASSERT_EQ( tm.isSearchFinished(), true );






}



