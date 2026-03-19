# KFS-2

# 기초 배경 지식 

## 32bit cpu 
32bit cpu 는 32bit 크기의 레지스터들을 가지고 있음
32bit로 4gb 공간만큼의 주소들을 표현 할 수 있음. 

## x86 레지스터 갯수와 크기 
범용 8개(32비트) 
세그먼트 6개 (16비트 - 16 비트 컴퓨터 하위호환) -> CS, DS, SS, ES, FS, GS
명령어 포인터(32비트)
플래그(32비트)

## 메모리 주소 
### 논리 주소 
프로그램이 사용하는 가상의 주소 (!= 실제 램 물리주소)
세그먼트 식별자(셀렉터) : 오프셋(세그먼트 시작 점으로 부터 거리 - 상대적인 주소)

### 선형 주소 
세그먼트 처리 후 나온 가상 논리 주소 (base + offset)

## 세그먼트
물리적인 메모리 공간을 논리적으로 나눠서 이름 붙여놓은 각각의 독립된 공간.
다른 레지스터가 침범 불가한 공간. 

## 세그먼트 레지스터 
각 세그먼트의 세그먼트 셀렉터를 확보하기 위한 목적으로 사용함 (세그먼트 셀렉터를 보관하고 있음)

### CS code segment
실행중인 코드 영역
### DS Data segment
변수, 전역 데이터
### SS stack segment 
함수 호출, 지역변수 
### ES Extra segment 
추가 데이터 영역 
### FS/GS F/G segment 
OS 별 특수 용도


## 세그먼트 셀렉터
GDT/LDT 에서 특정 세그먼트 디스크립터 를 선택하는 식별자. 16비트로 테이블 안의 인덱스를 가리키는 값

### 구조 
인덱스(13비트) : 테이블내 디스크립터 위치
TI 비트 : O = GDT, 1=LDT
RPL(2 비트): 요청자 권한 레벨

우리가 GDT 만들때 이 값을 직접 만들어서 GDT 인덱스로 쓰고 각 레지스터에도 값을 넣어줘야 ?
TI / RPL 은 값을 찾으러 갈때?

## 리얼 모드 

프로그램 동작할때 실제 물리 메모리에 프로그램을 통째로 올려서 작동 시키는것 

## 보호 모드 

각 프로세스 (프로그램) 마다 각자의 가상 메모리 영역을 할당 하고 각각 이 리얼 모드인 것 처럼 인식하고 동작 하게 함. 다른 프로세스의 해당 영역에 대한 접근을 차단 하여 다른 프로세스의 데이터를 보호. 
유저 영역의 프로세스사 커널영역에 접근 하지 못하도록 함 (대신 시스템 콜 같은 프로토콜을 이용하여 사용하게 함).

각 프로그램은 보조 장치에 저장 되있다가 실제 필요한 부분만 메모리에 올라와서 실행(페이징) 됨.

## 참고 :
우리가 처음에 꼽아준 esp 는 임시 스택?


## 세그먼트 디스크립터 
특정 세그먼트에 대한 모든 정보를 담은 8 바이트 구조체 
x86 cpu 가 구조를 이미 알고 있음 (intel 매뉴얼에 프로토콜 처럼 정의됨) 
각 아키텍쳐 마다 다른 메모리 보호 메커니즘이 존재 함. 
64bit 인텔 아키텍쳐는 그대로 사용하고 있음. 
-  ARM : 페이지 테이블만

### 세그먼트 디스크립터 레이아웃 (8 bytes)

복잡하게 나눠진 이유 : 80286 시절 주소 버스가 24 비트 였다고.
주소버스 : cpu 와 램 사이 통로 
Limit
(0 : 15)  limit 의 15 - 0 바이트 [0, 1]

Base
(16: 31)  base address 의 15 - 0 바이트 [2, 3]
(32: 39)  base address 의 23 -16 바이트 [4]

Access, Flags, limit [5, 6]
(40: 43)  type 
(44)  S
(45: 46) dpl
(47) P
(48: 51) limit 의 19 - 16 비트 
(52) AVL
(53) O
(54) D
(55) G

Base 
(56: 63) base address 의 31 - 24 비트

## Limit 
이 세그먼트의 한계점
오프셋은 이 숫자를 넘어갈 수 없음. 
원래 20비트가 필요 해서 하위 16비트와 상위 4비트를 따로 나눠서 저장
마지막 바이트의 인덱스(오프셋)

## Base
이 세그먼트의 시작 주소


## Access Bytes 

7 : p
6 : DPL
5
4 : S
3 : E
2 : DC
1 : RW
0 : A

### A (Accessed) [0]
cpu 가 접근할 때 1로 변함 

### W/R (Write, Read) [1]
code segment : 읽기 권한 
data segment : 쓰기 권한 

### C/D (Confirming, Direction) [2]
code segment : 실행 
data segment : 확장 방향

### E (Executable)

### S (System)
시스템 세그먼트인지 (0)
코드 / 데이터 세그먼트 (1) 인지 결정 
TSS (task state segment) 빼고는 1로 하면됨 (인터럽트 발생했을때 모든 레지스터 저장)


### DPL(Privilege)
이 세그먼트가 커널레벨 인지 유저 레벨인지 나타냄
Ring 0: kernel
Ring 1, 2 : Device drivers
Ring 3: Applications - user level

### P bit 
이 세그먼트가 메모리상에 존재하는지를 나타냄

## Flags 
이 세그먼트 해석 방식을 결정

3 : G
2 : DB
1 : L
0 : Reserved

### G
0 : 세그먼트 크기 단위를 1 byte 블록 단위로 설정
1 : 크기 단위를 4 KiB로 설정 

### DB (Default/Big)
0 : 16 bit
1 : 32 bit

### L (Long mode)
64비트 롱모드 여부 

### Reserved (AVL)
하드웨어가 사용하지 않는 영역 


# 참고 
https://medium.com/@mangryang.dev/%EC%9A%B4%EC%98%81%EC%B2%B4%EC%A0%9C-gdt-4d60d0f40dfc


# GDT (Global descriptor table)
각 세그먼트 디스크립터 를 가진 테이블 
각 엔트리는 8byte!
첫 엔트리는 항상 Null

#  GDTR (Global descriptor table register) 48 비트 
CPU 가 gdt 를 찾아낼 수 있도록 gdt 의 주소와 사이즈 를 담고 있는 레지스터 
GDT base 32 비트 + gdt limit 16비트 
