FROM alpine:latest


RUN apk update && apk add --no-cache g++ make curl curl-dev


WORKDIR arachnida

COPY ./src/* .

RUN make

CMD ["/bin/sh"]

