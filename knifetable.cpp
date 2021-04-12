#include "knifetable.h"
#include "search.h"
#include "uci.h"
#include "position.h"

KeyMove knifeTable;


void KnifeTable::add(const std::string& fen, const std::string& m){
	Position pos;
	StateInfo si;
	pos.set(fen, &si, nullptr);
	knifeTable[pos.key()] = UCI::to_move(m);
}

void KnifeTable::init() {
	
	         
	//下面设置起步为炮二平五
    //	add("rnbakabnr/9/1c5c1/p1p1p1p1p/9/9/P1P1P1P1P/1C5C1/9/RNBAKABNR w - - 0 1", "h2e2");       //起步炮二平五;设置起步会冲突，切记!
    //中炮局;

	//add("rnbakab1r/9/1c4nc1/p1p1p3p/6p2/2P6/P3P1P1P/1CN4C1/9/R1BAKABNR w - - 0 2", "h0i2");    //马二进一;
	//add("rnbakab2/8r/1c5c1/p1p1p3p/6pn1/2P6/P3P1P1P/1CN3C1N/9/R1BAKAB1R w - - 0 4", "b2a2");   //炮八平九;
	add("rnbakab2/8r/1c5c1/p1p1p3p/6pn1/2P6/P3P1P1P/C1N3C1N/9/R1BAKAB1R b - - 0 5 ", "c9e7");   //象３进５ ;
	add("rn1akab2/8r/1c2b2c1/p1p1p3p/6pn1/2P6/P3P1P1P/C1N3C1N/9/R1BAKAB1R w - - 0 5", "a0b0");   //车九平八 ;
	add("rn1akab2/8r/1c2b2c1/p1p1p3p/6pn1/2P6/P3P1P1P/C1N3C1N/9/1RBAKAB1R b - - 0 6", "b9d8");   //马２进４ ;
	add("r2akab2/3n4r/1c2b2c1/p1p1p3p/6pn1/2P6/P3P1P1P/C1N3C1N/9/1RBAKAB1R w - - 0 6", "b0b5");   //车八进五 ;
	add("r2akab2/3n4r/1c2b2c1/p1p1p3p/1R4pn1/2P6/P3P1P1P/C1N3C1N/9/2BAKAB1R b - - 0 7", "c6c5");   //卒３进１;
	add("r2akab2/3n4r/1c2b2c1/p3p3p/1Rp3pn1/2P6/P3P1P1P/C1N3C1N/9/2BAKAB1R w - - 0 7", "c4c5");   //兵七进一;
	add("r2akab2/3n4r/1c2b2c1/p3p3p/1RP3pn1/9/P3P1P1P/C1N3C1N/9/2BAKAB1R b - - 0 8", "a9c9");   //车１平３;
	add("2rakab2/3n4r/1c2b2c1/p3p3p/1RP3pn1/9/P3P1P1P/C1N3C1N/9/2BAKAB1R w - - 0 8 ", "i0i1");   //车一进一 ;
	add("2rakab2/3n4r/1c2b2c1/p3p3p/1R4p2/9/P3P1P1n/C1N1C3N/3R5/2BAKAB2 w - - 0 11 ", "c2d4");   //马七进六 ;
	add("2rakab2/3n4r/1c5c1/p3p3p/1Rb3p2/9/P3P1P1n/C1N1C3N/3R5/2BAKAB2 b - - 0 11", "c5e7");   //象３退５;
	add("2rakab2/3n1r3/1c2b2c1/p3p3p/1R4p2/3N5/P3P1P1n/C3C3N/3R5/2BAKAB2 w - - 0 12", "a2a6");   //炮九进四 ;
	add("2rakab2/3n4r/1c5c1/p3p3p/1Rb3p2/9/P3P1P1n/C1N1C3N/8R/2BAKAB2 w - - 0 10", "i1d1");   //车一平六;
	add("2rakab2/3n4r/1c2b2c1/p3p3p/1RP3p2/9/P3P1P1n/C1N1C3N/8R/2BAKAB2 b - - 0 10 ", "e7c5");   //象５进３ ;
	//add("1crakab2/3n4r/4b2c1/p3p3p/1RP3pn1/9/P3P1P1P/C1N1C3N/8R/2BAKAB2 b - - 0 10 ", "d8b7");   //马４进２ ;
	//add("2rakab2/3n4r/1c2b2c1/p3p3p/1RP3pn1/9/P3P1P1P/C1N3C1N/8R/2BAKAB2 b - - 0 9", "b7b9");   //炮２退２;
	add("2rakab2/3n4r/1c2b2c1/p3p3p/1RP3p2/9/P3P1P1n/C1N3C1N/8R/2BAKAB2 w - - 0 9", "g2e2");   //炮三平五 ;
	add("2rakab2/3n4r/1c2b2c1/p3p3p/1R4p2/3N5/P3P1P1n/C3C3N/3R5/2BAKAB2 b - - 0 12", "i8f8");   //车９平６ ;
	add("2b1kab2/4a4/3c5/p3Nr2p/2P6/1R1N2p2/P3P2c1/C7B/4A3n/4KAB2 b - - 0 1", "d7g7");         //炮4平7
	add("2bk1ab2/4a4/2c6/4C3p/2N6/1RP3p2/P3P1c1n/8B/4Nr3/2BAKA3 w - - 0 1", "e6d6");           //炮5平6
	add("2bakab2/1r7/4c4/p1C1R3p/9/2P6/P3P3P/4B1r2/R3A4/4KA3 w - - 0 18", "e2c0");             //相五退七
	add("r1bakabr1/9/1cn3nc1/p1p1p2Rp/6p2/2P6/P3P1P1P/1C2C1N2/9/RNBAKAB2 b - - 0 5", "h7i7");  //炮8平9
	
	add("rnbakabnr/9/1c5c1/p1p1p3p/6p2/2P6/P3P1P1P/1CN4C1/9/R1BAKABNR b - - 0 2", "h9g7");     //马8进7
	add("1rbakab1r/9/1cn3nc1/p1p1p3p/6p2/2P6/P3P1P1P/C1N4C1/9/1RBAKABNR w - - 0 4", "g0e2");   //象3进5
	add("1rbaka2r/9/1cn1b1nc1/p1p1p3p/6p2/1RP6/P3P1P1P/C1N1B2C1/9/2BAKA1NR b - - 0 6", "b7a7");//炮2平1
	add("2baka2r/9/c1n3nc1/p3p2Cp/2b3p2/9/P3P1P1P/C1N1B1N2/9/2BAKA2R w - - 0 10", "c2d4");     //马七进六
	add("2baka2r/9/c1n1b2c1/C3p3p/6pn1/3N5/P3P1P1P/C3B1N2/9/2BAKA2R w - - 0 12", "f0e1");      //仕四进五
	add("2baka2r/9/c1n1b2c1/C3p3p/6pn1/3N5/P3P1P1P/C3B1N2/4A4/2BAK3R b - - 0 13", "f9e8");     //士6进5
	add("2bak4/4a4/2n1b1c2/2C6/P3p1p1p/3N5/4P1n1P/4B1N2/4A4/2BAK4 w - - 0 21", "d4b5");        //马六进八
	add("rnbakabnr/9/1c5c1/p1p1p1p1p/9/6P2/P1P1P3P/1C5C1/9/RNBAKABNR b - - 0 1", "c6c5");      //卒3进1
	add("rnbakabr1/9/1c4nc1/p1p1p1p1p/9/6P2/P1P1P3P/1C2C1N2/9/RNBAKAB1R b - - 0 3", "h7i7");   //炮8平9
	
	add("r2akabr1/9/1cn1b1nc1/p3p1p1p/2p6/6P2/P1P1P3P/NC2C1N2/9/R1BAKABR1 w - - 0 5", "a0a1");  //车九进一
	add("r2akabr1/9/1cn1b1n2/p3p1p1p/2p6/6P2/P1P1P2cP/NC2C1N2/R8/2BAKABR1 w - - 0 6", "b2c2");  //炮八平七
	add("1r1akabr1/9/1c4n2/p3p1p1p/1nb6/6P2/P3P2cP/N1C1C1N2/R8/2BAKABR1 w - - 0 9", "g2f4");    //马三进四
	add("rnbakabnr/9/1c5c1/p3p1p1p/2p6/6P2/P1P1P3P/NC5C1/9/R1BAKABNR b - - 0 2", "b9c7");       //马２进３
	add("2bak4/1P7/3ab4/4R1P2/2r6/6B2/9/9/4A4/3AK4 b - - 0 98", "d7e8");                        //士4退5
	add("2bak4/1P2a4/4b4/4R1P2/2r6/6B2/9/9/9/3AKA3 b - - 0 97", "e7g9");                        //象５退７
	add("2bak1b2/1P2a4/9/3R2P2/2r6/6B2/9/9/4A4/3AK4 b - - 0 100", "c5e5");                      //车３平５
	add("2bak1b2/1P2a4/2r6/4R1P2/9/6B2/9/9/4A4/3AK4 b - - 0 101", "c7e7");                      //车3平5
	add("1c1akabr1/4n3c/2r1b4/p3p1C1p/3R5/2p3P2/P1n1P3P/2C3N2/4N4/R1BAKAB2 w - - 0 14", "g2f4");  //马三进四      
	add("1r1akabr1/9/1c4n2/p3p1p1p/2b6/5NP2/n3P2cP/N1C1C4/R8/2BAKABR1 w - - 0 10", "a1c1");     //车九平七 
	add("3akabr1/9/4c1n2/p3p1p1p/2bNc4/1r4P2/n1C1P2RP/N3C4/2R6/2BAKAB2 w - - 0 14", "d5e7");    //马6进5
	add("4ka3/4aC3/4b3b/p2R4p/9/4c1p2/r4n3/1N2B1C2/4A4/4KAB2 w - - 0 34", "d6d3");              //车六退三
	add("r1bak1br1/4a4/1cn3nc1/p3p1p1p/2p6/6P2/P1P1P3P/NC2C1N2/9/R1BAKABR1 w - - 0 5", "a0a1");    //车九进一
	//add("3a5/4k4/4b4/p1n4Np/6p2/9/P3P3P/c1N5B/4A4/4KA3 w - - 0 39", "i2g0");                    //相一退三//仕五退四
	add("3ak4/9/4b4/p1n6/5Np1p/4P4/P7P/2N2c2B/9/4KA3 w - - 0 42", "c2e3");                      // 马七进六
	add("4k1b2/4a4/9/p1nN5/6p1p/2N1P4/P4c2P/8B/9/4KA3 w - - 0 45", "c4b6");                     //马七进八
	add("4k4/7N1/4b1c2/p2P1N3/8p/3n5/P6pP/8B/9/3K1A3 w - - 0 62", "d0e0");                     //帅6平5
	add("9/4k2N1/3Nb4/p8/8p/3n5/P7p/8B/9/4KA3 w - - 0 65", "d7c9");                            //马6进7
	add("2N1k4/7N1/4b4/p8/8p/3n5/P7p/8B/9/4KA3 w - - 0 66", "c9d7");                           //马七退六
	add("4k4/1CR6/5an2/9/9/7p1/9/4CA2B/9/r2cKA3 w - - 0 83", "c8c9");                          //车七进一
	//add("r1bakab1r/9/1cn1c1n2/p3p1p1p/2p6/6P2/P1P1P3P/NC4N1C/9/R1BAKABR1 b - - 0 5", "c7d5");    //马3进4//车九进一
	add("4kab2/2r1a4/4b2c1/4p3p/p6C1/2NR4P/P1c1P2n1/4B4/1C2A4/2BAK4 w - - 0 21 ", "b1c1");    //炮八平七
	add("2b1kabr1/4a4/2n6/2p1p3p/5R3/C1P3p2/P1c1P1c1n/3CB4/4N4/1N1AKAB2 b - - 0 17", "h9h5");    //车８进４
	add("2bakab2/1r7/n1c3n1c/p3pN2p/2r3p2/3N5/P3P3P/R2CC4/9/2BAKABR1 b - - 0 15", "b8f8");    //车２平６
	add("3a1ab2/2N1k4/4b4/4p1C2/5rn1p/P8/4P3c/4B4/4A4/2BAK1R2 w - - 0 29", "g0g4");    //车三进四
	add("3a1ab2/2N1k4/4b4/4p1C2/5r2p/P3P4/7nc/4B4/4A4/2BAK1R2 w - - 0 30", "g0g4");    //车三进四
	add("3a1ab2/2Nk5/4b4/4p2C1/5r2p/P3P4/7nc/4B4/4A4/2BAK1R2 w - - 0 31", "h6h8");    //炮二进二
	add("4k1b2/9/5a2b/3Np2c1/P8/8p/7n1/4B4/1C2A4/2BA1K3 w - - 0 53", "d6c8");    //马六进七
	add("2bak1b2/4a4/2n3n1c/pNp1p3p/4r1p2/P8/2P5P/3CC4/4A4/1RB1KAB2 b - - 0 15", "e5d5");    //车５平４
	add("2bak1b2/4a4/2n3n1c/pNp1p3p/3r2p2/P8/2P5P/3C2C2/4A4/1RB1KAB2 b - - 0 16 ", "g7f5");    //马７进６
	//add("2bak1C2/4a4/2n6/pNp1p3p/3r1np2/P8/2P5c/7C1/4A4/1RB1KAB2 b - - 0 18", "i3h3");    //炮９平８//炮九平五
	add("2ba1kC2/4a4/2n6/pNp1p3p/3r1np2/P8/2P1c4/4B2C1/4A4/1RB1KA3 w - - 0 19", "c3c4");    //兵七进一
	add("2bak1C2/4a3c/2n6/pNp1p3p/4r2n1/PR4p2/2P5P/3C5/4A4/2BAK1B2 b - - 0 18", "c7a8");    //马３退１
	add("2bak1C2/4a3c/2n6/pNp1pn2p/4r4/PR4p2/2P5P/3C5/4A4/2BAK1B2 w - - 0 18", "g9i9");    //炮三平一
	add("Cn1ak4/3N3R1/9/4p3p/2p2C3/P1n1c1p2/8P/9/4K4/2Br1AB2 b - - 0 45", "c4e3");  //马３进５
	add("4ka3/2P1a4/4b4/3P5/2N5c/5n3/7p1/3A4C/6C2/3AK3c b - - 0 71", "f4e2");  //马６进５
	add("1rbaka2r/3c5/4b1n2/p3p1p1p/1cpn5/8R/P1P1P1P1P/2N1C1C1N/1R7/2BAKAB2 b - - 0 1", "i6i5");  //卒９进１
	add("1rbaka2r/3c5/4b1n2/p3p1p2/1cpn4p/7R1/P1P1P1P1P/2N1C1C1N/1R7/2BAKAB2 b - - 0 1", "i9h9");  //车９平８
	add("1rbaka1r1/3c5/4b1n2/p3p1p2/1cpn4p/7RP/P1P1P1P2/2N1C1C1N/1R7/2BAKAB2 b - - 0 1", "h9h4");  //车８进５
	add("1rbaka3/3c5/4b1n2/p3p4/2pn2p1P/7N1/PcP1P1P2/2N1C1C2/5R3/2BAKAB2 b - - 0 1", "f9e8");  //士６进５
	add("2baka3/3c5/4b3C/pr2p4/2pn4P/7p1/PcP1P4/2N1C4/5R3/2BAKAB2 b - - 0 1", "d5e3");  //马４进５
	add("2baka3/3c5/4b3C/pr2p4/2p5P/7p1/PcP1n4/2N1C4/5R3/2BAKAB2 w - - 0 1", "c2e3");  //马七进五
	add("2baka3/8c/4b2C1/pr2p4/2pn4P/7p1/PcP1P4/2N1C4/5R3/2BAKAB2 b - - 0 1", "i8c8");  //炮９平３
	
	add("4ka3/2P1a4/4b4/3P5/2N5c/5n3/7p1/3A4C/6C2/3AK3c b - - 0 71", "f4e2");  //马６进５
    add("2ba1a3/4kc3/3Nb1n2/p3p1p1p/9/2P3P2/2c2r2P/1C1RBA3/4A4/2C1K4 w - - 0 28", "b2b7");  //炮八进五
	add("1Cba1a3/4k4/4b1n2/pN2pcp1p/9/2P3P2/2c5r/3RBA3/4A4/2C1K4 w - - 0 31", "b6d5");  //马八退六
	add("2ba1a3/4k4/4b4/p3n1p1p/9/1NPp2P2/5C3/4BA3/3cA4/2C1K4 w - - 0 39", "f3e3");  //炮四平五
	add("2ba1a3/5k3/4b4/p1N1n3p/6p2/2Pp2P2/4C4/4BA3/3cA4/2C1K4 w - - 0 41", "e0d0");  //帅五平六
	add("2ba1a3/3N1k3/4b4/p7p/6p2/2Pp1nP2/4C4/4BA3/2c1A4/2CK5 w - - 0 43", "g4g5");  //兵三进一
	add("3a1a3/9/4bk3/p3N3p/6b2/2P1C4/3p5/4BAn2/2cKA4/6C2 w - - 0 48", "g0d0");  //炮三平六
	add("r1bakab2/9/6n1c/p3p1p1p/9/2P3P2/rC2P3P/NC4N2/3RA4/2c1KAB1R w - - 0 14", "b3b6");  //前炮进三
	add("2bakab2/r8/6n1c/pC2p1p1p/9/r1P2NP2/4P3P/1C6R/1R2A4/c3KAB2 w - - 0 18", "b2b4");  //后炮进二
	add("1Cbakab2/3rn4/8c/p3p1p1p/9/rCP2NP2/4P3P/2R6/1R2A4/c3KAB2 w - - 0 21", "b4b5");  //后炮进一
	add("1Cbakab2/4n4/8c/pC2p1p1p/9/r1Pr1NP2/4P3P/2R6/1R2A4/c3KAB2 w - - 0 22", "f4e6");  //马四进五
	add("2bak1b2/4a4/4c4/p3n1p1p/4C4/2P1P1P2/8P/3A5/9/C3KAB2 w - - 0 33", "a0c0");  //炮九平七
	add("3ak1b2/4a4/b3c4/p3n1p1p/4C4/2P1P1P2/8P/3A5/9/2C1KAB2 w - - 0 34", "c0c3");  //炮七进三
	add("3ak1b2/4a4/b7c/p3n1p1p/4C4/2P1P1P2/2C5P/3A5/9/4KAB2 w - - 0 35", "e5b5");  //炮五平八
	add("4k4/1C2aP3/4ba3/p1c6/2b5C/9/9/3A5/9/4KAB2 w - - 0 58", "b8b1");  //炮八退七
    add("1r1akabr1/9/c1n1b1n2/p1p1p3p/6pc1/2P1P4/P3N1P1P/C1N1C4/5R3/R1BAKAB2 b - - 0 9", "h9h8");  //车８进１
	add("1r1akab2/7r1/c1n1b1n2/p1p1p3p/7c1/2P1P1p2/P3N3P/C1N1C4/5R3/R1BAKAB2 w - - 0 10", "e3g4");  //马五进三
	add("1r1akab2/7r1/c1n1b1n2/p1p1p3p/6c2/2P1P1N2/P7P/C1N3C2/5R3/R1BAKAB2 b - - 0 12", "h8h4");  //车８进４
	add("1r1akab2/9/c1n1bRn2/p1p1p3p/6c2/2P1P1N2/P5r1P/C1N3C1B/R8/2BAKA3 b - - 0 15", "g7h5");  //马７进８
	add("1r1akab2/9/c1n1bR3/p1p1p3p/6cn1/2P1P1N2/P5r1P/C1N3C1B/R8/2BAKA3 w - - 0 15", "a1h1");  //车九平二
    add("3akabn1/9/n1c1b2c1/p2rp1p1p/9/2R6/P3P1P1P/N2C1CN2/4A4/2B1KAB2 b - - 0 12", "a7c6");  //马１进３  
	add("3akab2/9/2c1b2cn/p1nrpCp1p/9/7R1/P3P1P1P/N2C2N2/4A4/2B1KAB2 b - - 0 14", "e6e5");  //卒５进１
	add("3akab2/9/2c1b2cn/p1nr1Cp1p/4p4/7R1/P3P1P1P/N2C2N2/4A4/2B1KAB2 w - - 0 14", "f6i6");  //炮四平一
	add("2baka3/6r2/2n1b2c1/p1p1p2Np/1r7/1cP2n3/P3P3P/C3B1C1N/4A4/1RBAK1R2 b - - 0 14", "d9e8");  //士４进５
	//add("1rbaka3/9/2n1b4/p3pPC1p/2p2P3/9/Pcn4rP/2N4cN/4C4/1RBAKABR1 b - - 0 15", "h9e8");  //士６进５//车二进五
	add("1rbak4/4a4/4b4/p3P3p/2p2P3/9/P1n4rP/2N4cN/1c2C4/1RBAKABR1 w - - 0 17", "e1e2");  //炮五进一
	add("1rbak4/4a4/4b4/p3P3p/2p2P3/9/P1n4rP/2N1C2cN/1c7/1RBAKABR1 b - - 0 18", "c5c4");  //卒３进１
	add("1rbak4/4a4/4b4/p3P3p/5P3/2p6/P1n4rP/2N1C2cN/1c7/1RBAKABR1 w - - 0 18", "d0e1");  //仕六进五
	add("1rbak4/4a4/4b4/p3P3p/5P3/2p6/P1n4rP/2N1C2cN/1c2A4/1RB1KABR1 b - - 0 19", "i6i5");  //卒９进１
	add("2bak4/4a4/4b4/p3PP3/8p/2p6/Prn4rP/2N1C2cN/1c2A4/1RB1KABR1 w - - 0 20", "a3a4");  //兵九进一
	add("1rbak4/4a4/4b4/p3PP3/8p/2p6/P1n4rP/2N1C2cN/1c2A4/1RB1KABR1 b - - 0 20", "b9b3");  //车２进６
	add("2bak4/4a4/4b4/p3PP3/8p/P1p6/1r5rP/2N1B2cN/1c2A4/1R2KABR1 b - - 0 22", "b1b2");  //炮２退１
    add("r1bakabr1/9/nc4nc1/p1p1p3p/6p2/1CP6/P3P1P1P/2C1B1N2/9/RNBAKA2R b - - 14", "h7i7");  //炮８平９
	
	add("1c1ak1b2/8r/2Nab2c1/p1C6/6pnp/9/P3P1P1P/1n2C3N/2R6/3AKAB2 b - - 0 20", "b9b7");  //炮２进２
	//add("3a1kb2/2r6/1cN1b2c1/p3C4/6pnp/9/P3P1P1P/1n1AC3N/2R6/4KAB2 b - - 0 25", "b2c0");  //马２进３//仕四进五
	
	//add("3akab2/c7r/4b3n/C7p/2p6/7p1/P1P1R3P/4B2C1/4A4/4KAB2 w - - 0 17", "a6e6");  //炮九平五炮二平三
	add("3akab2/4c3r/4b3n/4C3p/2p6/7p1/P1P1R3P/4B2C1/4A4/4KAB2 w - - 0 18", "e6e8");  //炮五进二
	add("3akab2/4r4/4b3n/8p/2p6/7p1/P1P1R3P/4B2C1/4A4/4KAB2 w - - 0 19", "e2c0");  //相五退七
	add("3ak1b2/4a1r2/4b3n/8p/2p6/7p1/P1P1R3P/4C4/4A4/2B1KAB2 w - - 0 21", "e3d3");  //车五平六
	//add("3ak1b2/4a1r2/4b3n/8p/2p6/7p1/P1PR4P/4C4/4A4/2B1KAB2 b - - 0 22", "h7g6");  //马９进７//车七平八
	add("3ak1b2/4a1r2/4b4/6n1p/2p6/7p1/P1P3R1P/4C4/4A4/2B1KAB2 b - - 0 25", "h4h3");  //卒８进１
	add("3ak1b2/4a1r2/4b4/6n1p/2p6/9/P1P4RP/4C4/4A4/2B1KAB2 b - - 0 26", "g6f4");  //马７进６
	add("3ak1b2/4a1r2/4b4/4n3p/2p6/9/P1P1R3P/4C4/4A4/2B1KAB2 b - - 0 28", "e6f4");  //马５进６
	add("4ka3/2n1a4/9/p7R/2b6/2B3PN1/P5r1P/9/4A4/3AK4 w - - 0 34", "i6a6");  //车一平九;
	add("3k1a3/2n1a4/b8/R2r1N3/9/P8/8P/9/4A4/3AK4 w - - 0 42", "a6d6");  //车九平六;
	add("3k1a3/4a4/b8/3n1N3/P8/9/8P/9/4A4/3AK4 b - - 0 44", "d6c4");  //马４进３;
	add("2bak3r/4a4/2c1b2c1/p8/6pRp/2P1P4/P1r3P1P/4BC2N/4A4/2BAK3R w - - 0 15", "f2f5");  // 炮四进三
	//add("1rbakab1r/9/1c4n2/p3p1p1p/1np4c1/3R2P2/P1P1P3P/2N1CC3/9/2BAKABNR b - - 0 7", "i9h9");  // 车９平８//相三进五
	add("1r1akabr1/9/1c2b1n2/p3p1p1p/1np4c1/3R2P2/P1P1P3P/2N1CCN2/9/2BAKAB1R w - - 0 8", "i0h0");  // 车一平二
	add("3k5/2N1aC3/3N1a2b/9/9/p8/3c5/2cCB4/2p1AK3/3A5 w - - 0 97", "d7f6");  // 马六退四
	add("3k5/2N1aC3/5a2b/5N3/9/p8/4c4/2cCB4/2p1AK3/3A5 w - - 0 98", "f8g8");  // 炮四平三
	add("3ak1b2/4a4/2c1b1n2/4p1N1p/p1p6/3R2P1P/P3P1r2/n1N1BC3/4A4/3AK1B2 b - - 0 24", "c7b7");  // 炮３平２
	add("3a1k3/2N1an3/7c1/4pP2p/pR7/2p5P/P5r2/4BA3/9/3A1KB2 b - - 0 40", "g3g7");  // 车７退４
	add("3a1k1n1/2N1a4/2c6/4p1P1p/p1p6/8P/PR1n2r2/4BC3/4A4/3A1KB2 b - - 0 36", "c7h7");  // 炮３平８
	add("3ak1b2/4a4/3cb1n2/4p1N1p/p1p6/1R4P1P/P1n1P1r2/2N1BC3/4A4/3AK1B2 b - - 0 27", "d7d5");  // 炮４进２
	add("2bak1c2/4a4/5c2b/5P3/2R5p/6R2/9/3NB4/4A3r/2BAKN1r1 b - - 0 47", "f7h7");  // 炮６平８
	add("2bnk2r1/4a4/cR2b4/p1p1p1n1p/9/2P2rN2/P3P3P/4C4/4N4/2BAKAR2 w - - 0 22", "e1c2");  // 马五进七


	add("r1bakabr1/9/1cn3nc1/4p1p1p/p1p6/6P2/P1P1P3P/NC2C1N2/9/R1BAKABR1 w - - 0 5", "b2c2");  // 炮八平七 
	add("r3kab2/4a4/2n1b1n1c/p3p1p1p/2p4r1/2PRP1P2/P3N3c/1C2C1N2/R8/2BAKAB2 w - - 0 11", "g2i3");  // 马三进一 
	add("r3kab2/4a4/2n1b1n2/p5p1p/2p1p2r1/2PR2P2/P3N3c/1C2C4/R8/2BAKAB2 w - - 0 13", "c4c5");  //兵七进一 
	add("r3kab2/4a4/2n1b1n2/p5p1p/2r6/2N1R1P2/c8/1C2C4/8R/2BAKAB2 b - - 0 17", "c7b5");  //马３进２ 2B 
	add("3rkab2/4a4/4b4/p3n1p1p/1n2r4/R5P2/8R/1C2C4/4A4/2BAK1B2 w - - 0 21", "a4a6");  //车九进二
	add("3rkab2/4a4/4b4/R3n1p1p/4r4/3n2P2/8R/1C2C4/4A4/2BAK1B2 w - - 0 22", "e2e6");  //炮五进四
	add("3rkab2/4a4/4b4/R3C1p1p/4r4/3n2P2/8R/1C7/4A4/2BAK1B2 b - - 0 23", "e5e6");  //车５退１
	add("4k1b2/1c2a4/4bR3/3Cn4/2r5p/P3p1B2/9/1C4N2/4A4/3A1K3 w - - 0 44", "f7f3");  //车四退四 2B
	add("4k1b2/4a4/4b4/1c1Cn4/2r5p/P3p1B2/5R3/1C4N2/4A4/3A1K3 w - - 0 45", "f3b3");  //车四平八
	add("1R1ak1b2/9/4b4/3C5/6r1p/P1Bnp4/2c6/1C1A5/9/3AKN3 b - - 0 52", "c3c0");  //炮３进３ 4C
	add("2bak1b2/9/9/9/8p/P2p5/1R7/3A5/3KC4/5r3 b - - 0 61", "f0a0");  //车６平１
	add("2ba1kb2/9/9/9/8p/P2p5/4R4/3A5/3KC4/r8 w - - 0 62", "e3g3");  //车五平三
	add("2ba1kb2/9/9/9/8p/P2p5/6R2/3A5/3KC4/r8 b - - 0 63", "g9i7");  //象７进９
	add("2ba1k3/9/8b/9/8p/P2p5/8R/r2A5/3KC4/9 w - - 0 64", "e1e0");  //炮五退一
	add("2ba1k3/9/8b/9/8p/P2p5/8R/3A5/3K5/r3C4 w - - 0 65", "e0e1");  //炮五进一 2B
	add("2ba1k3/9/8b/9/8p/P2p5/8R/3A5/3KC4/r8 b - - 0 66", "a0a4");  //车１退４
	add("2ba1k3/9/8b/9/3R5/9/r2p5/3A5/3K5/4C4 b - - 0 69", "f9e9");  //将６平５
	add("2ba1k3/9/8b/9/9/9/r2p2R2/3A5/9/3KC4 w - - 0 76", "g3f3");  //车三平四
	add("3ak1b2/4a4/4b4/p3pP2p/1r3n3/5NR1c/P3P4/2N1B4/9/3AKAB2 b - - 0 24", "i6i5");  //卒９进１
	add("3ak1b2/4a4/4b4/p3P4/1n6p/5N2c/P3P4/2N1B4/9/3AKAB2 b - - 0 27", "i4i3");  //炮９进１
	add("3ak1b2/2c1a4/4b4/p3P4/1n2P3p/5N3/P8/2N1B4/9/3AKAB2 w - - 0 29", "f4d5");  //马四进六
	add("3ak1b2/c3a4/4b4/p3P4/1n1NP3p/9/P8/2N1B4/9/3AKAB2 w - - 0 30", "d5b4");  //马六退八 3B
	add("r2akab2/9/2n1b1n1c/p2Rp1p1p/2p4r1/4P1P2/PcP5P/1CN1C1N2/9/R1BAKAB2 w - - 0 8", "d6b6");  //车六平八
	add("r2akab2/9/2n1b1n1c/p2Rp1p1p/2p4r1/P3P1P2/2P5c/1CN1C1N2/9/R1BAKAB2 w - - 0 9", "a0b0");  //车九平八 
	add("r2akab2/9/2n1b1n1c/p2Rp1p1p/2p4r1/P3P1P2/2P5c/1CN1C1N2/9/1RBAKAB2 b - - 0 10", "a9b9");  //车１平２ 3C
	add("r3kab2/4a4/2n1b1n1c/p2Rp1p1p/2p4r1/P3P1P2/2P5c/1CN1C1N2/9/1RBAKAB2 w - - 0 11", "g2i3");  //马三进一


	add("1r1akab2/9/2n1b1n2/p2Rp1p1p/2p4r1/P3P1P2/2P5c/1CN1C4/9/1RBAKAB2 w - - 0 11", "d6c6");  //车六平七 
	add("2rakab2/9/2n1b1n2/p1R1p1p1p/2p4r1/P3P1P2/2P5c/1CN1C4/9/1RBAKAB2 w - - 0 12", "e4e5");  //兵五进一 3A
	add("2rakab2/4n4/4b1n2/R3p3p/2p1r1p2/P5P2/1RP6/2N1C4/9/2BAKAB2 w - - 0 16", "g4g5");  //兵三进一 2B
	add("2rakab2/1R7/2n1b1n2/2R1p3p/P1p3r2/9/2P1N4/4C4/9/2BAKA3 b - - 0 21", "d9e8");  //士４进５
	add("2rakab2/1R2n4/4b1n2/2R1p3p/P1p3r2/9/2P1N4/4C4/9/2BAKA3 w - - 0 21", "c6d6");  //车七平六
	add("2r1kab2/1R2a4/2n1b1n2/2R1p3p/P1p3r2/9/2P1N4/4C4/9/2BAKA3 w - - 0 23", "b8b4");  //车八退四 2B
	add("2r1kab2/4a4/2n1b4/2R5p/P1p6/5R3/4r4/4C4/4A4/2BAK4 w - - 0 30", "f4f6");  //车四进二 2B
	add("4kab2/4a4/4b1n2/4p3p/1P7/5NP2/9/9/4C4/c1BAKA3 w - - 0 31", "f4g6");  //马四进三
	//add("22r1kab2/4a4/4b4/C2c2p2/3NP3p/P5P2/1R1p5/3CB4/3nA4/1c1K1AB2 w - - 0 28", "a6g6");  //炮九平三 2A
	//add("2r1kab2/4a4/4b4/3c2C2/3NP3p/P5P2/1R1p5/3CB4/3nA4/1c1K1AB2 b - - 0 29", "deb2");  //炮九平三 2A
	add("1R1ckab2/4a4/4b4/4C4/3NP1P1p/P8/9/3pBA3/2r4c1/4K1B2 b - - 0 37", "i5i4");  //卒９进１
	add("4k1b2/3ca4/9/4c4/2bN1CP2/9/Pn4p2/2N5B/4K4/3A1AB2 w - - 0 40", "f5f4");  //炮四退一 2B
	add("2C3b2/3k5/9/9/1P7/4R3P/2p6/n4Ar2/9/5K3 w - - 0 86", "f0f1");  //帅四进一 2B
	add("1C7/4k4/9/9/2P6/8P/4p4/3R1A3/3n2r2/4K4 b - - 0 98", "g1g4");  //车７退３
	add("1C7/4k4/9/9/2P6/6r1P/4p4/1R3A3/4K4/1n7 b - - 0 100", "g4b4");  //车７平２
	add("1C7/4k4/9/9/2P6/1R6P/4p4/2n2A3/4K4/9 w - - 0 101", "e1d1");  //帅五平六 2B
	add("7C1/4k4/9/9/3P5/8P/9/1n1p5/9/3K1A3 w - - 0 110", "h9d9");  //炮二平六 2B
	add("6C2/4k4/9/9/3P5/8P/9/1n1p5/9/3K1A3 w - - 0 112", "g9d9");  //炮三平六
	//add("4kab2/4a4/c8/4p4/p2C2n2/2PN2B2/P3p3P/9/9/2BAKA3 w - - 0 33", "c4c5");  //兵七进一



	 //仙人指路;
	add("1nbaka2r/5n3/c3b2c1/p3p1p1p/2p6/6P2/P1P1P3P/N1C1B1NC1/9/2BAKA2R b - - 0 8", "i9g9");  //车９平７
	add("1nbaka3/9/c2nb2c1/p3pR2p/2p3r2/9/P1P1P3P/N1C1B1NC1/4A4/2BAK4 b - - 0 12", "a6a5");  //卒１进１
	add("1nbaka3/9/c2nb1c2/R6Cp/p1p1p1r2/5N3/P1P1P3P/N1C1B4/4A4/2BAK4 b - - 0 15", "g5f5");  //车７平６
	add("1nbaka1C1/9/c2nb1c2/R7p/p1p1pr3/5N3/P1P1P3P/N1C1B4/4A4/2BAK4 b - - 0 16", "e7g9");  //象５退７
	add("1nbakabC1/9/c2n2c2/R7p/p1p1pr3/9/P1P1P3P/N1C1B1N2/4A4/2BAK4 b - - 0 17", "f5h5");  //车６平８
	add("1nb1kab1C/4a4/c2n2c2/R7p/p1p1p2r1/9/P1P1P3P/2C1B1N2/4A4/1NBAK4 b - - 0 19", "b9c7");  //马２进３
	add("3k1a1nC/4a4/4b4/8p/p2P5/4p4/8P/4BA2c/4K1C2/2BA5 b - - 0 36", "i2g2");  //炮９平７
	add("3k1a1nC/4a4/4b4/8p/p2P5/4p4/8P/4BAc2/4K1C2/2BA5 w - - 0 36", "g1i1");  //炮三平一
	add("3k1a1nC/4a4/4b4/8p/p2P5/4p4/8P/4BAc2/4K3C/2BA5 b - - 0 37", "d9d8");  //将４进１
	add("5a1n1/3ka3C/4b4/8p/p2P5/4p4/8P/4BAc2/4K3C/2BA5 b - - 0 38", "d8d9");  //将４退１;
    add("1rbakab1r/9/2n1c1nc1/p1p1p1p1p/9/6P2/P1P1P3P/1CN3NC1/9/1RBAKAB1R w - - 0 4", "g2f4");  //马三进四
	add("1rbakab1r/n8/4c1nc1/p3p1p1p/1Cp6/6P2/P1P1P3P/2N3NC1/8R/1RBAKAB2 b - - 0 7", "b9b6");  //车２进３ ;
	add("1rbakab1r/9/2n1c1nc1/pC2p1p1p/2p6/6P2/P1P1P3P/2N3NC1/8R/1RBAKAB2 b - - 0 8", "i9i8");  //车９进１

	//进马局;
	
	add("2baka3/6c2/2n1b1nr1/p3pR3/2p6/5N3/P1P1P3P/C3B4/9/1N1AKAB2 b - - 0 17", "g7h5");  //马７进８
	add("2baka3/1c7/2n1b1nr1/p3pR3/2p6/5N3/P1P1P3P/C3B4/9/1N1AKAB2 w - - 0 17", "b0d1");  //马八进六
	add("2baka3/1c7/2n1b1nr1/p3pR3/2p6/5N3/P1P1P3P/C3B4/3N5/3AKAB2 b - - 0 18", "g7h5");  //马７进８
	add("1rbakab2/1c7/2n3n1c/p1P1p3p/6p2/5R3/P3P3P/C1N1B1r1C/9/1R1AKAB2 b - - 0 12", "g5g4");  // 卒７进１
	add("1rbakab2/1c2n4/6n1c/p1P1p3p/9/2R3p2/P3P3P/C1N1B1r1C/9/1R1AKAB2 w - - 0 13", "c4d4");  // 车七平六
	add("1rbakab2/1c2n2c1/6n2/p1P1p3p/9/3R2p2/P3P3P/C1N1B1r1C/4A4/1R2KAB2 w - - 0 15", "b0b7");  // 车八进七
	add("1rbakab2/1c2n2c1/1R4n2/p1P1p3p/9/3R2p2/P3P1r1P/C1N1B3C/4A4/4KAB2 w - - 0 16", "e0d0");  // 帅五平六
	add("1rba1k3/4a4/n3b4/p3C4/n8/2P3p2/P3P3P/1C6N/4A2R1/2c1KAB2 w - - 0 20", "b2f2");  // 炮八平四
	add("1rba1k3/4a4/n3b4/p3C4/n8/2P3p2/P3P3P/5C2N/4A2R1/2c1KAB2 b - - 0 21", "c0a0");  // 炮３平１
	add("1rba1k3/4a4/n3b4/p3C4/n8/2P3p2/P3P3P/5C2N/4A2R1/c3KAB2 w - - 0 21", "h1h9");  // 车二进八
	add("1rba1k1R1/4a4/n3b4/p3C4/n8/2P3p2/P3P3P/5C2N/4A4/c3KAB2 b - - 0 22", "f9f8");  // 将６进１
	add("1rba1k3/4a2R1/n3b4/p3C4/n8/2P3p2/P3P3P/5C2N/4A4/c3KAB2 w - - 0 23", "h8h9");  // 车二进一
	add("2ba3R1/4ak3/n3b4/p4C3/5N3/2n2p3/P3P3P/5C3/1r7/c2AKAB2 w - - 0 30", "d0e1");  // 仕六进五
    add("r1bakabr1/9/1cn3nc1/p3p2Rp/2p3p2/9/P1P1P1P1P/NC4N1C/R8/2BAKAB2 b - - 0 6", "c9e7");  // 象３进５
	add("4kab2/4a4/7cr/p6R1/1R2pnr1p/9/P3P1p1P/2N6/4N4/2BAKAB2 b - - 0 19", "h7c7");  //  炮８平３
	add("4kab2/4a4/2n4cr/p6R1/1C2pnr1p/9/P3P1p1P/2N6/1R2N4/2BAKAB2 b - - 0 18", "g3g2");  //  卒７进１
	add("4kab2/4a4/2n4cr/p6R1/1C2pnr1p/9/P3P3P/2N3p2/1R2N4/2BAKAB2 w - - 0 18", "c2d4");  //  马七进六
	add("4kab2/4a4/7cr/p6R1/1n2pnr1p/3N5/P3P3P/6p2/1R2N4/2BAKAB2 w - - 0 19", "b0b5");  //  车八进四
	add("4kab2/4a4/7cr/p6R1/1R2p1r1p/3N5/P3n3P/6p2/4N4/2BAKAB2 w - - 0 20", "e1f3");  //  马五进四
	add("3cka3/4a4/2r1b4/p1N2R3/1R2N3p/4r4/P3n3P/4B1p2/9/2BAKA3 w - - 0 26", "d0e1");  //  仕六进五
	add("3cka3/4a4/2r1b1R2/p1N6/1R2N3p/4r4/P3n3P/4B4/4A4/2B1Kp3 w - - 0 29", "e1f0");  //  仕五退四
	add("4ka3/4a4/2r1b1R2/p1Nc5/1R2N3p/P3r4/4n3P/4B4/4Ap3/2B1KA3 b - - 0 30", "d6h6");  //  炮４平８
	add("2ba1kr2/4a4/4c4/3PCN2p/p1b6/3R5/P7P/4B4/4A4/1cpAK4 b - - 0 29", "g9h9");  //  车７平８
	add("2ba1k3/9/5a3/3P1N2p/p1b6/4CR3/P5r1P/3Ac4/9/1cpAK4 b - - 0 33", "b0d0");  //  炮２平４
	add("2ba1k3/9/5a3/3P1N2p/p1b6/4CR3/P5r1P/3Ac4/9/2pcK4 w - - 0 33", "f4h4");  // 车四平二
	add("2ba1k3/9/5a3/3P1N2p/p1b6/4C2R1/P5r1P/3Ac4/9/2pcK4 b - - 0 34", "d0d6");  // 炮４退６
	add("9/3k5/4bR3/4cN3/p1b5p/9/P3r3P/3AC4/4K4/2p6 b - - 0 43", "c0d0");  // 卒３平４



	//下面飞象局;
	
	
	
	
	//过宫炮;
	
	add("r1bakabr1/9/n1c3nc1/p1p1p3p/6p2/P1P6/4P1P1P/1CNC2N2/9/R1BAKAB1R w - - 0 5 ", "c2b4");  //马七进八
	add("1rbakabr1/9/n5n2/N3p3p/PCp3p2/2c4c1/4P1P1P/3C2N2/9/1RBAKAB1R b - - 0 10 ", "c9e7");  //象３进５
	add("1r1akabr1/9/n3b1n2/N3p3p/PCp3p2/2c4c1/4P1P1P/3C2N2/9/1RBAKAB1R w - - 0 10", "c0e2");  //相七进五
	add("1r1akabr1/9/n3b1n2/N3p3p/PCp3p2/7c1/2c1P1P1P/3CB1N2/9/1R1AKAB1R w - - 0 11", "d2b2");  //炮六平八
	add("1r1akabr1/9/n3b1n2/N3p3p/PCp3p2/7c1/2c1P1P1P/1C2B1N2/9/1R1AKAB1R b - - 0 12", "h4b4");  //炮８平２
	add("1r1akabr1/9/n3b1n2/N3p3p/PC4p2/1cp6/4P1c1P/2C1B1N2/8R/1R1AKAB2 w - - 0 14", "a6c7");  //马九进七
	add("1rbakabr1/9/n5n2/N1p1p3p/1Cc3p2/P6c1/4P1P1P/3C2N2/8R/1RBAKAB2 b - - 0 10", "b9b7");  //车２进２






	//内置飞刀库编码//砍佳佳
	add("1rb1kab2/4a4/2n1c3n/p1p1p1p1p/9/2P1P2r1/Pc4P1P/C1N1C1N2/5R3/1RBAKAB2 w - - 0 9", "f1f5");  //车四进四
	add("1rb1kab2/4a4/2n1c3n/p1p1p1p1p/5R3/2P1P2r1/Pc4P1P/C1N1C1N2/9/1RBAKAB2 b - - 0 10", "h4h3");  //车８进１
	add("2b1kab2/4a4/1rn1c3n/p3p1p1p/9/4P4/P1R3PrP/C1N1C1N2/1c7/1RBAKAB2 w - - 0 13", "d0e1");  //仕六进五
	add("2b1kab2/4a4/1rn3c1n/p1R1p1p1p/9/3NP4/P3r3P/C3C1N2/1c2A4/1RB1KAB2 w - - 0 16", "a2c2");  //炮九平七
	add("1nbak3r/4a4/c3b1n2/p3p2cp/2pP2p2/8P/P1P3P2/2N1C1NC1/9/2BAKAB1R b - - 0 11", "b9c7");  //马２进３
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	//内置残局库编码

	//内置残局库编码

	add("3k5/3cac3/3a1r3/9/9/4R1N1P/9/7C1/9/4K4 b - - 0 88", "f8h8");//炮６平８
	add("3k5/3ca2c1/3ar4/9/4N4/4R3P/9/4C4/9/4K4 b - - 0 90", "d8c8");//炮４平３
	add("3k5/2c1a2c1/3ar4/9/4N4/4R3P/9/4C4/9/4K4 w - - 0 90", "e4e3");  //车五退一
	add("4k4/3ca4/P3ba2b/4N4/9/4p1P2/9/4B4/3K5/5A3 w - - 0 84", "a7b7");  //兵九平八
	add("3nka3/4a4/4b1Nc1/1Rp3r2/c3C1bNp/2P6/4P4/9/9/2BAKAB2 w - - 0 25", "e3e4");  //兵五进一
	add("3nka3/4a4/6Ncb/1Rp3r2/2b1P2Np/9/9/9/9/2BAKAB2 w - - 0 28", "c0e2");  //相七进五
	add("R2cka3/4a4/4b1Nc1/2p1Nr3/6b1p/2P6/4P4/9/4A4/2B1KAB2 w - - 0 28", "e6c7");  //马五进七
	add("R2cka3/4a4/2N1b1Nc1/2p2r3/6b1p/2P6/4P4/9/4A4/2B1KAB2 b - - 0 29", "f6f7");  //车６退１
	add("5kC2/4P4/9/9/2b6/9/9/9/5p3/3AK4 w - - 0 1", "e8e9");  //兵五进一
	add("r2aka3/4r1n2/b3c1C2/p1p1C3p/9/9/P1P5P/N3B4/9/3AKAB2 w - - 0 1", "c3c4");  //兵七进一
	add("4kab2/3Pn4/9/9/6b2/9/9/9/4K4/4CA3 w - - 0 1", "e1e2");  //帅五进一
	add("4kab2/3Pn4/8b/9/9/9/9/4K4/9/4CA3 w - - 0 2", "e0e1");  //炮五进一
	add("4k4/3Pa4/4r4/7R1/6b2/9/9/3AB4/4K4/2BA5 w - - 0 1", "e1e0");   // 帅五退一
	add("2b2k3/9/4b4/R8/9/9/1pp6/9/9/3K5 w - - 0 1", "a6f6");   // 车九平四
	add("5k3/4P4/9/9/8n/8N/9/B8/5p3/p3K4 w - - 0 1", "i4g5");   // 马一进三
	add("5k3/4P4/9/6n2/6N2/9/9/B8/5p3/p3K4 w - - 0 2", "g5e6");   // 马三进五
	add("5k3/4P4/4n4/4N4/9/9/9/B8/5p3/p3K4 w - - 0 3", "e6c7");   // 马五进七
	add("4ka3/4an3/9/9/4R4/9/9/9/9/4K4 w - - 0 1", "e6c7");   // 马五进七
	add("2bak4/4anC2/4b4/4P1c1p/N2R2r2/3pn2R1/8P/C8/3r5/1cBAKAB2 w - - 0 1", "d5d9");   // 车六进四
	add("3a1k3/6N2/5a3/4p1p1n/2b3b1P/2B6/4P4/3p1N3/crR1KC3/3r5 w - - 0 5", "f2h3");   // 马四进二
	add("3a1k3/6N2/5a3/6p1n/2b3b1P/2B2N3/4P4/3p5/crR1KC3/3r5 w - - 0 9", "f4d5");   // 马四进六
	add("3a1k3/4a1N2/9/6p1n/2bN2b1P/2B6/4P4/3p5/crR1KC3/3r5 w - - 0 10", "d5f6");   // 马六进四

	add("2Pc5/4r1r2/bnnak1C1b/4p2PN/3PP1P2/R2N2p1c/9/4C4/3p1p3/4K1p2 w - - 0 1", "d4f5");   // 马六进四
	add("2Pc5/4rkr2/bnnaN1C1b/4pP1PN/3PP4/R3pc3/9/5C3/3p1p3/4K1p2 w - - 0 6", "f6g6");   // 兵四平三
	add("1Nbk1n1P1/9/7r1/5R1C1/6p1c/6B2/9/2p1KA3/3pA4/9 w - - 0 1", "f6d6");   // 车四平六

	add("1Nbk1n1P1/9/7r1/5R1C1/6p1c/6B2/9/2p1KA3/3pA4/9 w - - 0 1", "e1f2");   // 仕五进四
	add("C3kab2/4a3R/4b4/7R1/p5pn1/9/5rP2/4B4/4A4/3CKA1rc w - - 0 1", "d0d9");   // 炮六进九
	add("C3kab2/5r2R/3Rb4/9/p5pn1/9/6P2/4B4/4A4/3K1A1rc w - - 0 5", "d7d9");   // 车六进二
	add("C3kab2/3R1r3/4b4/9/p5pn1/9/6P2/4B4/3KA4/8c w - - 0 9", "d8f8");   // 车六平四
	add("C3kab2/5R3/4b4/9/p5p2/9/6n2/4B4/3KA4/8c w - - 0 10", "a9a6");   // 炮九退三
	add("r2akabr1/9/2n1b4/p1p1pR2p/5npc1/2P6/P3P1c1P/C1N1C1N1B/9/R1BAKA3 w - - 0 2", "a0a1");   // 车九进一
	add("4kabr1/4a4/2n1b4/p1p1pR2p/1r3npc1/2P4R1/P3P1c1P/C1N1C1N1B/9/2BAKA3 w - - 0 5", "a2a1");   // 炮九退一
	add("1R1ak1b2/4a4/R3b4/p3p3p/9/2P1P4/P4rn1P/2N1BC3/3CA4/3AKN1rc b - - 0 1", "g3i2");   // 马７进９
	add("1R1ak1b2/4a4/R3b4/p3p3p/4P4/2P6/P4r2P/2N1BC2n/3CA4/3AKN1rc b - - 0 2", "f3g3");   // 车６平７
	add("3akab2/9/4b1n2/p1RPp3p/1R7/6P2/6r1P/4B4/4Ar3/2B1KAC2 w - - 0 1", "d6d7");   // 兵六进一
	add("3akab2/9/3Pb1n2/p1R1p3p/1R7/6P2/6r1P/4B4/4Ar3/2B1KAC2 b - - 0 2", "f1f5");   // 车６退４
	add("2ba3R1/5k3/4ba3/p7p/3rN4/4P2N1/2c5P/4B4/2p1A4/c3KAB2 b - - 0 1", "d5e5");   // 车４平５
	add("2ba3R1/5k3/4ba3/p7p/4r4/4P2N1/2c5P/4B4/2p1A4/c3KAB2 w - - 0 1", "h9h8");   // 车二退一
	add("2baka3/r8/4b4/p1pR4p/5N1r1/2P3p2/c3P1n1P/3CB1Nc1/9/1R1AKAB2 w - - 0 1", "f5e7");   // 马四进五
	add("2bckab2/4a4/5n3/CR3N2p/5r3/P3P1B2/9/2n1B4/4A4/3AK1C2 w - - 0 1", "g0g9");   //炮三进九
	add("2bakab2/9/2n1c1R1c/3r4p/4N4/r8/6P1P/6C1C/4A4/1RBAK1B2 w - - 0 1", "g7e7");   //车三平五
	add("1r1akar2/9/6c1b/1cp3N1p/6n2/2P1P1R2/R7P/4B3C/4A4/2CAK1B2 w - - 0 1", "g6e5");   //马三退五
	add("1r1akar2/9/6c1b/1cp5p/4N1n2/2P1P1R2/R7P/4B3C/4A4/2CAK1B2 b - - 0 2", "b9b7");   //车２进２
	add("3akar2/9/1r4c1b/1cp5p/4N1n2/2P1P1R2/R7P/4B3C/4A4/2CAK1B2 w - - 0 2", "g4f4");   //车三平四
	add("3akar2/9/1r4c1b/2p5p/4N1n2/2P1PR3/R7P/4B3C/4A4/1cCAK1B2 w - - 0 3", "e2g4");   //相五进三
	add("3k1abr1/1R2a1N2/4b1n2/p3p1p1p/2p6/P5P2/4P2cP/3C5/3rA4/2B1KABR1 w - - 0 1", "b8b6");   //车八退二

	add("2ba5/4k4/4ba3/1N5RC/5rp1P/2P6/9/2c1B4/3rA4/3AK1B2 w - - 0 1", "h6h8");   //车二进二
	add("3k1a3/4a4/4b4/4P4/6b2/9/2crC2R1/8C/4A4/2B1KAB2 w - - 0 1", "i2d2");   //炮一平六
	add("3k1a3/4a4/4b4/4P4/6b2/9/2c4R1/3rC4/4A4/2B1KAB2 b - - 0 3", "d2d5");   //车４退３
	add("3k1a3/4a4/4b4/4P4/6b2/9/2c4R1/3rC4/4A4/2B1KAB2 b - - 0 3", "d2d5");   //车４退３
	add("33k2b2/4a4/3a5/9/3r5/9/4R4/3C5/4A4/2B1KAB2 w - - 0 7", "e3g3");   //车五平三
	add("4k4/4a4/3ab1R2/9/3r5/9/9/3C5/4A4/2B1KAB2 w - - 0 9", "g7e7");   //车三平五
	add("4k4/4a4/3aR4/9/2r6/9/9/3C5/4A4/2B1KAB2 w - - 0 10", "e7g7");   //车五平三
	add("r3kab2/4a4/n1c1bc3/pC2CN2p/2pR1n3/9/P1P1P3P/B1r6/4A4/2NRKA3 w - - 0 1", "d5f5");   //前车平四
	add("3akabr1/9/4c4/p1pRn2Cp/4rcp2/2P1p4/P3P1P1P/3CB1N2/9/3AKABR1 w - - 0 1", "d2d1");   // 炮六退一
	add("C3kab2/4a4/2Rnb3n/8p/6p2/1p2c3r/P5P2/4B3N/3CA4/2BAK4 w - - 0 1", "d1d6");   // 炮六进五
	add("C3kab2/4a4/2Rnb3n/3C4p/6p2/1p2c4/P5P2/4B3r/4A4/2BAK4 w - - 0 2", "e0f0");   // 帅五平四
	add("C3kab2/4a4/2Rnb3n/3C4p/6p2/1p2c4/P5P2/4B4/4A4/2BA1K2r w - - 0 3", "f0f1");   // 帅四进一
	add("C3kab2/4a4/2Rnb3n/3C4p/6p2/1p2c4/P5P2/4B4/4AK3/2BA4r b - - 0 4", "i0i1");   // 车９退１
	add("C3kab2/4a4/2Rnb3n/3C4p/6p2/1p2c4/P5P2/4B4/4A3r/2BA1K3 b - - 0 5", "e8f7");   // 士５进６
	add("C3kab2/9/2Rnba2n/3C4p/6p2/1p2c4/P5P2/4B4/4A3r/2BA1K3 w - - 0 5", "d6b6");   // 炮六平八
	add("C3kab2/9/2Rnba2n/1C6p/6p2/1p2c4/P5P2/4B4/4A3r/2BA1K3 b - - 0 6", "i1i9");   // 车９进１
	add("3k5/9/3aCa3/p3C4/8p/4R4/8P/3A1p3/9/3K1Ar1c w - - 0 58", "e6e5");   // 后炮退一
	add("3k5/9/3aCa3/9/p3C3p/4R4/8P/5p3/3KA1r1c/5A3 w - - 0 61", "e4e3");   // 车五退一
	add("3k5/9/3aCa3/9/p3C4/4R3p/9/5p3/3KA1r1c/5A3 w - - 0 62", "d1d0");    // 帅六退一
	
	add("3k5/9/3aCa3/9/p2C5/4R3p/9/5p3/3KA1r1c/5A3 b - - 0 65", "d9e9");    // 将４平５
    add("3k5/4a4/4Ca3/9/p2C5/4R3p/9/5p3/3KA1r1c/5A3 w - - 0 79", "d1d2");    // 帅六进一
	add("3k5/9/3aCa3/p8/4C3p/4R4/8P/3A1p3/9/3K1Ar1c b - - 0 59", "a6a5");    // 卒１进１
	add("3k5/9/3aCa3/9/p3C3p/4R4/8P/3A1p3/3K5/5Ar1c b - - 0 60", "g0g1");    // 车７退１
	add("3k5/9/3aCa3/9/p3C3p/4R4/8P/5p3/3KA1r1c/5A3 w - - 0 61", "i3i4");   // 兵一进一
	add("3k5/9/3aCa3/9/p3C4/4R3p/9/5p3/3KA1r2/5A2c b - - 0 62", "i0i1");   // 炮９退１
	add("3k5/9/3aCa3/9/p3C3p/4R3P/9/5p3/3KA1r1c/5A3 b - - 0 2", "i5i4");   // 卒９进１
	add("3k5/9/3aCa3/9/p3C3p/4R3P/9/5p3/3KA1r1c/5A3 b - - 0 2", "i5i4");   // 卒９进１
	add("4C4/3k5/3a1a3/4r4/9/9/2R6/3Ap3p/3KA4/9 w - - 0 42", "e9e2");   // 炮五退七
	add("2bak1r2/4a4/1c3c3/4P1CRp/p1b6/3R2N2/P4r2P/4B4/4A4/2pAK4 b - - 0 25", "b7b0");   // 炮２进７
	add("2bak1r2/4a4/b4c3/4P1CRp/p8/2R3N2/P4r2P/4B4/4A4/1c1K5 w - - 0 27", "a3a4");   // 兵九进一
	add("2bak1r2/4a4/b4c3/4P1CRp/9/R5N2/5r2P/4B4/4A4/1c1K5 b - - 0 29", "i6i5");   //卒９进１
	add("2bak1r2/4a4/b4c3/4P1CR1/8p/R5N2/5r2P/4B4/4A4/1c1K5 w - - 0 29", "d0e0");   //帅六平五
	add("2bak1r2/4a4/b4c3/4P1CR1/8p/R5N2/2r5P/4BA3/9/1c2K4 b - - 0 31", "c3c0");   //车３进３
	add("2bak1r2/4a4/b4c3/4P1CR1/8p/R5N2/8P/4BA3/4K4/1cr6 b - - 0 32", "c0c1");   //车３退１
	add("2bak1r2/4a4/b4c3/4P1CR1/8p/R5N2/8P/4BA3/2r6/1c2K4 b - - 0 33", "c1c2");   //车３退１
	add("2bak1r2/4a4/b4c3/4P1CR1/8p/R5N2/8P/2r1BA3/4K4/1c7 b - - 0 34", "c2b2");   //车３平２
	add("2bak1r2/4a4/b4c3/4P1CR1/8p/3R2N2/8P/1r2BA3/4K4/1c7 b - - 0 35", "f7c7");   //炮６平３

	add("2bak4/4a4/3cb4/2NRpr2p/6R2/7r1/2P1n3P/4B1n1C/4A4/2C1KAB2 b - - 0 30", "f6f0");   //车６进６
	add("2bak4/4a4/3c5/2N1R3p/3n2b2/7r1/2P5P/4B1n1C/4A4/4KCB2 w - - 0 32", "e6g6");   //车五平三
	add("3ak1r2/4a4/5c3/4P1CRp/p5R2/4crN2/P7P/4B4/4A4/2pAK4 b - - 0 28", "f7c7");   //炮６平３
	add("3ak1r2/4a4/5c3/4P1CRp/p5R2/4crN2/P7P/4B4/4A4/2pAK4 b - - 0 28", "f7c7");   //炮６平３
	add("3ak4/9/2car4/6P1p/R8/4c1N2/P7P/4B4/4A4/2pAK4 b - - 0 33", "e4e6");   //炮５退２
	add("3ak4/9/2car4/4c1P1p/7R1/6N2/P7P/4B4/4A4/2pAK4 b - - 0 34", "c7c6");   //炮３进１
	add("5R3/3ck4/3a5/6P1p/9/6N2/P7P/9/4r4/3c1K3 b - - 0 44", "d8b8");   //后炮平２
	add("9/3k5/1R1a5/5NP1p/9/9/P7P/9/1c2r4/3c1K3 b - - 0 47", "e1d1");   //车５平４
	add("3k5/4a4/2R6/5NP1p/9/9/P7P/9/2cr5/3c1K3 w - - 0 50", "c7c9");   //车七进二
	add("2R6/3ka4/9/5NP1p/9/9/P7P/9/2cr5/3c1K3 w - - 0 51", "c9c5");   //车七退四
	add("9/3ka4/9/5NP1p/2R6/9/P7P/9/2cr5/3c1K3 b - - 0 52", "c1a1");   //炮３平１
	add("9/3k5/3a5/5NP1p/1R7/9/P2r4P/9/c8/3cK4 b - - 0 55", "a1c1");   //炮１平３
	add("9/3k5/3a5/5NP1p/1R7/P8/3r4P/9/2c6/3cK4 b - - 0 56", "d0d2");   //炮４退２
	add("3k5/9/1R1a2P2/3r1N2p/9/P8/8P/3c5/2c6/4K4 b - - 0 59", "c1d1");   //炮３平４
	add("9/3k2N2/3c2r2/8p/1P7/9/8P/2R6/c8/3K5 b - - 0 70", "g7g0");   //车７进７
	add("2R6/3k2N2/3c2r2/8p/1P7/9/8P/9/3cK4/9 b - - 0 78", "g7g1");   //车７进６
	add("2R6/3k2N2/3c5/8p/1P7/9/8P/4K4/3c2r2/9 b - - 0 79", "g1g7");   //车７退６
	add("3c5/3N1k3/b2ab4/5N3/9/6B2/9/9/2nK5/5A3 w - - 0 164", "d1e1");   //帅六平五
	add("4ka3/1rNRa4/4b1n2/p5p1p/6b2/3p4P/P6n1/3A5/3C1K3/2BA2B2 w - - 0 31", "d1d4");   //炮六进三
	add("4ka3/1rNRa4/4b4/p3n1p1p/6b2/4C3P/P4n3/3A5/9/2BA1KB2 w - - 0 34", "e4e3");   //炮五退一
	add("4ka3/1rNRa4/4b1n2/p3p1p1p/6b2/8P/P6n1/3C5/4AK3/2BA2B2 b - - 0 29", "e6e5");   //卒５进１
	add("4ka3/1rNRa4/4b1n2/p5p1p/6b2/4p3P/P6n1/3A5/3C1K3/2BA2B2 b - - 0 31", "e4d4");   //卒５平４
	add("4ka3/1rNRa4/4b1n2/p3p1p1p/6b2/8P/P8/4C4/4AKn2/2BA2B2 w - - 0 27", "e2h2");   //炮五平二
	add("4ka3/1rNRa4/4b1n2/p3p1p1p/6b2/8P/P6n1/7C1/4AK3/2BA2B2 w - - 0 28", "h2d2");   //炮二平六
	add("4ka3/1rNRa4/4b1n2/p5p1p/4p1b2/8P/P6n1/3C5/4AK3/2BA2B2 w - - 0 29", "d2d1");   //炮六退一
	add("4ka3/1rNRa4/4b1n2/p5p1p/6b2/4p3P/P6n1/9/3CAK3/2BA2B2 w - - 0 30", "e1d2");   //仕五进六

	add("4ka3/1rNRa4/4b4/p3n1p1p/6b2/3C4P/P6n1/3A5/5K3/2BA2B2 w - - 0 32", "d4e4");   //炮六平五
	add("1rb1ka3/4a4/1cn1b2c1/p1p2r3/4pNCnp/2P6/P3P1P1P/4C3N/1R3R3/2BAKAB2 b - - 0 12", "h5g7");   //马８退７

	add("1rb1ka3/4a4/2n1b1R2/p1p6/1c2pr2p/2P6/P3P1P1P/6C1N/1R7/2BAKAB2 w - - 0 16", "b1b2");   //车八进一
	add("2b1ka3/4a4/4b4/p8/3n3rp/2R1P1P2/P7c/1C2B3N/4A4/3AK1B2 b - - 0 26", "e8d8");   //士５退４
	add("2bak4/4a4/4b4/C4n3/7rp/3RP1P1c/P8/4B3N/4A4/3AK1B2 w - - 0 29", "a6e6");   //炮九平五
	add("2bak4/4a4/4b4/4C4/3R2nrp/8c/P8/4B3N/4A4/3AK1B2 b - - 0 32", "i4i3");   //炮９进１
	add("2bakab2/9/2n5n/p1p1p1p2/8p/2P1cNP2/P7P/4C4/4A4/1NBAK1B2 w - - 0 13", "b0c2");   //马八进七
	add("2baka3/9/2n1b3n/p1p1p1p2/8p/2P1cNP2/P7P/2N1C4/4A4/2BAK1B2 w - - 0 14", "e0f0");   //帅五平四
	add("2baka3/9/2n1b3n/p1p1p1p2/8p/2P1cNP2/P7P/2N1C4/4A4/2BA1KB2 b - - 0 15", "i7h5");   //马９进８
	add("2baka3/9/2n1b4/p1p1p4/8N/2P1c1P2/P7n/2N1C4/4A4/2BA1KB2 b - - 0 17", "i3h1");   //马９进８
	add("2baka3/9/2n1b4/p1p1p4/8N/2P1c1P2/P5n2/2N1C4/4A4/2BA1KB2 b - - 0 19", "g3e2");   //马７进５
	add("2baka3/9/2n1b4/p1p1p4/8N/2P1c1P2/P8/2N1B4/4A4/2BA1K3 b - - 0 20", "c6c5");   //卒３进１
	add("2bak4/4a4/2n1b4/p3p4/5P3/5cN2/P8/2N1B4/4A4/2BA1K3 w - - 0 24", "c2b4");   //马七进八
	add("2ba1k3/4a4/4b4/p3p4/1n1N1P3/P2c2N2/9/4B4/4A4/2BAK4 b - - 0 28", "d4e4");   //炮４平５
	add("2ba1k3/4a4/4b4/p3p4/1n1N1P3/P3c1N2/9/4B4/4A4/2BAK4 w - - 0 28", "f5f6");   //兵四进一
	add("2ba1k3/4a4/9/p3P1N2/2bN5/c2n5/9/4B4/4A4/2BAK4 b - - 0 32", "a6a5");   //卒１进１
	add("2ba1k3/4a1N2/6N2/1c1P5/p1b6/3n5/9/4B4/4A4/2BAK4 b - - 0 38", "a5a4");   //卒１进１
	add("2bakabr1/9/c1n3nc1/p3p3p/2r3p2/7R1/P3P1P1P/2N3N1C/R3C4/2BAKAB2 b - - 0 10", "c7d5");   //马３进４









 }


