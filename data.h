#include <stdbool.h>

// Structs
typedef struct {
	int column, row;
	bool open, end;
//	char map[][];
} data;

typedef struct {
	int x, y;
} koordinates;

typedef struct {
	koordinates position;
} character;

typedef struct {
	char map[18][64]; // [game.row][game.columns*2]
} level;	
	
// Prototypes
void test();