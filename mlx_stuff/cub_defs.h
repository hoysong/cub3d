#ifndef CUB_DEFS_H
# define CUB_DEFS_H

/*Window size.*/
# define WIN_WIDTH	900
# define WIN_HEIGHT	900

/*Minimap size.*/
# define MINISIZE	300
/*Minimap BG_color.*/
# define BG_Color	0xdddddd
/*Minimap GridColor.*/
# define GridColor	0xdddddd
/*Minimap WallColor.*/
# define WallColor	0x999999
/*FOV_COLOR*/
# define FOV_COLOR	0xff0000

/*size of block.*/
# define SIZE_OF_BLOCK	300

/*플레이어의 가시반경.*/
/*블록의 크기 * n 만큼이 지정되도록 함.*/
# define VIEW_DIST		SIZE_OF_BLOCK * 4
/*레이캐스팅 광선 투사 각도(해상도).*/
# define RAY_RES		1
# define DEPTH			3

/*Player FOV.*/
# define Player_FOV		90
/*Player Angle per tick.*/
# define CAM_ROTATE_ANGLE	1
/*Player's move distance.*/
# define STEP_PER_PIXEL	5
/*Convert Player cordinate to minimap_res*/
# define MINI_RES(X) X/(float)SIZE_OF_BLOCK
# define TO_INDEX(X) ((X)/(float)SIZE_OF_BLOCK)

#endif
