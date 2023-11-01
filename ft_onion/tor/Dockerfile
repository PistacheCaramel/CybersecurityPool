FROM alpine:latest


RUN apk add --no-cache libevent openssl openssl-dev zlib zlib-dev build-base; wget "https://github.com/libevent/libevent/releases/download/release-2.1.11-stable/libevent-2.1.11-stable.tar.gz" ; tar xvf libevent-2.1.11-stable.tar.gz; cd libevent-2.1.11-stable; ./configure ; make install 

RUN wget "https://dist.torproject.org/tor-0.4.8.7.tar.gz" 

RUN  tar xzf tor-0.4.8.7.tar.gz; cd tor-0.4.8.7/ ; ./configure ; make install

COPY torrc /usr/local/etc/tor/torrc

CMD ["tor"]
