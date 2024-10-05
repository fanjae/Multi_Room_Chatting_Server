## 1. Project 소개 
- Multi Thread를 이용한 Chatting Room을 제공하는 서버이다.

## 2. 개발 환경
- **Server-side (C++)**
- **Client-side(C#)**
- **OS : Windows**

## 3. 서버 아키텍처
- 클라이언트-서버 모델
- 프로토콜 : TCP/IP
- 서버는 멀티스레드 방식으로 다중 클라이언트 요청 처리

## 4. 라이브러리 및 프레임워크
- C# (UI) : Windows Forms
- C++ : std::thread

## 5. 구현 관련 Post 정리
- [Tistory Blog](https://fanjae.tistory.com/category/Toy%20Project/Multi%20Room%20Cheating%20Server)   

## 6. Test Client
- [C# Client](https://github.com/fanjae/Multi_Room_Chatting_Client)   

## 7. etc (개선 필요 사항)
- Client 구현을 최소화 하기 위해 ID 등을 추가하지 않음.
- 다른 Project에서는 DB를 추가하거나 서버가 임의의 ID를 생성하는 방법으로 ID를 사용하는 것이 필요해보임.
