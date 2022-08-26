#!/bin/bash

INPUT=$1
INPUT_COUNT=$#
BACKUP_DB_PATH=./back/server/backup-db

if [ $INPUT_COUNT -ne 1 ]; then
    exit
fi

if [ $INPUT = "up" ]; then
	openssl req -x509 -newkey rsa:4096 -nodes -sha256 -keyout ./back/server/secrets/private-key.pem -out ./back/server/secrets/public-certificate.pem -days 365 -subj "/C=KR/ST=Seoul/L=Gaepo/O=42Seoul/OU=gon/CN=ft-trans" && \
    if [ ! -d $BACKUP_DB_PATH ]; then
        mkdir $BACKUP_DB_PATH
    fi
    docker-compose up --build
elif [ $INPUT = "down" ]; then
    docker-compose down
elif [ $INPUT = "clean" ]; then
    echo -e "BACKUP_DB의 경로가 \033[31m$BACKUP_DB_PATH\033[0m 가 맞습니까? (yes / no)"
    read USER_ANSWER
    if [ $USER_ANSWER = "yes" ]; then
        rm -rf $BACKUP_DB_PATH
    fi
        docker-compose down --rmi all
fi
