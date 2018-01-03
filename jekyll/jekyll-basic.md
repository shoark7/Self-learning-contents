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

설치 방식은 여러 방법이 있는데, 공식 홈페이지에서 권장하는 방법도 있지만,    
내게 편한 방법인 Ubuntu의 패키지 관리자 apt를 사용해 설치해 보도록 한다.

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

적지 않은 시간이 걸리고 설치가 끝난다. 이제 프로젝트를 시작해볼 수 있다.


> 요약
>
> jekyll은 루비로 만든 프로그램이고, 일반적으로 설치할 땐 ruby의 패키지 매니저인 gem을 사용해 설치한다.
>
> `sudo apt-get install ruby-full`로 gem을 설치한다.
> `sudo gem install jekyll`로 jekyll을 설치한다.


<br>
<br>
<br>


## 1. 프로젝트 시작해보기
Jekyll은 Command Line Interface(이하 CLI)이고 GUI 없이 커맨드만으로 모든 작업을 처리한다.  
그래서 터미널이 필수인 것이며 실제로 프로젝트를 만들어보자.  

Jekyll에서 프로젝트를 처음 시작하는 것도 명령어로 수행하는데,  
**내가 프로젝트를 만들고 싶은 위치로 먼저 이동해주어야 한다.**  
우리가 익숙한 `cd`라는 명령어를 활용해서 내가 프로젝트를 시작할 디렉토리로 먼저 이동해주자.  
이 부분은 여기까지만 하고 넘어간다.  

<br>

실제 프로젝트를 수행할 때는 `new`라는 sub-command를 사용한다.  

```sh
jekyll new PATH
```

`new`는 프로젝트를 시작한다. 이때 설치될 경로를 명시해줘야 한다.  
우리는 프로젝트를 시작하고 싶은 위치로 이동했기 때문에 PATH에 `./내가원하는이름`으로  
프로젝트를 생성할 수 있다.

```sh
jekyll new ./designer-portfolio
```

여기서 `.`은 Unix에서 현재 경로를 의미하는 대명사이고, 현재 경로에 'designer-portfolio'라는  
이름의 포트폴리오를 생성한다. **이때 이 경로는 존재하는 디렉토리여서는 안 된다.**  

존재하지 않는 디렉토리를 입력했으면 성공적으로 포트폴리오가 생성됐다는 메시지가 나올 것이다.  

'ls'를 통해 확인할 수도 있겠다.

<br>

잘 생성됐는지 확인해보자.  

Jekyll은 개발 과정에서 쓸 수 있는 로컬 서버를 지원하고 이 안에서 우리가 브라우저를 통해 우리가  
사용하고 싶은 템플릿이 잘 동작하는지 테스트해볼 수 있다.

<br>

```sh
jekyll serve
```

이 명령어는 jekyll 로컬 서버를 실행하는 명령어이고,  
**jekyll 프로젝트 디렉토리의 상위 디렉토리에서 실행해야 한다.**   
프로젝트 디렉토리 안에서 실행하는 것이 아니다.  
실행하면 쉘 프롬프트가 보이지 않고 '127.0.0.1:4000'을 볼 수 있을 것이다.  
로컬 호스트(127.0.0.1)의 4000번 포트에서 서버가 동작하고 있다는 의미이며, 크롬 등 브라우저에서  
`127.0.0.1:4000`을 입력하면 투박하지만 어떤 페이지가 나오는 것을 알 수 있다.  
초라하지만 일단 프로젝트가 동작하고 있다는 것을 의미한다. 꾸미는 것은 이제 할 것이니까 걱정 말자.  
'네 시작은 미천했지만 그 끝은 창대하리라.  


<br>

> 요약
>
> `jekyll new PATH`로 프로젝트를 시작한다.  입력한 PATH로 프로젝트 디렉토리가 생성된다.
> `jekyll serve`로 프로젝트를 로컬에서 테스트해볼 수 있다. 이후 템플릿 개발 등에서 자주 사용할 것이다.

<br>
<br>
<br>


## 2. Jekyll을 github에 연동해보기
결국 우리가 Jekyll을 공부하는 이유는 github에 연동하기 위해서일 것이다.  
Jekyll은 정적인 사이트 생성 프로그램이고, 서버 등에 연동하는 것(호스팅)을 github가 우리를 위해  
대신 해준다.  그러면 우리는 서버관리, 장고 등 백엔드 관리 등을 할 필요가 없는 것이다.
그러려면 당연히 github 아이디는 가지고 있어야 한다. 만약 없다면 어떤 식으로든 만들어야 한다.

github는 우리에게 무료, 자동으로 호스팅해주는 기능을 가지고 있고, 그것을 사용하려면  
우리는 특수한 git repository를 만들어야 한다. 그것의 이름은,

```sh
각자아이디.github.io

# 내 경우는 shoark7.github.io
```

가 된다.  

이 이름으로 리포지토리를 만들면 github는 자동으로 이 리포지토리의 내용물을 호스팅할 하나의 폴더로 인식한다.  
이제 우리가 할 것은 우리가 만든 Jekyll 프로젝트를 이 `아이디.github.io` 깃 디렉토리와 연동하는 것이다.  

<br>

만든 jekyll 디렉토리에서 다음과 같이 입력한다.


```sh
git init
git add --all
git commit -m "Create jekyll project
```

git에 대한 설명은 하지 않는다. 이 정도는 공부했다고 감히 가정한다.

