FROM    alpine:3.15.4

RUN     apk update; \
        apk upgrade; \
        apk add --no-cache nginx openssl; \
        rm -f /var/cache/apk/*

COPY ./conf/my_nginx.conf /etc/nginx/http.d/my_nginx.conf
COPY ./conf/ulee.crt /etc/ssl/certs/ulee.crt
COPY ./conf/ulee.pem /etc/ssl/private/ulee.pem

EXPOSE 443

ENTRYPOINT ["nginx", "-g", "daemon off;"]