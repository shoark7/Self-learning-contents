# Git 별칭 만들기 & 커밋 메시지 컨벤션

### 2018/01/01
### 박성환

기본적인 git에 대한 내용은 우리 모두 알고 있습니다.  
관련한 강의 등이 많기 때문입니다. 그렇다면 이번엔,  
git을 어떻게 더 잘 쓸 것인지에 대해도 고민해보겠습니다.  

첫 번째는 git 커맨드를 길게 다 입력하지 않는 방법에 대한 것이고,    
두 번째는 git commit 메시지를 어떻게 효과적으로 입력할지에 대한 것입니다.  


<br>
<br>

## 1. Git 별칭 만들기

혼자 소스코드를 관리하며 깃허브에 푸쉬하기까지, 
git에 커밋을 작성하는 것은 다음과 같은 일련의 거칩니다.  

1. 내용을 작성함.  
2. git add로 스테이지에 추가
3. git commit -m 또는 git commit으로 메시지 작성
4. git pull & git push로 깃허브에 추가

이 과정을 우리는 코딩을 하는 한 끊임없이 해나가는데, 여기서 귀찮음을 느낄 수 있습니다.  

'저 명령어들을 다 입력해야해?', '어떻게 줄일 수 없을까?'.  

네, 가능하고 그 방법을 짧게 알아보겠습니다.   

<br>

### 1.1. git alias 만들기
git은 프로그램이고, 그 안에는 단축키를 만드는 기능도 있습니다.  
바로 `git alias`입니다.  어렵지 않아서 바로 확인하겠습니다.  


```git
# 터미널에 입력

git config --global alias.co checkout
git config --global alias.br branch
git config --global alias.ci commit
git config --global alias.st status 
```

<br>

`config`는 git 환경설정을 하는 기능인데 여기서 alias, 또는 별칭을 만들 수 있습니다.  
위 4개의 커맨드는 git의 checkout, branch, commit, status를 두 자씩으로 줄인 것으로,  

이후 쓸 때는

<br>

```git
git co HEAD
git br
git ci -m "Create unusal.py"
git st
```

<br>

와 같이 쓸 수 있습니다.  

좀 더 활용해서, 아예 새로워보이는 기능도 만들 수 있습니다.

<br>


```git
 git config --global alias.last 'log -1 HEAD'
 git config --global alias.graph 'log --oneline --decorate --all --graph'

# 첫 번째는 마지막 로그 확인
# 두 번째는 로그들을 그래프로 확인

# 둘 다 해보세요!!
```

<br><br>

### 1.2. .bash\_profile alias 만들기
근데 저라면 여기서 한 번 더 스트레스를 받을 것 같습니다.  
맨 앞에 'git'도 쓰기 싫으면 어떡하지??  
저 같은 분들을 위해서 터미널 자체에 단축키를 만드는 방법을 소개해 드리겠습니다.  


아마 맥이나 리눅스를 쓰시는 분들을 기준으로 설명드리겠습니다.  
git을 터미널 CLI 환경에서 작업하실텐데, 터미널에는 '.bash\_profile'라는 터미널 환경설정 파일이 있습니다.  
여기에 작성된 내용들은 터미널이 실행될 때 같이 실행되는데 터미널 customization에 제격입니다.  

다양한 개인 맞춤화를 해볼 수 있는데 이 파일을 통해
* 변수를 만들고 나만의 맞춤 함수를 만들기
* 쉘 프롬프트에 색을 입히거나 모양을 주기
* 테마 씌우기

등을 할 수 있습니다.  
이에 더해 `alias`라고 해서 터미널에서 쓰는 일종의 단축키를 만들 수 있고,  
이것을 활용해서 git용 단축키를 만들어보겠습니다.  

<br>

### 1.2.1. vi란?

.bash\_profile은 파일이고, 편집기를 통해 편집할 수 있는데요.  
이번에는 터미널의 오래 된 편집기 `vi`를 써보겠습니다.  
이 편집기는 그 옛날 마우스나, GUI가 없던 시절에 파일을 편집하기 위해 쓰던 편집기로,  
대단히 어렵고 공부도 많이 해야 하지만, 모든 기능을 키보드만으로 할 수 있어 익숙해지면  
생산성이 높다는 장점이 있습니다.  


이 편집기를 쓰셔야 하는 건 아니지만, 터미널에서 작업하면  
`vi`를 쓰셔야만 하는 상황이 종종 발생합니다.  
그렇기 때문에 어떻게 쓰는지 확인도 해두는겸 이걸 써볼게요 :)

<br>

> 1. 먼저 터미널을 엽니다.
> 2. 첫 위치에서 `vi .bash_profile`이라고 입력합니다.
> 3. `j`를 눌러서 파일의 맨 밑으로 내려갑니다. 그다음 `o`를 입력해 입력모드로 들어갑니다.
> 4. 파일에 alias를 만들겠습니다. 정확한 과정은 밑에서 살펴볼게요
> 5. 모든 작업이 끝나면 'esc' 버튼을 누릅니다.`:wq` 입력하고 'ENTER'를 누르고 vi를 종료합니다.
> 6. 'source ~/.bash\_profile'이라고 입력해 우리가 입력한 내용이 터미널에 적용되게 합니다.

<br>

위에서 하이라이트 된 `o`, `j`, `:wq`는 vim의 기능을 사용하는 건데  
대소문자를 지켜서 입력해야 합니다.

<br>


### 1.2.2. alias 만들기
지금 위의 5단계 중 4번째 단계에 있다고 생각하고 실제로 별칭을 만들게요.  
하나도 어렵지 않고 다음의 문법만 지켜주면 됩니다.

```sh
alias 명령어='줄일 표현'
```

이것을 써서 내 입맛껏 단축키를 만들게요.  

제가 쓰고 있는 단축키들을 조금 보여드릴게요

<br>

```sh
alias pull='git pull origin master'
alias push='git push origin master'
alias st='git status'
```

pull, push, status를 최대한 짧게 쓰기 위해 만들었고,  

<br>

```sh
alias ga='git add'
alias gaa='git add --all'
alias gc='git commit'
```

<br>

위처럼 만들어 git add와 commit을 단 두세글자로 통일할 수 있습니다.  
특히 git add, git commit은 가장 많이 쓰는 명령어이기 때문에 꼭 해보셨으면 좋겠습니다.  

여기서 한발 더 나아가면, git add와 git commit을 보통 같이 쓰기 때문에  
이 둘을 한 명령어로 처리하고 싶을 수 있고, 실제로 가능합니다.  
 

여러분도 가장 많이 쓰시는 기능부터 만들어 보시면 좋겠습니다.  

게을러집시다 :)
