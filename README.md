# Libft


> 앞으로의 C언어 프로젝트에서 사용할 간단한 함수들을 만들어 보는 프로젝트.

* atoi, strdup, strlen 등의 기본 내장함수를 비롯하여
* split, trim 등의 사용자정의 함수와
* lstnew, lstmap 같은 연결리스트와 관련된 함수들을 만들어야 한다.

# [Part1]

## ft_memset

### 프로토 타입
```
void  	ft_memset(void *dest,  int c, size_t n);
```
### 함수 설명

dest배열을 입력받아

n의 길이만큼 c문자로 초기화하는 함수



## ft_bzero

### 프로토 타입
```
void	*ft_bzero(void *str, size_t n);
```
### 함수 설명

문자열str과 길이 n을 입력받아

문자열 str의 요소들을 n의 길이만큼 0으로 세팅(초기화)한다. 


## ft_memcpy

### 프로토 타입
```
void	*ft_memcpy(void *dest, const void *src, size_t n);
```
### 함수 설명

src배열의 내용을 n길이만큼 dest배열에 복사하는 함수.


## ft_memccpy

### 프로토 타입
```
void	*ft_memccpy(void *dest, const void *src, int c, size_t n);
```
### 함수 설명

src배열의 내용을 n길이만큼 dest배열에 복사하되
c문자 까지만 복사한 후
dest배열에서 c문자가 위차한 인덱스의 다음 인덱스의 주소를 반환한다.


## ft_memmove

### 프로토 타입
```
void	*ft_memmove(void *dest, const void *src, size_t n);
```
### 함수 설명

src배열의 내용을 n길이만큼 dest배열에 복사하되
배열의 요소를 뒤에서부터 복사한다.


## ft_memchr

### 프로토 타입
```
void	*ft_memchr(const void *arr, int c, size_t n);
```
### 함수 설명

arr배열을 첫 인덱스부터 n의 길이까지 검사한다.
검사 도중 c요소를 발견하면, c요소가 존재하는 인덱스의 주소를 반환한다.


## ft_memcmp

### 프로토 타입
```
int	ft_memcmp(const void *s1, const void *s2, size_t n);
```
### 함수 설명

s1배열의 첫 인덱스와 s2배열의 첫 인덱스부터 하나씩 비교하여 n의 길이만큼 비교한다.
비교 도중 같지 않은 부분의 인덱스의
s1요소에서 s2요소를 뺀 값을 반환한다.


## ft_strlen

### 프로토 타입
```
size_t	ft_strlen(const char *str);
```
### 함수 설명
str문자열의 길이를 반환한다.(요소의 갯수)


## ft_strlcpy

### 프로토 타입
```
size_t	ft_strlcpy(char *dst, const char *src, size_t len);
```
### 함수 설명
str문자열의 내용을 dst문자열에 len의 길이만큼 복사한다.(NULL문자 포함)
그 후 src의 길이를 반환한다.


## ft_strlcat

### 프로토 타입
```
size_t	ft_strlcat(char *dest, const char *src, size_t len);
```
### 함수 설명
dest문자열의 끝 부분에(NULL문자의 자리) src문자열을 이어붙이되(NULL문자 포함)
len의 길이를 넘지않게 한다.
그 후 dest와 src길이를 합한 값을 반환한다.


## ft_strchr

### 프로토 타입
```
char	*ft_strchr(const char *str, int c);
```
### 함수 설명
str문자열의 첫 인덱스부터 검사하여
c문자가 위치한 인덱스의 주소를 반환한다.


## ft_strrchr

### 프로토 타입
```
char	*ft_strrchr(const char *str, int c);
```
### 함수 설명
str문자열의 '마지막 인덱스'부터 검사하여
c문자가 위치한 인덱스의 주소를 반환한다.


## ft_strnstr

### 프로토 타입
```
char	*ft_strnstr(const char *s1, const char *s2, size_t n);
```
### 함수 설명
s1문자열이 s2문자열을 포함한 경우
s1문자열에서 s2문자열이 포함된 시작 부분의 주소를 반환한다.

