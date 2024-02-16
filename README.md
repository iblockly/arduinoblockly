# ArduBlocklyAndroid
Android app using Arduino-Blockly.

... 이 사이트는 작업 중 ...


# 전체 시스템 구성

안드로이드 앱에서 작동하는 blockly 기반의 편집기에 아두이노와 연동하는 Javascript 기반의 대응 동작을 통해 작동한다.

![실행구조](https://github.com/iblockly/ArduBlocklyAndroid/assets/160044072/a2424154-de65-4809-9ab5-2d1f3587d383)


## 아두이노

- 아두이노에서 안드로이드와 연결하기 위해 블루투스를 사용한다. 
- 블두투스는 클래스 버전을 기반으로 연결하고 아두이노의 포트 상태를 연동한다.

## 안드로이드

- 'Blockly' 기반의 스크레치 기반의 블럭 코드를 입력하면
- 실행 시, Javascript 언어로 변환하여 코드를 생성한다.
- 자바스크립트 언어는 인터프리터에 의해 실행되면서 블루투스를 통해 아두이노와 상태 및 포트 명령을 전송하여 동작한다.


