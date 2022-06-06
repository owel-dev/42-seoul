FROM alpine:3.14

RUN     apk update; \
        apk upgrade; \
        apk add --no-cache nginx openssl; \
        rm -f /var/cache/apk/*

RUN     openssl req -newkey rsa:4096 -x509 -sha256 -days 365 -nodes\
        -out /etc/ssl/certs/ulee.crt\
        -keyout /etc/ssl/private/ulee.pem\
        -subj "/C=KR/ST=Seoul/L=Seoul/O=42Seoul/OU=ulee/CN=ulee.42.fr"

COPY ./conf/my_nginx.conf /etc/nginx/http.d/my_nginx.conf

EXPOSE 443

ENTRYPOINT ["nginx", "-g", "daemon off;"]