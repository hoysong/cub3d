#ifndef CUB_DEFS_H
# define CUB_DEFS_H

/*Window size.*/
# define WIN_WIDTH	750
# define WIN_HEIGHT	600
# define HALF_WIN_WIDTH 375
# define HALF_WIN_HEIGHT 300

/*mouse*/
# define MOUSE_MIDDLE_X (WIN_WIDTH / 2)
//# define MOUSE_MIDDLE_Y (WIN_HEIGHT / 2)

/*Minimap size.*/
# define MINISIZE	200
/*Minimap BG_color.*/
# define BG_Color	0x666666
/*Minimap GridColor.*/
# define GridColor	0x666666
/*Minimap WallColor.*/
# define WallColor	0x222222
/*FOV_COLOR*/
# define FOV_COLOR	0x990000

/*size of block.*/
# define SIZE_OF_BLOCK	100

/*가상 좌표상의 플레이어 사이즈입니다.*/
/*벽충돌 판정에 사용됩니다.*/
# define PLAYER_SIZE	20

/*Player's view distance.*/
# define VIEW_DIST		(SIZE_OF_BLOCK * 3)
/*레이캐스팅 광선 투사 각도간격(해상도).*/
# define RAY_RES		0.5
/*Player FOV.*/
# define Player_FOV		65
/*Player Angle per tick.*/
# define CAM_ROTATE_ANGLE	2
/*Player's move distance.*/
# define STEP_PER_PIXEL	5
/*Convert Player cordinate to minimap_res*/
# define MINI_RES(X) ((X)/(float)SIZE_OF_BLOCK)
# define TO_INDEX(X) ((X)/(float)SIZE_OF_BLOCK)

#endif
