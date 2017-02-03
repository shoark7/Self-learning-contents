# 13-16 Chapter
목요일, 19. 1월 2017 11:20오

## 14. 패키지 관리
* **패키지 관리**란 시스템에 소프트웨어를 설치하고 유지 및 관리하는 방법
* 패키지 시스템은 크게 **데비안(.deb) 진영**과 **레드헷(.rpm) 진영**으로 나뉜다.
    - 데비안 진영 : Debian, Ubuntu, Xandros
     - 레드햇 진영 : Fedora, CentOS, Red Hat Enterprise Linux
 
### 14.1   패키지 시스템
 패키지 시스템에서 소프트웨어의 가장 기본적인 단위를 패키지 파일이라고 한다.  
 패키지 파일은 소프트웨어 패키지를 구성하고 있는 파일들의 압축된 형태.  
 단순  소스파일뿐 아니라, 메타데이터, 설치 전, 후에 실행될 스크립트 파일도 포함함.  
  패키지 파일은 패키지 관리자(package maintainer)라고 하는 사람에 의해 만들어지는데,  주로 배포판 회사 직원.  
관리자는 상위 배포자(주로 프로그램 원작자)에게 소스코드 형태의 소프트웨어를 받아서  
컴파일하고 패키지 메타데이터와 기타 필요한 설치 스크립트를 만든다.


### 14.2 의존성
프로그램들은 거의 독립적이지 않다.  
프로그램 구성을 위해 다른 프로그램을 필요로, 의존한다.  
공유 라이브러리가 있고 다수 프로그램에게[ 필수 서비스를 제공한다.
* 우분투 의존 프로그램 검색 방법
> sudo apt-cache depends _pkjname_

### 14.3. 고수준과 저수준 패키지 툴
패키지 관리 시스템은 저수준툴과 고수준툴이 있다.  
저수준 툴은 패키지 삭제, 설치하는 작업을 중점으로 하고, 고수준 툴은 이에 대해 메타데이터 검색 및 의존성 문제 해결까지 해준다.
* 데비안 형식 : dpkg(저수준), apt-get, aptitude(고수준)
* 페도라, 레드햇 : rpm(저수준), yum(고수준)


### 14.4. 우분투 기반 커맨드
1. 패키지 검색 : apt-cache search _search-string_
2. 패키지 설치 : apt-get install _pkg-name_
3. 패키지 삭제 : apt-get remove _pkg-name_
4. 패키지 의존성 검색 : apt-get depends _pkg-name_
5. 설치 파일 삭제 : sudo apt-get autoclean


## 15. 저장 장치
RAID(Redundant Array of Independent Disks): 
- 복수 배열 독립 디스크(Redundant Array of Independent Disks 혹은  Redundant Array of Inexpensive Disks)는 여러 개의 하드 디스크에 일부 중복된 데이터를 나눠서 저장하는 기술이다. 디스크 어레이(disk array)라고도 한다. 데이터를 나누는 다양한 방법이 존재하며, 이 방법들을 레벨이라 하는데, 레벨에 따라 저장장치의 신뢰성을 높이거나 전체적인 성능을 향상시키는 등의 다양한 목적을 만족시킬 수 있다.

* 로그 확인 : sudo tail -f /var/log/sysinfo

## 16. 네트워킹

### 16.1. ping
**ICMP ECHO-REQUEST**라고 하는 고유의 네트워크 패킷을 지정된 호스트로 전송한다.  
이러한 패킷을 수신하는 대부분의 네트워크 장비들은 이에 응답하여 네트워크 연결을 확인시켜준다.

* ICMP(Internet Control Message Protocol)
> The Internet Control Message Protocol (ICMP) is a supporting protocol in the Internet protocol suite. It is used by network devices, like routers, to send error messages and operational information indicating, for example, that a requested service is not available or that a host or router could not be reached.   
> ICMP differs from transport protocols such as TCP and UDP in that it is not typically used to exchange data between systems, nor is it regularly employed by end-user network applications (with the exception of some diagnostic tools like ping and traceroute).
> ICMP는 인터넷 프로토콜에서 지원용 프로토콜에 해당한다. 라우터와 같은 네트워크 장비들이 에러메시지를 보내거나, 요청된 서비스가 더 이상 사용할 수 없거나 호스트나 라우터에 더 이상 접근할 수 없는 등의 기능 정보들을 보내는 데 사용된다.  
> ICMP는 TCP, UDP와 같은 전송 프로토콜과는 다른데, ICMP는 일반적으로 시스템관 정보를 교환하는 데 사용되지도 않고, 엔드 유저 네트워크 어플리케이션에 의해 사용되지도 않는다.(ping이나 traceroute같은 몇몇 대화식 도구들과 같은 예외는 있다.

* 사용 예제
> ping linuxcommand.org

* 유용한 옵션
  1.  -c _number_ : _number_번만큼만 보낸다.
  
### 16.2. traceroute
- 우분투에서는 traceroute가 없다. 설치하자.

### 16.3. netstat
네트워크 설정 및 통계 정보 확인하기

* 유용한 옵션
    1. i : 인터페이스별 통계
     2. e : extend (ie 함께 쓰면 ifconfig와 동일)
    2. r  : route와 동일
    3. s  : 프로토콜별 통계
    
### 16.4 ssh, scp, sftp
제가 집에 만든 라즈베리 파이 서버   
포트 : 222 ,   
주소 : 112.149.17.53  
아이디 : pi2  
비밀번호 : 123456  

이걸로 실습합시다.
* ssh로 저 계정에 접속하자.
* scp로 파일을 가져오자.
* sftp로 파일을 가져오자.

### DHCP, DDNS, 포트 포워딩
설명하겠습니다~!

