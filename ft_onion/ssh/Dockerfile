
FROM alpine:latest

RUN apk add --no-cache openrc openssh-server openssh

COPY known_host.txt /

COPY sshd_config /etc/ssh/sshd_config

RUN mkdir -p /run/openrc && touch /run/openrc/softlevel && rc-status \
			&& mkdir -p /root/.ssh \
			&& chmod 0700 /root/.ssh \
			&& cat known_host.txt > /root/.ssh/authorized_keys

EXPOSE 4242

WORKDIR /etc/ssh

RUN ssh-keygen -A

CMD ["/usr/sbin/sshd", "-D"]

