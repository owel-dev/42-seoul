COMPOSE_FILE = srcs/docker-compose.yml
WP_VOLUME = /home/ulee/data/wordpress
MARIADB_VOLUME = /home/ulee/data/mariadb
HOST_FILE = /etc/hosts
HOST_IP = 127.0.0.1
HOST_DOMAIN = ulee.42.fr

up : clean
	@sudo mkdir -p ${WP_VOLUME}
	@sudo mkdir -p ${MARIADB_VOLUME}
	@sudo grep -qxF "${HOST_IP} ${HOST_DOMAIN}" ${HOST_FILE} || echo "${HOST_IP} ${HOST_DOMAIN}" >> ${HOST_FILE}
	@sudo docker-compose -f ${COMPOSE_FILE} up --build -d
	@while true; do if [ -f "/home/ulee/data/wordpress/wordpress/index.php" ]; then \
		echo "\033[43;31mdone!\033[0m";break; else echo "please wait..."; fi; sleep 3; done

down:
	@sudo docker-compose -f ${COMPOSE_FILE} down --rmi all --remove-orphans

clean :
	@sudo rm -rf ${WP_VOLUME}/*
	@sudo rm -rf ${MARIADB_VOLUME}/*

re : down clean up

.PHONY: up down clean re
