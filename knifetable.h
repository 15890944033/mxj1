
#ifndef KNIFETABLE_H_INCLUDED
#define KNIFETABLE_H_INCLUDED

//#define		USING_UNORDEREDMAP

#include <string>

#ifdef USING_UNORDEREDMAP
#include <unordered_map>
#else
#include <map>
#endif


#include "misc.h"
#include "types.h"

#ifdef USING_UNORDEREDMAP

typedef  std::unordered_map<Key, Move>		KeyMove;
#else
typedef  std::map<Key, Move>		KeyMove;

#endif

extern KeyMove knifeTable;


namespace KnifeTable {
	void init();

	void add(const std::string& fen, const std::string& m);

	Move find(Key key);
}

inline Move KnifeTable::find(Key key) {

	auto it = knifeTable.find(key);
	return it != knifeTable.end() ? it->second : MOVE_NONE;
}




#endif
