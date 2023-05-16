# inception

Docker를 사용하여 Wordpress, Nginx, PHP, MariaDB 스택의 블로그를 배포하는 프로젝트 입니다.

## 개발 환경

-   OS: `Ubuntu 20.04`
-   CPU: `intel 64`
-   Wordpress: `2.9`
-   Docker: `Docker CE 19.03`

## 프로젝트 구조

```
.
├── srcs
│   ├── requirements
│   │   ├── mariadb
│   │   │   ├── tools
│   │   │   │   └── run.sh
│   │   │   └── Dockerfile
│   │   ├── nginx
│   │   │   ├── conf
│   │   │   │   └── my_nginx.conf
│   │   │   └── Dockerfile
│   │   └── wordpress
│   │       ├── tools
│   │       │   └── run.sh
│   │       └── Dockerfile
│   ├── .env
│   ├── docker-compose.yml
└── Makefile                            # make 명령어를 사용하여 Docker Compose를 실행합니다.
```

## 컨테이너 다이어그램

<img width="60%" alt="container_diagram" src="https://github.com/owel-dev/42Seoul-Assignments/assets/40191730/70d95a13-ccf7-4cd0-84d0-5f4c5c639009">

## 실행 방법
1.  `make` 명령어를 통해 Docker Compose 실행.
2.  브라우저에서 `localhost:443` 주소로 블로그 접속.
