FROM alpine:latest


RUN apk update && apk add --no-cache g++ make curl curl-dev 

WORKDIR arachnida

COPY ./src/* ./

RUN apk add libxml2 libxml2-dev ; make

CMD ["/bin/sh"]