포함되지 않은 경우 NULL을 반환한다.


## ft_strncmp

### 프로토 타입
```
int		ft_strncmp(const char *s1, const char *s2, size_t n);
```
### 함수 설명
s1문자열과 s2문자열을 첫 인덱스부터 비교 해나가며
같지 않은 부분 발견 시 해당 인덱스의
s1요소에서 s2요소를 뺀 값을 반환한다.

s1과 s2가 정확히 일치한다면 0을 반환한다.


## ft_atoi

### 프로토 타입
```
int  	ft_atoi(const char *str);
```
### 함수 설명

"1234"등의 숫자 문자열을 입력받아

int형 1234로 바꾼 후 이를 반환하는 함수


## ft_isalpha

### 프로토 타입
```
int	ft_isalpha(int c);
```
### 함수 설명

숫자를 입력받아

해당 아스키코드에 해당하는 문자가 글자(a~z)일 경우 1을 

그렇지 않을 경우 0을 반환한다.


## ft_isdigit

### 프로토 타입
```
int	ft_isdigit(int c);
```

### 함수 설명

숫자를 입력받아

해당 아스키코드에 해당하는 문자가 숫자(0~9)일 경우 1을 

그렇지 않을 경우 0을 반환한다.


## ft_isalnum

### 프로토 타입

```
int	ft_isalnum(int c);
```

### 함수 설명

숫자를 입력받아

해당 아스키코드에 해당하는 문자가 숫자(0~9) 혹은 글자(a~z)일 경우 1을 

그렇지 않을 경우 0을 반환한다.



## ft_calloc

### 프로토 타입
```
void	*ft_calloc(size_t n, size_t size);
```
### 함수 설명

size크기의 자료형을 n개만큼 저장할 수 있는 메모리 공간을 할당한다.

이후 메모리의 모든 비트를 0으로 초기화한다.



## ft_isascii

### 프로토 타입
```
int	ft_isascii(int c);
```
### 함수 설명

숫자를 입력받아

해당 아스키코드에 해당하는 문자가 printable 문자일 경우 1을 

그렇지 않을 경우 0을 반환한다.


## ft_isprint

### 프로토 타입
```
int	ft_isdigit(int c);
```
### 함수 설명

숫자를 입력받아

해당 아스키코드에 해당하는 문자가 printable 문자일 경우 1을 

그렇지 않을 경우 0을 반환한다.


## ft_toupper

### 프로토 타입
```
int	ft_toupper(int c);
```
### 함수 설명
c문자를 입력받아
해당 문자가 소문자라면 대문자로 변환한 후 이를 반환한다.


## ft_tolower

### 프로토 타입
```
int	ft_toupper(int c);
```
### 함수 설명
c문자를 입력받아
해당 문자가 대문자라면 소문자로 변환한 후 이를 반환한다.


# [Part2]

## ft_itoa

### 프로토 타입

```
char	*ft_itoa(int n);
```

### 함수 설명

int형 숫자를 입력받아 char *형의 문자열로 변환하는 함수,

동적할당한 메모리에 문자열을 저장한 후 그 주소를 반환한다.

## ft_substr

#### 프로토 타입
```
char	*ft_substr(char const *s, unsigned int start, size_t len);
```
#### 함수 설명

str문자열의 begin인덱스부터 n의 길이만큼의 문자열을 잘라서
동적 할당한 메모리에 복사한 후, 그 주소를 반환하는 함수.


## ft_strjoin
#### 프로토 타입
```
char	*ft_strjoin(char const *s1, char const *s2);
```
#### 함수 설명

동적 할당한 메모리에 s1문자열과 s2문자열을 이어붙인 문자열을 복사한 후, 
그 주소를 반환하는 함수.

## ft_strtrim
#### 프로토 타입
```
char	*ft_strtrim(char const *s1, char const *set);
```
#### 함수 설명

str문자열의 '앞과 뒤에서' set문자열에 포함된 문자들을 제거한 후,
이를 동적 할당한 메모리에 복사하여 그 주소를 반환하는 함수.


