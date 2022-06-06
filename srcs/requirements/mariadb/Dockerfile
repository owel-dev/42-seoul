FROM alpine:3.14

RUN     apk update; \
        apk upgrade; \
        apk add --no-cache mariadb mariadb-client; \
        rm -f /var/cache/apk/*

COPY    tools/run.sh /my_scripts/run.sh
RUN	chmod 755 /my_scripts/run.sh

EXPOSE 3306

ENTRYPOINT ["sh", "/my_scripts/run.sh"]
