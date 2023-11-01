
FROM alpine:latest

RUN apk add --no-cache openrc openssh-server

COPY sshd_config /etc/ssh/.

EXPOSE 4242

CMD ["rc-service", "sshd start"]
