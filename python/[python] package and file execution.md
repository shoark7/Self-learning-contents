# 패키지와 파이썬 스크립트 파일 실행에 관하여  
### 2016-01-01 박성환
---
## 순서

1. 문제 제기 - 패키지에서의 파일 실행..  
  - 1.1. Introduction  
  - 1.2. 문제 제기
2. package와 스크립트 실행  
  - 2.1. package  
      - 2.1.1. What is package?  
      - 2.1.2. \_\_init\_\_.py  
  - 2.2. 스크립트 실행  
      - 2.2.1. 스크립트 실행과 '\_\_name\_\_'
      - 2.2.2. 상대, 절대 경로 import
3. 해결방안  
  - 3.1. -m 옵션을 사용하기
  - 3.2. 프로젝트 구조 개선하기
  - 3.3. \_\_main\_\_.py 사용하기
<br>

그리고 이 글을 읽을 때 다음을 감안해주시면 좋겠다.

* 폴더와 디렉토리라는 용어를 혼용해서 사용하는데 동의어로 사용했다.
* 작성자는 파이썬 3.5 버전을 사용한다.
<br>
<br>

### 1. 문제 제기 - 패키지에서의 파일 실행
#### 1.1. Introduction
  나의 생애 첫 파이썬 프로젝트는 [CLI 금전출납부](https://github.com/shoark7/Persoanl_accountbook)를 만드는 것이었다.
  pickle을 데이터베이스 삼아 그 날의 금전 지출을 기록하고 요일별, 월별 통계를 조회할 수 있는 프로그램이었는데
   약 300줄 정도의 프로그램으로 며칠 동안 매달렸던 기억이 있다.  
  12월을 마무리하면서, 그리고 나름 파이썬을 좋아하고 공부해왔으니 문득 내가 얼마나 성장했는지 보고 싶었다.  
  
   그래서 이번에는 비슷한 컨셉의 [금전출납부](https://github.com/shoark7/second-accountbook)를 완전히 새로 만들고 싶었고 작업에 착수했다.  
    그런데 이번에는 특히 파이썬 패키지 구조를 잘 지키면서 개발하고 싶었다.(패키지에 대해서는 나중에 더 설명한다.)  
   
   파이썬은 모듈화가 장점이기에 패키지, 모듈화를 잘 지키면 반드시 차후에도 나한테 득이 될 것이라고 생각했다. 
   그리고 앞으로도 언제나 그렇개 개발하고 싶었다.
<br>

   
#### 1.2. 문제 제기
개발을 하던 중 처음 보는 치명적인 Error가 발생했다. 
한 줄로 말하면 **패키지에서의 스크립트 파일 실행에 관한 문제**였는데 본격적으로 이야기하기 전에 설명을 위한 디렉토리 구조를 간단히 그리면 다음과 같다.

```python
# 프로젝트 구조
  container/
		└ account_book/    # 최상위 폴더
             ├ __init__.py
		     └ A/
			   ├ __init__.py
			   └ B/
  			      ├ __init__.py
	  		      ├ helper.py
		  	      └ main.py  # 메인 모듈
```
즉 디렉토리 구조는 container 디렉토리 안에 account\_book이라는 최상위 폴더가 있고, 실제 프로그램은 더 깊숙이 main.py에서 실행되는 구조이다.  

helper.py에는 main.py가 실행되는 데 필요한 필수 함수를 담고 있다. helper.py와 main.py의 내용을 살펴보면 다음과 같다.

```python
# helper.py
"""
프로그램이 돌아가는 데 필요한 편의 함수를 담고 있다.
"""

def print_new_year():
    print("다들 새해 복 많이 받으세요!")

```


```python
# main.py

"""
B 패키지 안의 helper 모듈에서 함수를 빌려쓴다. 
"""

from . import helper

print('2016년 병신년이 갔습니다.')
helper.print_new_year()

# main.py는 helper 모듈을 import하고 있다.
```
<br>
자, 이것이 내 금전출납부 프로그램의 대략적인 뼈대다. 실제 프로그램을 실행하기 위해서는 메인을 실행해야 한다.   
파이썬 스크립트 실행을 모르는 사람은 없고 나도 마찬가지이므로 프로그램을 실행시켜 보았다.

```bash
➜  cd account_book/A/B
➜  python main.py  
Traceback (most recent call last):
  File "main.py", line 4, in <module>
    from . import helper
SystemError: Parent module '' not loaded, cannot perform relative import
```

??? SystemError라는 보기 힘든 에러가 출력되었고 실행이 안 됐다.  
이게 안 되면 프로그램 자체가 실행이 안 되는 것이기 때문에 당황했고, 며칠을 알아보았다.  
그 후에야 어느 정도 감을 잡게 되어, 나를 위해서, 또 배움에 굶주리는 다른 분들을 위해 정리해보기로 했다.
<br>
<br>  
<br>    
      
## 2. package와 스크립트 실행
이 문제를 해결하기 위해 자료를 많이 찾아보았다. 검색 결과 기대한 이상 공부를 많이 하게 됐고  
package와 스크립트 실행이라는 두 가지 맥락을 다 정리하면 좋을 것 같다.

package..  
 나는 앞서 이번 프로그램은 패키지 구조로 짜겠다고 했다. 본격적으로 들어가기 전에 패키지는 구조가 있는 모듈 형태인데
 parent module라고 언급되어 있는 것을 보면 일단 패키지의 문제가 있다는 생각이 들었다.
 
스크립트 실행..  
 패키지 구조에서 스크립트 실행이 에러가 났는데 여기에는 \_\_name\_\_에 대해 살펴봐야 한다.
 
<br> 
 
### 2.1. package
나는 자바를 한 달 정도 공부한 기억이 있는데 자바에서는 package(이하 패키지)라는 개념이 있었다.  
1년 전에 잠깐 배웠음에도 패키지라는 개념이 생각이 나는데 파이썬에서 패키지라는 개념은 다소 생소한 것 같다.  

하지만 우리가 가져다 쓰는 많은 모듈의 경우도 패키지 구조이고 큰 프로젝트의 경우에는 이렇게 관리하지 않을 수가 없다.  
혹시 모르지 않는가? 우리가 나중에 DiJango(디장고)라는 커다란 프로젝트를 만들게 될지. 본격적으로 들어가 보자.

#### 2.1.1. What is package?
이름에서 유추해볼 수 있듯이 패키지는 묶음이다. 파이썬 파일의 묶음으로, 모듈의 묶음이라고도 할 수 있겠다. 그런데 단순히 묶어만 놓은 것은 아니다.  

파이썬 공식문서에 따르면 패키지는 **"모듈들을 ' . '으로 묶어 구조화하는(모듈들의 hierarchy를 만드는) 방법, 또는 묶음"**이라고 말하고 있다.(내가 조금 각색했다.)  

쉽게 말해서 비슷한 모듈끼리는 한 폴더에서 묶고,  
상하 관계의 모듈은 폴더 구조를 통해 위계를 만들어 파이썬 모듈들을 관리하는 것이다.  

그렇게 관리한 패키지와 모듈은 파이썬 안에서 ' . '으로 접근할 수 있다. 장고를 써본 사람들은 안다.  
`import django.contrib.auth` 와 같이..  

1.2에서 내 프로젝트의 디렉토리 구조를 소개했다. 간략화해서 파일이 몇 개 없지만 패키지 구조는 지키고 있다.  
이 프로그램의 경우 **account_book이라는 최상위 패키지는 A 패키지를 가지고 있고 A 안의 B 패키지는 helper, main 모듈을 가지고 있다.**  
이렇게 하면 나중에 모듈이 많아질 경우 알아보기도 쉽고 관리하기도 쉬울 것이다.  

그리고 **패키지는 모듈이다.** 그 증거로 container 디렉토리에서 파이썬 interpreter를 실행한 뒤, `import account_book`을 입력하면 정상적으로 import가 된다.
account_book은 파이썬 스크립트 파일이 아닌 폴더임에도 말이다.  
나는 이전까지 '모듈 = .py 파일'이라고 알고 있었는데 완전히 잘못된 개념이었다. 패키지도 모듈이기 때문에. 
뒤집어서, **모든 패키지는 모듈이라고 할 수 있지만 모든 모듈은 패키지라고 할 수도 없다.**  .py 파일은 패키지가 이니기 때문에 ㅎ  

그러면 이런 질문을 해볼 수도 있겠다. `패키지 모듈과 스크립트 파일 모듈을 구분할 수는 있을까?` 답은 '그렇다'이다.  
모듈이 import되면 그 모듈의 특정값들이 설정되는데, **패키지 모듈은 \_\_path\_\_라는 값을 갖는다.** 스크립트 파일 모듈은 그런 값이 없다.  

container 디렉토리에서 account_book을 import 해보자. 그리고 \_\_path\_\_값을 확인하면..

```python
>>> import account_book
>>> account_book.__path__

['/home/sunghwanpark/container/account_book']
```
<br>
패키지의 경로가 나온다. 이 경로에 있는 모듈을 'account_book'은 import할 수 있는 것이다. 
이 경로 안에 'Á' 패키지가 있어 `account_book.A`라고 접근할 수 있다.  

그러면 이런 의문이 든다. 이 패키지의 경로는 하나인데 왜 굳이 문자열로 출력이 안 되고 리스트가 출력되었을까?  
그 이유는 필요할 경우 이 **\_\_path\_\_ 리스트에 다른 경로를 추가해서 그 경로에 있는 모듈도 account_book을 통해서 접근할 수 있도록 할 수 있기 때문이다.**

```python
>>> account_book.__path__.append('/home/sunghwanpark')
>>> print(account_book.__path__)

['/home/sunghwanpark/container/account_book', '/home/sunghwanpark']
```
<br>
\_\_path\_\_ 디렉토리에 내 홈 경로를 추가했다.  
그리고 내 홈 경로에 `ok.py`라는 모듈이 있었다면  account_book을 import한 시점에서 그 파일을 쓸 수 있다.

```python
import account_book.ok
```
세상에.. 내가 이것을 의미있게 쓸 수 있을 수준이 될 수 있을지는 모르겠지만..  
어쟀든 이런 속성이 있다는 것을 알고 넘어가자.
<br>


#### 2.1.2. \_\_init\_\_.py

그러면 폴더에 파이썬 파일을 쑤셔넣으면 다 패키지인가? 라고 하면 그건 또 아니다. 
디렉토리 구조 부분에서 '\_\_init\_\_.py'가 보일 것이다. \_\_init\_\_이라는 클래스 초기화 메서드는 많이 써봤겠지만 \_\_init\_\_.py는 보지 못했을텐데, 용도는 비슷하다.  
**\_\_init\_\_.py는 패키지를 초기화하는 파일**로 패키지는 이 파일을 가지고 있어야 한다.  

3.3 버전 이전까지는 \_\_init\_\_.py가 없으면 아예 디렉토리를 패키지로 인식하지 않았다. 
3.3 부터는 사실 \_\_init\_\_.py가 없어도 문제없이 인식하지만, 패키지 초기화의 이슈나, 이전 버전과의 호환, 
그리고 다른 개발자들과의 협업을 위해서 빈 파일일지언정 꼭 만들어두는 것이 낫다.  

\_\_init\_\_.py가 초기화를 담당했다고 했는데 그 의미를 살펴보도록 하자.
뒤의 import에서 좀 더 살펴보겠지만 **패키지를 import할 때, 패키지에 \_\_init\_\_.py가 있다면 그 \_\_init\_\_.py가 실행된다.**  

account_book 패키지의 \_\_init\_\_.py에 다음과 같이 적었다고 치자.
세 가지 경우에서 \_\_init\_\_.py의 활용성을 살펴볼 것이다.
```python
print("I'm account_book!")   # 1.

ok_bank = 3		# 2.

from .A.B.helper import print_new_year # 3.
```
<br>
그리고 container 디렉토리에서 파이썬 인터프리터를 실행한 뒤, account_book을 import하자.

```python
>>> import account_book

I'm account_book!
```
<br>
\# 1. **print("I'm account_book!")**  
라고 적은 내용이 출력되었다. 우리가 [autoenv](https://github.com/kennethreitz/autoenv)를 사용해 특정 폴더에 접속하면 어떤 내용이 출력되도록 할 수 있듯이,
여기서도 이런 식으로 사용해서 해당 모듈에 대한 정보나, 다른 편의를 제공할 수 있을 것이다.  

\# 2.**ok_bank = 3**  
변수를 지정했다. 지금 'account_book'은 py 파일이 아니라 패키지, 다시 말해 폴더다.   
스크립트 파일 모듈에서는 모듈 상수, 함수 등을 만들어서 사용할 수 있는데 패키지에서는 \_\_init\_\_.py에 그 내용을 작성하면 일반 모듈과 동일하게 접근할 수 있다.  
지금은 ok\_bank'라는 변수를 설정해놓았다. 인터프리터에서 `account_book.ok_bank`라고 입력하면 '3'이라고 잘 출력되는 것을 알 수 있다.

\# 3. **from .A.B import helper**  
이 부분이 내가 장고를 배우면서도 많이 헷갈렸던 부분이다. 가정을 해보자.  
프로젝트가 성숙해지면서 많은 모듈, 패키지가 생성되었고 관계도 깊어졌다. 
그러던 중 관계의 깊이가 많이 차이나는 두 모듈 사이에서 반대 모듈이나 속성에 접근하려면 어떻게 해야 할까?  
우리의 프로젝트라면 account_book 패키지에서 helper.py의 'print\_new\_year' 함수를 바로 쓰고 싶다면?  

일반적인 방법은 정직하게 다 import하는 방법이 있다.

```python
# python interpreter
>>> from account_book.A.B.helper import print_new_year
```
<br>
이것도 나쁘지 않다. 하지만 언제나 그렇지만 좀 더 편하게 초기화할 수 있다면, 실행할 때마다
경로 고민 없이 차후에도 편하게 사용하고 싶다면 \_\_init\_\_.py에 초기화하는 것은 좋은 선택이다.  
프로젝트가 복잡해지면 더 유용할 것이다. 실제로 장고에서도 \_\_init\_\_.py에 모듈들을 미리 초기화해놓고 더 편하게 접근할 수 있도록 지원하고 있다.  

account\_book의 \_\_init\_\_.py에 `from .A.B.helper import print_new_year`처럼 적음으로써,  
`import account_book`을 하는 것만으로 바로 `account_book.print_new_year` 이렇게 함수에 접근할 수 있다.  

이전의 우리라면 'account_book이라는 py 모듈 안에 print\_new\_year라는 속성이 있구나'라고 하겠지만  
이제는 꼭 그렇지 않을 수도 있음을 안다.  

\* 파이썬 패키지의 기본 개념을 살펴보았다.  사실 이 문제는 더욱 깊게 들어갈 수 있다. 
단순 import뿐만 아니라 **load**라는 개념도 살펴보면 좋은데 생각보다 글이 길어진다. 이후 더 같이 공부해보자.  
~~사실 나도 모른다 하지만 꼭 다시 확인하겠다.~~  


<br>

### 2.2 스크립트 실행
패키지에 대해서는 어느 정도 알아보았다.  
우리 문제는 스크립트 파일을 실행하는 동안, 상대경로 import를 했는데 문제가 발생한 것이다.  
여기에는 '\_\_name\_\_'라는 변수가 한 몫했는데 이것에 대해 알아보고,  
상대, 절대경로 import도 간단히 살펴보도록 하자.


<br>
#### 2.2.1 스크립트 실행과 '\_\_name\_\_'

> 내가 그의 이름을 불러 주기 전에는 그는 다만 하나의 몸짓에 지나지 않았다

> 내가 그의 이름을 불러 주었을 때, 그는 나에게로 와서 꽃이 되었다.

> [김춘수 '꽃' 中]

잘 알다시피 스크립트 파일 실행은 `python abc.py`와 같이 실행한다.  
그런데 모듈을 import할 때와, 실행할 때를 구분하기 위해  
```python
if __name__ == '__main__':
    code...
    code...
```

이렇게 쓰는 것을 잘 알 것이다. 모듈은 \_\_name\_\_이라는 변수를 갖는다.
일반적으로 우리가 import를 해서 모듈을 사용한다면 \_\_name\_\_값은 모듈의 원래 이름을 갖는다.

```python
>>> import random
>>> print(random.__name__)

'random'
```

그런데, **모듈을 스크립트로 실행하면 \_\_name\_\_이 원래 이름이 아니라 '\_\_main\_\_'이라는 값으로 설정된다.**  
실행파일이라는 의미로, 인터프리터에서는 \_\_name\_\_이라는 전역변수가 '\_\_main\_\_'으로 이미 설정되어 있다.  

그래서 `if __name__ == '__main__':` 와 같은 코드를 사용할 수 있는 것이다.  

조금 있다가 살펴보겠지만, 이것이 우리의 문제의 원인이었다.

<br>
#### 2.2.2. 상대, 절대경로 import

이 부분은 핵심만 짚고 넘어가려고 한다.  
파이썬에서 import하는 방법은 알다시피 절대경로와 상대경로 방법이 있다.  

절대경로 방식은 `from account_book.A.B import helper`와 같이 경로를 처음부터 다 입력하는 방식이다.  

상대경로 방식은 **`from .. import B`**와 같이 **현재 경로를 기준으로 import를 표현하는 방식이다.**  
이때 ' . '은 현재 경로, ' .. '는 이전 경로를 의미한다. 위의 문장은 '현재의 이전 경로에서 B를 import하라'가 된다.  

문제의 main.py는 다음과 같이  상대경로로 import하고 있다.  
`from . import helper`  
helper와 main은 같은 경로에 있기 때문에 이렇게 import할 수 있다.

그리고 에러 메시지는 다음과 같다.  
`SystemError: Parent module '' not loaded, cannot perform relative import`   


main의 부모 모듈은 B이다. 그런데 부모 모듈이 '', 그러니까 빈 문자열이라고 에러를 내고 있는데 원인은 \_\_name\_\_에게 있다.  


패키지 상하관계에서 서로의 위계는 \_\_name\_\_의 값으로 구분된다.  
A의 \_\_name\_\_은 'A'이고, B의 \_\_name\_\_은 'B'인데 실제 구조에서 B 패키지는 A 패키지 밑에 속해 있다. 여기는 문제가 없다.  
main.py를 스크립트로 실행하면 main 모듈의 \_\_name\_\_은 '\_\_main\_\_'으로 설정된다.  
실행되면서 `from . import helper` 문장에서 ' . ', 그러니까 main.py의 부모 모듈을 찾게 된다.  

근데 main.py의 \_\_name\_\_은 '\_\_main\_\_'으로 파이썬은 **'main.py'가 아니라 '\_\_main\_\_'의 부모 모듈을 찾게 된다.**
지금 이런 모듈은 없고, 이 부모 모듈을 '', 즉 없는 값으로 표현하는 것이다.  

그래서 파이썬 공식문서에서도 패키지의 main(실행) 모듈에서는 상대경로 import를 쓰지 말라고 적혀 있다.  
이런 문제점이 있기 때문으로 main에서는 절대경로 import만 써야겠다. 

이것은 파이썬 패키지 구조가 꼭 물리적 디렉토리에만 의존하는 것을 보여주는 예로서,  
여기서 소개는 안 했지만 일반 패키지와 함께 디렉토리 구조에 한정되지 않는 namespace package라는 것이 따로 있다고 한다.  
이건 더 실력 쌓이면 공부해보겠다..
<br>
<br>

## 3. 해결방안
처음 겪은 문제의 원인이 무엇인지 밝혀졌다.
정리하자면,

> 파이썬은 모듈을 import할 때 \_\_name\_\_값을 통해 본인의 이름으로 확인한다.  
> 파이썬 스크립트를 실행하면 \_\_name\_\_은 모듈의 본연의 값이 아니라 '\_\_main\_\_'이라는 문자열로 설정된다.
> main 모듈에서 상대경로 import를 사용하면 '\_\_main\_\_'모듈의 부모, 형제를 찾게 되는데 이는 우리가 바라는 바가 아니다.
> 그래서 패키지의 main 모듈에서는 상대경로 import를 쓰면 안 된다.

정말 돌고 돌아 무엇이 문제였는지 결국 파악했다.  
이제는 어떻게 이 문제를 해결해야 할까. 알아본 바에 의하면 몇 가지 방법이 있다.

<br>
<br>
### 3.1. -m 옵션 사용하기
우리가 파이썬 스크립트 파일을 사용할 때 옵션을 넣을 수 있다.  
`python -h`이라고 입력하면 여러 옵션들을 확인할 수 있는데, 우리는 -m 옵션을 사용할 것이다.(추가적으로 -c, -o(-oo), -s 정도 보면 좋을 것 같다.)  

-m은 'run library module as a script', 모듈을 스크립트로 실행하는 것이다.  

이렇게 실행하면 모듈 자체를 사용하므로 \_\_name\_\_은 그대로 본인의 이름을 사용하게 된다.  
우리의 경우에는 '\_\_name\_\_'이 'main'이라는 값을 가질 것이다.  
이렇게 되면 'main'의 부모 모듈, B를 찾게 되고 자연스럽게 'helper' 모듈까지 검색이 가능해지는 것이다.  

```python
# 파이썬 모듈이기 때문에 ' . '으로 연결하고, py 확장자를 붙이지 않는다.
# 현재 디렉토리는 'container'

>>> python -m account_book.A.B.main
2016년 병신년이 갔습니다.
Happy new year, guys!
```
<br>
아까의 에러는 온데간데 없고, 결국 실행되었다.

<br>
<br>
### 3.2. 프로젝트 구조 개선하기
나는 이 방법이 위 방법보다는 나은 것 같다. 메인 모듈은 상대 경로로 import하지 말라고 했다.  
그러면 절대경로로 import하라는 뜻인데 그렇게 되도록 프로젝트 구조를 개선해보면 어떨까?

```python
# main.py 쓰기
  container/
		├ main.py	   # 메인 모듈
		└ account_book/    # 최상위 폴더
             ├ __init__.py
		     └ A/
			   ├ __init__.py
			   └ B/
  			      ├ __init__.py
	  		      └ helper.py
```
<br>

아까와 비교해보면, account_book이라는 최상위 패키지가 프로그램을 실행하는 main.py와 같은 디렉토리 안에 있다.  
그러면 main에서 account_book을 직접 import하는 것이 가능해진다!  

그리고 account_book의 \_\_init\_\_.py에 초기화 코드를 설정해준다면 더 좋을 것이다.
<br>
<br>

### 3.3. \_\_main\_\_.py 사용하기
이 방법을 사용하면 `python account_book`처럼 프로젝트 자체를 실행하는 게 가능해진다.  
account_book 디렉토리에 \_\_main\_\_.py를 만들고 여기에 실행코드를 작성하는 것이다.  

```python
# __main__.py
  container/
		└ account_book/    # 최상위 폴더
             ├ __init__.py
             └ __main__.py
		     └ A/
			   ├ __init__.py
			   └ B/
  			      ├ __init__.py
	  		      └ helper.py
```
<br>

그리고 \_\_main\_\_.py에는 기존 main.py의 내용을 조금 수정해서 적는다.

```python
"""
B 패키지 안의 helper 모듈에서 함수를 빌려쓴다.
"""
from A.B import helper

print('여기는 서울, 서울')
helper.print_new_year()
```
<br>

그리고 account_book 패키지 자체를 실행한다!

```python
# 현재 경로는 container
# .py 확장자가 없음을 주목!

>>> python account_book

2016년 병신년이 갔습니다.
Happy new year, guys!
```
<br>

아아, python 커맨드를 .py 확장자 없이 쓰리라고 누가 예상했을까.. 실로 아름답기 그지없다.



<br>
<br>
<br>
<br>




# 부록
### import
파이썬을 처음 배우던 때를 더듬어보자. 아마 print라는 함수부터 시작해서 간단한 모듈을 import 해보기도 했을 것이다.  
나같은 경우에는 'string', 'random'과 같은 내장 모듈을 처음에 접했던 기억이 있다.  

그런데 **내가 어디에서 파이썬 인터프리터를 실행을 하든, 'string', 'random'과 같은 모듈은 문제없이 import 된다.** 그건 그렇다고 치자.  

나는 전에 숫자값을 넣으면 천의 자리마다 콤마( , )를 넣어 출력하는 함수를 만든 적이 있는데 파이썬에서 자체 지원함을 모르고
파이썬을 실행할 때마다 import할 수 있기를 바랬다.  

그렇지만, **내가 직접 만든 모듈은 해당 모듈이 있는 폴더에서가 아니면 import되지 않는다.**

왜 그럴까? 그래서 먼저 모듈의 import 경로에 대해서 알아보자.

#### 어떤 모듈이 import 되는가
과연 어떤 모듈이 import되고, 어떤 모듈은 안 되는가?  
파이썬 공식문서에 따르면 import될 모듈들이 속한 경로가 세 가지 조건 중 하나는 만족해야 한다.
> 1. **import하려는 모듈이 import하는 모듈(파일)과 같은 경로에 있을 때**(인터프리터의 경우는 현재 경로에 그 모듈이 있을 때)
>	- 한 경로에 모듈을 여러 개 만들어놓으면 한 쪽에서 다른 한 쪽을 import 할 수 있다.
> 2. 기존 파이썬 설치 경로에 있는, 미리 사용예정된 모듈들(builtin), 또는 공식 설치된 모듈들(django 등)
> 	- 파이썬 설치 경로를 추적해보면 이런 모듈들이 설치된 곳을 찾아볼 수 있다.
> 3. 컴퓨터의 **`PYTHONPATH`라는 환경변수 값에 지정된 경로 안의 모듈들**
>	- 이 변수에 디렉토리 값들을 설정하면 이 디렉토리 안의 모듈은 언제 어디서나 정상적으로 import할 수 있다.

그리고 각 조건에 해당하는 경로는 sys모듈의 `sys.path`라는 값에 리스트로 설정된다.  
이 값의 원소들은 경로의 문자열값으로, 해당 경로 안의 모든 모듈은 어디서든 import할 수 있는 것이다.  
직접 값을 찍어보자.  

```python
import sys
from pprint import pprint

print(sys.path)

['', # 1.
 '/home/sunghwanpark/.pyenv/versions/3.5.2/bin',
 '/home/sunghwanpark', 	# 2.
 '/home/sunghwanpark/.pyenv/versions/3.5.2/lib/python35.zip',
 '/home/sunghwanpark/.pyenv/versions/3.5.2/lib/python3.5',
 '/home/sunghwanpark/.pyenv/versions/3.5.2/lib/python3.5/plat-linux',
 '/home/sunghwanpark/.pyenv/versions/3.5.2/lib/python3.5/lib-dynload',
 '/home/sunghwanpark/.pyenv/versions/3.5.2/lib/python3.5/site-packages',
 '/home/sunghwanpark/.pyenv/versions/3.5.2/lib/python3.5/site-packages/IPython/extensions',
 '/home/sunghwanpark/.ipython']

```

\# 1. 첫 번째 값 ''은 빈 문자열인데 현재 모듈이 속한 경로다.(인터프리터에서는 현재 경로)  
\# 2. 이 값은 홈경로로서 내가 전에 PYTHONPATH에 설정해놓은 값이다. 이곳의 모든 모듈은 어디서든 접근할 수 있다.  
\# 3. 그리고 나머지는 파이썬이 기본적으로 빌트인 등 기본 모듈들을 찾는 곳이다.  

이 값은 리스트인데 이 값에 다른 값을 추가하면 **그 값도 모듈 검색 경로가 된다.**  
한 번 해보는 것을 추천한다.
