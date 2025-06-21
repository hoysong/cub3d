#ifndef CUB_DEFS_H
# define CUB_DEFS_H

/*Window size.*/
# define WIN_WIDTH	900
# define WIN_HEIGHT	900

/*Minimap size.*/
# define MINISIZE	900
/*Minimap BG_color.*/
# define BG_Color	0xdddddd
/*Minimap GridColor.*/
# define GridColor	0xdddddd
/*Minimap WallColor.*/
# define WallColor	0x999999

/*플레이어의 가시반경.*/
# define VIEW_DIST		3
/*레이캐스팅 광선 투사 각도(해상도).*/
# define RAY_RES		3
/*Player FOV.*/
# define Player_FOV		90
/*Player's move distance.*/
# define STEP_PER_PIXEL	10

/*size of wall.*/
/*example: map[vert][horiz].*/
/*vert  * SIZE_OF_WALL;*/
/*horiz * SIZE_OF_WALL;*/
# define SIZE_OF_WALL	10

#endif
