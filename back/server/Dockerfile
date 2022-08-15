FROM node:18 AS builder

WORKDIR /app
COPY . .

RUN apt-get -y update && apt -y upgrade && apt-get install -y bash npm postgresql && \
	npm install -y -g @nestjs/cli && \
	npm i &&\
	npm run build
	

FROM node:18-alpine
WORKDIR /usr/src/app
COPY --from=builder /app ./

EXPOSE 3000
ENTRYPOINT [ "npm", "run", "start:prod" ]