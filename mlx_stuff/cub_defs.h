#ifndef CUB_DEFS_H
# define CUB_DEFS_H

/*Window size.*/
# define WIN_WIDTH	1300
# define WIN_HEIGHT	900

/*mouse*/
# define MOUSE_MIDDLE_X (WIN_WIDTH / 2)
//# define MOUSE_MIDDLE_Y (WIN_HEIGHT / 2)

/*Minimap size.*/
# define MINISIZE	200
/*Minimap BG_color.*/
# define BG_Color	0xdddddd
/*Minimap GridColor.*/
# define GridColor	0xdddddd
/*Minimap WallColor.*/
# define WallColor	0x999999
/*FOV_COLOR*/
# define FOV_COLOR	0xff0000

/*size of block.*/
# define SIZE_OF_BLOCK	100

/*플레이어의 가시반경.*/
/*블록의 크기 * n 만큼이 지정되도록 함.*/
# define VIEW_DIST		(SIZE_OF_BLOCK * 3)
/*레이캐스팅 광선 투사 각도(해상도).*/
# define RAY_RES		1
/*키보드 인풋을 받는 간격.*/
# define MOVE_TICK		2
/*마우스 인풋을 받는 간격.*/
# define MOUSE_TICK		4
/*Player FOV.*/
# define Player_FOV		100
/*Player Angle per tick.*/
# define CAM_ROTATE_ANGLE	4
/*Player's move distance.*/
/*1ray만큼의.. 이동거리입니다.*/
# define STEP_PER_PIXEL	7
/*Convert Player cordinate to minimap_res*/
# define MINI_RES(X) ((X)/(float)SIZE_OF_BLOCK)
# define TO_INDEX(X) ((X)/(float)SIZE_OF_BLOCK)

#endif
