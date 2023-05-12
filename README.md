# ft-containers

C++ STL Container 클래스 중 Vector, Map, Set, Stack 을 C++98 표준에 맞게 구현해보는 프로젝트 입니다.

## 테스트 및 구현 환경

-   OS: `MacOS Catalina 10.15.7`
-   CPU: `intel 64`
-   컴파일러: `Clang 12.0.0`

## 프로젝트 구조

```
.
├── includes
│   ├── etc.hpp
│   ├── map_iterator.hpp
│   ├── map.hpp
│   ├── RBTree_iterator.hpp
│   ├── RBTree.hpp
│   ├── reverse_iterator.hpp
│   ├── set_iterator.hpp
│   ├── set.hpp
│   ├── stack.hpp
│   └── vector.hpp
├── src
│   └── main.cpp   # Container 클래스들의 기능을 테스트 하는 테스트 코드입니다.
└── Makefile       # make 명령어를 사용하여 테스트 코드를 컴파일합니다.
```

## 테스트 방법

`make test` 명령어를 사용하여 `main.c` 파일에 작성된 테스트를 진행합니다.  
ft_containers 클래스들의 간단한 동작과 성능을 측정합니다.

## 참고

-   [CppReference](https://en.cppreference.com/w/)
-   [CPlusPlus.com](https://cplusplus.com/reference/)
-   [llvm-project libc++](https://github.com/llvm/llvm-project)
