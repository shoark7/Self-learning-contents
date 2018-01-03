# Jekyll 기본에 대한 이해

#### 2018.01.03
#### Stonehead Park

<br>

##### **모든 명령어는 Ubuntu를 환경에서 동작하고 기타 환경에서는 동작하지 않을 수 있습니다.**


## 0. Jekyll 설치

Jekyll은 기본적으로 ruby라는 프로그래밍으로 만들어진 '프로그램'이고, 따라서  
ruby의 패키지 관리자인 gem을 통해 컴퓨터에 설치 가능하다.  

mac의 경우에는 기본적으로 gem이 깔려 있고, Ubuntu 등에서 gem이 설치되어 있지 않다면  
추가적으로 설치해주어야 한다.

설치 방식은 여러 방법이 있는데, 공식 홈페이지에서 권장하는 방법도 있고,  
내게 편한 방법은 Ubuntu의 패키지 관리자 apt를 사용해 설치해 보도록 한다.

<br>

```sh
sudo apt-get install ruby-full
```

gem을 포함한 ruby의 여러 유용한 프로그램을 전체적으로 설치해주는 명령어이고,  
sudo(SuperUserDO)가 아마 필요할 것이다.  이렇게 gem이 설치되면, gem을 통해 jekyll을 설치한다.  

<br>

```sh
sudo gem install jekyll
```

적지 않은 시간이 걸리고 설치가 끝난다. 설치가 온전히 됐는지 확인해보려면 다음과 같이 입력해본다.  

<br>