그리고 github에서 `아이디.github.io` 리포지토리를 생성 후 바로 뜨는 페이지에서 
`git remote add origin git@github.com:아이디/아이디.github.io.git` 문장을 복사한 후 
**jekyll project 디렉토리 안에서 실행한다.**  이제 jekyll 프로젝트와 github repository는 연동됐다.  
이제 jekyll project의 내용을 github로 쏜다.

```sh
git push -u origin master
```

`-u` 옵션은 처음 push할 때는 필요하다.   

이제 한 1~2분 후 browser에 `아이디.github.io`라고 입력하면 jekyll 프로젝트의 기본 페이지를 볼 수 있다.  
꾸미는 것은 jekyll project의 구조를 확인한 후 본격적으로 시작한다.


<br>

> 요약
>
> 우리의 최종 목표는 github.io 페이지를 만드는 것이고, 그러려면  
> **jekyll** 프로젝트와 github의 원격 repository를 연결해주어야 한다.
> 앞서 만든 jekyll 프로젝트를 git repository로 만들고,  
> github에서는 `아이디.github.io`의 이름으로 된 repository를 만든다.
> `git remote add origin git@github.com:아이디/아이디.github.io.git` 문장을 jekyll project에서 실행한다.
> `git push -u origin master` 문장으로 로컬의 jekyll project를 원격의 git repository로 push한다.
> 1~2여분 후 `아이디.github.io`를 브라우저에 입력하면 기본 페이지를 확인할 수 있다.


<br>
<br>
<br>


## 3. Jekyll 프로젝트의 구조

'jekyll new'로 프로젝트를 생성하면 디렉토리에 여러 파일이 생겼을텐데,  
이는 jekyll 프로젝트의 정말 뼈대만을 담고 있다. 일반 프로젝트를 가정하고,  
공식 페이지에서 가정하는 '보통의' 프로젝트의 프로젝트 구조를 가져와서 이를 하나씩 살펴보자.


```sh
.
├── _config.yml
├── _drafts
|   ├── begin-with-the-crazy-ideas.textile
|   └── on-simplicity-in-technology.markdown
├── _includes
|   ├── footer.html
|   └── header.html
├── _layouts
|   ├── default.html
|   └── post.html
├── _posts
|   ├── 2007-10-29-why-every-programmer-should-play-nethack.textile
|   └── 2009-04-26-barcamp-boston-4-roundup.textile
├── _data
|   └── members.yml
├── _site
├── .jekyll-metadata
└── index.html
```

<br> 이제 각각에 대해 살펴보면 다음과 같다. <br>


* \_config.yml		: **환경설정 정보 파일.**  명령에 여러 옵션을 부여할 수 있지만,  
		 	  하나의 파일로 관리하는 것이 훨씬 편리하다. 
* \_drafts		: draft는 `초안`의 의미가 있다. **아직 게시되지 않은 포스트를 말한다.**   
			  파일명 형식에 날짜가 없다. `title.MARKUP`
* \_includes		: **재사용하기 위한 파일을 담는 디렉토리.** 필요에 따라 포스트나 레이아웃에 삽입
			  `{% include file.ext %}`와 같이 liquid 태그를 사용하면, `\_includes/file.ext`  
			  파일에 담긴 코드가 삽입된다.
* \_layouts		: 포스트를 포장할 때 사용하는 템플릿. YAML 머리말로 포스트별로 레이아웃을 선택하며,  
			  `{{ content }}`와 같이 liquid 태그를 사용하면 페이지에 컨텐츠가 삽입된다.
* \_posts		: 실제 포스트들이 담긴다. 이때 **반드시 파일 명명 규칙을 준수해야 하며**, 다음과 같다.
			  `**YEAR-MONTH-DAY-title.MARKUP**` 주소는 포스트별로 정의할 수 있지만,  
			  날짜와 마크업 종류는 오로지 파일명에 의해 결정된다.
* \_data		: 사이트에서 사용할 데이터를 적절한 포맷으로 정리하여 보관하는 디렉토리.  
			  Jekyll 엔진은 이 디렉토리의 '.yml', '.yaml', '.json', '.csv' 등 모든 YAML 파일을 읽어  
			  `site.data`로 사용할 수 있게 한다. 예를 들어 `member.yml` 파일이 있다면 이 파일은  
			  `site.data.member`로 접근할 수 있다.
* \_site		: Jekyll이 변환 작업을 마친 뒤 생성된 사이트가 저장되는 기본 경로.  
			  `.gitignore`에 이 폴더를 저장하는 것은 괜찮은 아이디어.
* .jekyll-metadata	: Jekyll은 이 파일을 참고해 마지막으로 빌드한 이후 한 번도 수정되지 않은 파일은  
			  어떤 것인지, 다음 빌드 때 어떤 파일을 다시 생성해야 하는지 판단할 수 있다.  
			  이 파일 또한 `.gitignore`에 추가하는 것은 괜찮은 생각.
* `index.html` 등	: Jekyll은 YAML 머리말 섹션을 가진 모든 파일을 찾아 변환 작업을 수행.
			  이 섹션을 가지고 있지 않은 모든 '.html', '.md', '.markdown' 등이 여기 포함.
* `css`, `image` 폴더	: `favicon`과 같이 이런 폴더나 파일들은 변하지 않고 그대로 생성된 사이트에 복사.
