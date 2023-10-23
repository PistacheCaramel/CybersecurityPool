FROM node:14-alpine


RUN apk update && apk add --no-cache openrc vim nginx tor openssh-server 

COPY nginx.conf /etc/nginx/.

COPY sshd_config /etc/ssh/.

COPY torrc /etc/tor/.

EXPOSE 80
EXPOSE 4242

CMD ["/bin/sh"]

