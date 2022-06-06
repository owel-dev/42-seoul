FROM alpine:3.14

RUN     apk add --no-cache php7 php7-common php7-fpm php7-opcache php7-gd php7-mysqli php7-zlib php7-curl\
        php7-json php7-phar php7-mbstring php7-session mysql-client wget; \
        rm -f /var/cache/apk/*

COPY    tools/run.sh /my_scripts/run.sh
RUN     chmod +x /my_scripts/run.sh

RUN     wget https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar; \
        mv wp-cli.phar /usr/bin/wp; \
        chmod +x /usr/bin/wp

WORKDIR /var/www/html/wordpress

EXPOSE 9000

ENTRYPOINT ["sh", "/my_scripts/run.sh"]