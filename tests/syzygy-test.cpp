#include <iostream>
#include <fstream>
#include <string>

#include "gtest/gtest.h"

#include "./../position.h"
#include "./../syzygy/tbprobe.h"

TEST(Syzygy, test)
{
	Position pos;
	
	std::string line;
	std::ifstream myfile ("D:/vajolet/testsyzygy.csv/testsyzygy.csv");
	
	ASSERT_TRUE(myfile.is_open());
	
	tb_init("D:/vajolet/syzygy");
	ASSERT_TRUE(TB_LARGEST > 0);
	
	
	unsigned long int num = 0;
	unsigned long int testedNum = 0;
	while ( std::getline (myfile,line) )
	{
		++num;
		//std::cout << line << std::endl;
		
		size_t delimiter = line.find_first_of(',');
		ASSERT_NE(std::string::npos, delimiter);
		std::string fen = line.substr(0, delimiter);
		
		line = line.substr(delimiter+1);
		delimiter = line.find_first_of(',');
		ASSERT_NE(std::string::npos, delimiter);
		std::string dtz = line.substr(0, delimiter);
		
		line = line.substr(delimiter+1);
		delimiter = line.find_first_of(',');
		ASSERT_NE(std::string::npos, delimiter);
		std::string wdl = line.substr(0, delimiter);
		
		
		
		pos.setupFromFen(fen); 
		
		
		unsigned result1 = tb_probe_wdl(pos.getBitmap(Position::whitePieces),
			pos.getBitmap(Position::blackPieces),
			pos.getBitmap(Position::blackKing) | pos.getBitmap(Position::whiteKing),
			pos.getBitmap(Position::blackQueens) | pos.getBitmap(Position::whiteQueens),
			pos.getBitmap(Position::blackRooks) | pos.getBitmap(Position::whiteRooks),
			pos.getBitmap(Position::blackBishops) | pos.getBitmap(Position::whiteBishops),
			pos.getBitmap(Position::blackKnights) | pos.getBitmap(Position::whiteKnights),
			pos.getBitmap(Position::blackPawns) | pos.getBitmap(Position::whitePawns),
			0,//pos.getActualState().fiftyMoveCnt,
			pos.getActualState().castleRights,
			pos.getActualState().epSquare == squareNone? 0 : pos.getActualState().epSquare ,
			pos.getActualState().nextMove== Position::whiteTurn);

		//EXPECT_NE(result1, TB_RESULT_FAILED);
		int wdl_res = TB_GET_WDL(result1)-2;
		
		
		unsigned results[TB_MAX_MOVES];
		unsigned result2 = tb_probe_root(pos.getBitmap(Position::whitePieces),
			pos.getBitmap(Position::blackPieces),
			pos.getBitmap(Position::blackKing) | pos.getBitmap(Position::whiteKing),
			pos.getBitmap(Position::blackQueens) | pos.getBitmap(Position::whiteQueens),
			pos.getBitmap(Position::blackRooks) | pos.getBitmap(Position::whiteRooks),
			pos.getBitmap(Position::blackBishops) | pos.getBitmap(Position::whiteBishops),
			pos.getBitmap(Position::blackKnights) | pos.getBitmap(Position::whiteKnights),
			pos.getBitmap(Position::blackPawns) | pos.getBitmap(Position::whitePawns),
			pos.getActualState().fiftyMoveCnt,
			pos.getActualState().castleRights,
			pos.getActualState().epSquare == squareNone? 0 : pos.getActualState().epSquare ,
			pos.getActualState().nextMove== Position::whiteTurn,
			results);
			
		//EXPECT_NE(result2, TB_RESULT_FAILED);
		int dtz_res = TB_GET_DTZ(result2);
		
		if( result1 != TB_RESULT_FAILED && result2 != TB_RESULT_FAILED )
		{
			
			++testedNum;
			if( wdl_res != std::stoi(wdl) || ( (result2 != TB_RESULT_CHECKMATE) && dtz_res!= std::abs(std::stoi(dtz))))
			{
				std::cout <<"-------------------"<< std::endl;
				std::cout <<"FEN: "<< fen << std::endl;
				std::cout <<"DTZ: "<< dtz << std::endl;
				std::cout <<"WDL: "<< wdl << std::endl;
				std::cout <<"PROBE DTZ:"<< dtz_res << std::endl;
				std::cout <<"PROBE WDL:"<< wdl_res << std::endl;
				std::cout <<"checkmate:"<< (TB_RESULT_CHECKMATE == result2 )<<std::endl;
				//exit(0);
			}
			EXPECT_EQ(wdl_res, std::stoi(wdl));
			EXPECT_EQ(dtz_res, (result2 != TB_RESULT_CHECKMATE)? std::abs(std::stoi(dtz)): 0);
		}
		
		
		//std::cout<<pos.getFen()<<std::endl;
		
		if( num %10000 == 0 )
		{
			std::cout<<testedNum<<"/"<<num<<" ("<< (testedNum*100.0/num) <<"%)"<<std::endl;
		}
		
	}
	std::cout<<num<<std::endl;
	myfile.close();
	


}