## ft_split
#### 프로토 타입
```
char	**ft_split(char const *s, char c);
```
#### 함수 설명
str문자열에서 c문자를 기준으로 단어를 구분하여 각 단어를
동적할당한 이차원 배열 메모리에 담아 그 주소를 반환하는 함수.


## ft_itoa

#### 프로토 타입
```
char	*ft_itoa(int n);
```
#### 함수 설명

int형 숫자를 입력받아 char *형의 문자열로 변환한다. 이후

동적할당한 메모리에 문자열을 저장한 후 그 주소를 반환한다.


## ft_strmapi

#### 프로토 타입
```
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
```
#### 함수 설명

s문자열의 각 인덱스에 담긴 값을 
f함수를 적용한 값으로 치환하는 함수.


## ft_putchar_fd

#### 프로토 타입
```
void	ft_putchar_fd(char c, int fd);
```
#### 함수 설명
c문자를 fd파일 디스크립터 형식을 적용하여 출력하는 함수.


## ft_putstr_fd

#### 프로토 타입
```
void	ft_putstr_fd(char *s, int fd);
```
#### 함수 설명
str문자열을 fd파일 디스크립터 형식을 적용하여 출력하는 함수.


## ft_putendl_fd

#### 프로토 타입
```
void	ft_putendl_fd(char *s, int fd);
```
#### 함수 설명
끝에 '줄바꿈'이 추가된 str문자열을 fd파일 디스크립터 형식을 적용하여 출력하는 함수.


## ft_putnbr_fd

#### 프로토 타입
```
void	ft_putnbr_fd(int n, int fd);
```
#### 함수 설명
int형 숫자 n을 fd파일 디스크립터 형식을 적용하여 화면에 출력하는 함수.

# [Bonus Part]

## ft_lstnew

#### 프로토 타입
```
t_list	*ft_lstnew(void *content);
```
#### 함수 설명
content배열이 담긴 구조체를 동적할당으로 생성 후
그 주소를 반환하는 함수.


## ft_lstadd_front

#### 프로토 타입
```
void	ft_lstadd_front(t_list **lst, t_list *new);
```
#### 함수 설명
lst인자로 들어온 연결리스트의 맨 앞에 new인자로 받은 구조체를 끼워넣는 함수.


## ft_lstsize

#### 프로토 타입
```
int ft_lstsize(t_list *lst);
```
#### 함수 설명
lst인자로 받은 구조체 이후로 연결된 구조체가 몇개인지 세어
그 개수를 반환하는 함수.


## ft_lstlast

#### 프로토 타입
```
t_list *ft_lstlast(t_list *lst);
```
#### 함수 설명
lst인자로 받은 구조체에 연결된 구조체들 중
맨 마지막 구조체의 주소를 반환하는 함수.


## ft_lstadd_back

#### 프로토 타입
```
void	ft_lstadd_front(t_list **lst, t_list *new);
```
#### 함수 설명
lst인자로 들어온 연결리스트의 맨 앞에 new인자로 받은 리스트를 끼워넣는 함수.


## ft_lstdelone

#### 프로토 타입
```
void ft_lstdelone(t_list *lst, void (*del)(void *));
```
#### 함수 설명
lst인자로 받은 구조체의 content를 del함수를 이용하여 삭제한 후,
lst구조체의 메모리를 해제하는 함수.


## ft_lstclear

#### 프로토 타입
```
void ft_lstclear(t_list **lst, void (*del)(void *));
```
#### 함수 설명
lst인자로 받은 구조체와 연결된 '모든 구조체들'의 content를 del함수로 삭제하고
구조체의 메모리를 해제해주는 함수.


## ft_lstmap

#### 프로토 타입
```
t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

```
#### 함수 설명
lst인자로 받은 구조체와 연결된 '모든 구조체들'의 content에 f함수를 적용한 리스트를
복사한 후, 복사한 리스트의 첫번째 구조체의 주소를 반환한다.

각 구조체의 content에 f함수를 적용하는 도중 적용에 실패했다면
앞서 f함수가 적용된 모든 구조체의 메모리를 해제한 후 NULL을 반환한다.
