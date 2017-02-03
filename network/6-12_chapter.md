59쪽
: A bit bucket is typically an unidentifiable place where data that is lost in network transmission, data corruption or computer malfunctioning is stored. It was first used to refer to any data objects that were not where they were supposed to be. It is also used in bit shift operations to define the carry bits that are discarded by the computer in a shift operation. Bit bucket is also related to the recycle bin or trash can found in most operating systems, although the contents of a bit bucket generally represent unintentional data loss, whereas the recycle or trash bin is for the intentional deletion or removal of data.

비트 버켓은 일반적으로 네트워크 통신, 데이터 붕괴, 컴퓨터 오작동에서의 데이터가 표류하는 확인할 수 없는 공간을 의미한다. 처음엔 자신의 현재 자리에 있어서는 안 되는 모든 데이터 객체를 의미했다. 또한 비트 단위 연산에서 비트가 좌우로 움직이며 버려지는 비트들을 정의하는 데도 쓰인다. 비트 버킷은 또한 거의 모든 운영체제에서 재활용통이나 휴지통과도 관련 있다. 그런데 비트 버킷의 내용물은 일반적으로 의도되지 않은 데이터 손실과 관련 있지만, 재활용통이나 쓰레기통은 의도적인 데이터 삭제를 위한다는 차이가 있다.


61쪽 cat의 옵션
-s : blank line이 연속해서 있으면 하나만 출력함.
-n : 줄 번호를 출력함


63쪽 wc의 옵션
-c : bytes
-m : char counts
-l : line counts
-w : word counts

한글은 희한하게 3바이트이다.
그리고 파일에 EOF 문자가 들어가서 1byte가 추가된다.

7. 확장과 인용

확장 : 특정 기호들을 번역해서 특별한 의미로 처리하는 것(ex. echo *)

  1. 경로명 확장 : echo *, ls -d .[^.]?*
  2. 틸드(~) 확장: echo ~
  3. 산술 확장   : echo $((2+2))  <-- 산술은 '$(( ))' 로 감싸야 한다.
  4. 중괄호 확장 : Front-{A,B,C}-Back, a{A{1,2},B{3,4}}b
  5. 매개변수 확장: $USER
  6. 명령어 치환 : '$( )'로 감싼다.


76쪽. 따옴표 활용(Quoting)
쉘은 원치 않는 확장을 선택적으로 감출 수 있는 따옴표 기호를 활용하는 기능을 제공한다.

  1. 큰 따옴표
    - 쉘에서 사용하는 모든 특수기호들이 의미가 없어짐($, \, ` 는 예외)
    - 매개변수 확장, 산술확장, 명령어 치환은 그대로 실행된다.

    - echo "file $(ls .)" <-- 이게 왜 안 될까?

  2. 작은 따옴표
    - 작은 따옴표는 모든 확장을 숨긴다.

82쪽. 유용한 커맨드라인 단축키
  1. CTRL-A : 줄 맨 앞으로 이동
  2. CTRL-E : 줄 맨 뒤로 이동
  3. CTRL-K : 현재 커서부터 줄 끝까지 지우기
  4. CTRL-U : 현재 커서부터 줄 앞까지 지우

86쪽. 히스토리 확장
  1. !number <-- number번째 history를 현재 커맨드라인에 복사
  2. !string <-- string으로 시작하는 가장 최근의 history 복사.
  3. !?string <-- string이 포함된 가장 최근의 history 복사

98쪽. 특수 퍼미션
  1. setuid(8진수 4000) : 유효 사용자 id가 실행자에서 소유자로 변경. 신분 상승 가능. +s
  2. setgid(8진수 2000) : 실행자의 그룹에서 소유자의 그룹으로 옮겨감. +s
  3. sticky(8진수 1000) : 디렉토리에 적용하면 함부로 파일을 삭제하거나 이름을 변경하지 못한다.
                          비교 : `g+w`와 다르다! 얘는 생성, 삭제, 이름 변경 모두 가능. +t


107쪽. 프로세스
  프로세스 : 리눅스가 CPU 사용하기 위해 차례를 기다리는 각 프로그램들을 구조화한 것.

110쪽. ps 옵션.
  1. x : tty 조건을 상승시켜(list) tty가 없어도(화면에서 ?) 표시됨.
  2. a : user 조건을 상승시켜, 나의 프로세스가 아니여도 표시됨.
  3. u : displya user-oriented format. 프로세스의 주인인 유저 중심으로 표현


110쪽. VSZ vs RSS
  VSZ : Virtual memory SiZe. 가상 메모리 크기. 기기 매핑은 제외된 상태. 변화할 수 있다.
  RSS : Resident Set Size. 태스크가 사용한 스왑되지 않은 물리적 메모리 크기.


112쪽. top
	hi  --  Hardware IRQ
          The  amount  of  time  the  CPU  has  been  servicing  hardware
          interrupts.

        si  --  Software Interrupts
          The  amount  of  time  the  CPU  has  been  servicing  software
          interrupts.

        st  --  Steal Time
          The  amount  of  CPU  'stolen' from this virtual machine by the
          hypervisor for other tasks (such  as  running  another  virtual
          machine).


127쪽. .bash_profile과 .bashrc의 차이.
  쉘은 로그인 쉘 세션과 비로그인 쉘 세션으로 나뉜다.
  둘에 따라 환경변수 설정파일이 달라지는데,

  1. .bash_profile은 로그인 쉘에
  2. .bashrc는 비로그인 쉘에 적용된다.
