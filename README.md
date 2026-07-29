# cub3D

![cub3D 실행 화면](./video.gif)

`cub3D`는 42 과제 중 하나로, 고전 FPS 게임 **Wolfenstein 3D**에서 영감을 받은
간단한 3D 그래픽 프로젝트입니다.
C와 MiniLibX를 사용해 2차원 맵을 파싱하고, 레이캐스팅으로 플레이어의 시점에
맞는 3차원 공간을 실시간으로 렌더링합니다.

## 1. 주요 기능

- DDA 기반 레이캐스팅과 원근감 있는 벽 렌더링
- 동·서·남·북 방향별 XPM 벽 텍스처
- 바닥 및 천장 RGB 색상 지정
- 키보드 이동 및 회전
- 마우스를 이용한 시점 회전
- 플레이어 위치와 시야를 표시하는 미니맵
- `.cub` 파일의 요소, 맵 구성 및 폐쇄 여부 검증

## 2. 개발 환경

- C
- Make
- MiniLibX (Linux)
- X11

이 프로젝트는 Linux용 MiniLibX를 저장소의 `minilibx-linux` 디렉터리에 포함하고
있습니다. 빌드하려면 X11 관련 개발 패키지가 필요합니다.

Ubuntu/Debian 계열에서는 다음 명령으로 의존성을 설치할 수 있습니다.

```bash
sudo apt update
sudo apt install build-essential libx11-dev libxext-dev libbsd-dev
```

## 3. 빌드 및 실행

```bash
git clone <repository-url>
cd cub3d
make
./cub3D test_map/good.cub
```

다른 예제 맵도 실행할 수 있습니다.

```bash
./cub3D test_map/pacman.cub
./cub3D test_map/circle.cub
```

사용 가능한 Make 타깃은 다음과 같습니다.

| 명령어 | 설명 |
| --- | --- |
| `make` | `cub3D` 실행 파일 빌드 |
| `make clean` | 오브젝트 파일 삭제 |
| `make fclean` | 오브젝트 파일과 실행 파일 삭제 |
| `make re` | 전체 재빌드 |

### 3.1. `cannot find -lbsd` 오류

빌드 중 다음과 같은 오류가 발생한다면 BSD 호환 라이브러리가 설치되어 있지 않은
상태입니다.

```text
gcc -o mlx-test main.o -L.. -lmlx -L/usr/include/../lib -lXext -lX11 -lm -lbsd
/usr/bin/ld: cannot find -lbsd: 그런 파일이나 디렉터리가 없습니다
```

Ubuntu/Debian 계열에서는 `libbsd-dev` 패키지를 설치한 뒤 다시 빌드합니다.

```bash
sudo apt update
sudo apt install libbsd-dev
make re
```

## 4. 조작법

| 키 | 동작 |
| --- | --- |
| `W` / `S` | 전진 / 후진 |
| `A` / `D` | 좌측 / 우측 이동 |
| `←` / `→` | 시점 회전 |
| `P` | 마우스 시점 회전 켜기 / 끄기 |
| `M` | 미니맵 켜기 / 끄기 |
| `ESC` | 프로그램 종료 |

창의 닫기 버튼으로도 프로그램을 종료할 수 있습니다.

## 5. `.cub` 맵 형식

맵 파일은 텍스처 경로, 바닥·천장 색상, 그리고 실제 맵으로 구성됩니다.
각 설정의 순서는 자유롭지만, 맵은 설정 이후에 위치해야 합니다.

```text
NO ./path/to/north_texture.xpm
SO ./path/to/south_texture.xpm
WE ./path/to/west_texture.xpm
EA ./path/to/east_texture.xpm

F 30,30,30
C 120,180,255

1111111
1000001
10N0001
1000001
1111111
```

### 5.1. 식별자

| 식별자 | 의미 |
| --- | --- |
| `NO` | 북쪽 벽 텍스처 |
| `SO` | 남쪽 벽 텍스처 |
| `WE` | 서쪽 벽 텍스처 |
| `EA` | 동쪽 벽 텍스처 |
| `F` | 바닥 RGB 색상 |
| `C` | 천장 RGB 색상 |

RGB 값은 각 채널마다 `0`부터 `255`까지 지정합니다.

### 5.2. 맵 문자

| 문자 | 의미 |
| --- | --- |
| `0` | 이동 가능한 공간 |
| `1` | 벽 |
| `N`, `S`, `E`, `W` | 플레이어의 시작 위치와 방향 |
| 공백 | 맵 외부의 빈 공간 |

맵에는 플레이어 시작 지점이 정확히 하나 있어야 하며, 이동 가능한 모든 공간은
벽으로 완전히 둘러싸여 있어야 합니다.

## 6. 프로젝트 구조

```text
.
├── main.c                  # 프로그램 진입점
├── parser/                 # .cub 파일 파싱 및 유효성 검사
├── mlx_stuff/
│   ├── algorithm/          # 광선과 벽 충돌 계산
│   ├── raycasting/         # 레이캐스팅 및 화면 렌더링
│   └── ...                 # 창, 입력, 플레이어, 미니맵 관리
├── my_libft/               # 자체 구현 C 유틸리티 라이브러리
├── minilibx-linux/         # Linux용 MiniLibX
├── test_map/               # 정상·비정상 맵과 XPM 텍스처
└── Makefile
```

## 7. 렌더링 개요

각 화면 열마다 플레이어의 시야각에 대응하는 광선을 발사합니다. 광선과 가장
가까운 벽의 충돌 지점 및 거리를 계산한 뒤, 거리에 따라 벽의 높이를 보정해
원근감을 표현합니다. 충돌한 벽의 방향과 좌표를 기준으로 XPM 텍스처의 알맞은
세로 구간을 화면에 그립니다.
