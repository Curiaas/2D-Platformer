// Structs
typedef struct {
	int column, row;
//	char map[][];
} data;

typedef struct {
	char map[9][32]; // [game.row][game.columns*2]
} level;

// Prototypes
void test();