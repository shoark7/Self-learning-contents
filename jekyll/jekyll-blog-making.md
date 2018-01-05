# Jekyll blog 실제로 만들기

#### 2018.01.03
#### 박성환


##### 작성하는 포스트는 jekyll 3.7.0 버전에서 작성되었습니다.

<br>

이제 실제로 jekyll 블로그를 구현해본다. 본 과정은 udemy의 jekyll 강좌를  개인적으로 정리하는 파일이며, 약간의 내용이 추가될 수 있다.  
jekyll project의 기본 구조는 다음과 같다.

<br>

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
├── index.html
├── about
   └── index.html    # url/about  <-- 으로 접근 가능.
```

<br>

이 구조 내에서 각 파일 또는 폴더가 어떤 역할을 하는지는 [이전 포스트](https://github.com/shoark7/Self-learning-contents/blob/master/jekyll/jekyll-basic.md)에서 설명했다.  
이제 이 파일들을 통해 실제로 구현해보자.

<br>
<br>


## 0. 간단한 환경설정하기
환경설정은 `_config.yml` 파일에서 가능하다. 'yml', 또는 'yaml'은 "YAML Ain't Markup Language"의 약자로  
'사람이 쉽게 읽을 수 있는 데이터 직렬화 양식'이다. 처음에는 마크업 언어로 고안되었으나,  
점차 사용처가 데이터를 표현하는 데에 집중되고 있다. jekyll에서도 yml 파일을 이용해 프로젝트의 환경설정을 하고 있다.  

처음 파일을 열어봐도 알겠지만 설정을 기술하는 것은 어렵지 않다. `property: value` 식으로만 입력하면 된다.  
기본 설정 몇 개를 가져오면 다음과 같다.

```yml
title: your awesome title
email: your-email@example.com
...
```

여기서 입력한 값들은 향후 템플릿에서 **'site.title', 'site.email'과 같이 'site.PROPERTY'로 접근가능하다.**  

여기에 설정한 값들은 일반적으로 한 번 설정하면 잘 변하지 않고, 그러지 않아야 한다.  

설정이야 정말 많지만 기본적으로 입력한 것은 다음과 같다.


```yml
title: Stonehead Park's on the way
email: shoark7@gmail.com
description: Blog for dev, knowledge, expressing my thoughts. Managed by Stonehead Park. 
baseurl: ""
url: "http://ok.com"
twitter_username: ""
github_username:  shoark7
google_username: shoark7
```

필요에 맞게 값을 주면 된다. 더 많은 값은 공식문서에서 찾아봐야 한다.

* 참고: 환경설정 파일에 탭을 쓰면 안 된다. 띄어쓰기를 사용할 것  

<br>

> 요약
>
> jekyll project에서 환경설정은 '\_config.yml'에서 가능하며 'property: value' 식으로 원하는 설정을 입력한다.  
> 이후 여기서 입력한 값들은 `site.PROPERTY`로 그 값(value)로 접근할 수 있다.


<br>
<br>
<br>


## 1. Styling
페이지에 진부함을 느껴서인지, 강의에서 스타일링을 먼저 한다.  
Jekyll에서는 css의 확장판인 scss을 지원한다. SASS는 'Syntatically Awesome Styling Sheets'의 약자로,  
기본 CSS를 좀더 편하게 쓰기 위해 개발되었고, SASS 3.0 부터는 주문법이 SCSS로 대체되었다고 한다. 

그래서 이 강의에서는 SCSS를 맛볼 수 있도록 SCSS를 사용한다. 아마 CSS를 써도 큰 문제는 없는 것 같다.


.. 여기는 이후에 추가


<br>
<br>
<br>



## 2. Layout




<br>
<br>
<br>


## 3. 정적인 파일
Jekyll에는 변환이나 렌더링되는 컨텐츠뿐만 아니라 정적 파일이라는 것도 존재한다.  
정적 파일은 **YAML 머리말이 없는 파일을 의미한다.** 이미지, PDF, css 파일 등을 의미한다.  

이 파일들은 `site.statis_files`라는 Liquid tag를 통해 접근 가능하다.  
그리고 다음과 같은 메타 태그를 가지고 있다.

* `file.path` : 파일에 대한 상대경로.
* `file.modified_time` : 파일이 마지막으로 수정된 시간.
* `file.extname` : 파일의 확장자명. 예를 들어 '.jpg'.


<br>
<br>
<br>


## 4. 변수
Jekyll은 작업이 필요한 파일을 찾아 사이트 내부를 이리저리 돌아다닌다.  
작업대상은 **YAML 머리말을 가진 모든 파일**. Jekyll은 Liquid 템플릿 시스템을 통해  
각각의 작업 대상마다 다양한 데이터를 생성한다. 사용할 수 있는 전역변수들은 다음과 같다.

* `site` : 사이트 정보 + `_config.yml`의 환경설정 정보. 
* `page` : 해당 페이지 고유 정보 + YAML 머리말 변수 정보. 사용자 정의 변수 추가
* `content` : 레이아웃에 포함된 포스트 또는 페이지 컨텐츠.
* `paginator` : 페이지네이션(pagination)을 사용할 때 쓸 수 있다. 

특히, 여기서 `site`, `page`는 정말 중요하다. 이 변수의 속성값도 정말 많은데,  
구체적인 값은 [다음](http://jekyllrb-ko.github.io/docs/variables/)에서 확인하자.  
**다 읽는 것을 추천한다.**  
