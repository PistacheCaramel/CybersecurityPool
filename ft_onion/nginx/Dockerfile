FROM alpine:latest


RUN apk update && apk add --no-cache openrc vim nginx 

COPY nginx.conf /etc/nginx/.

COPY index.html /usr/share/nginx/html/index.html

EXPOSE 80

CMD ["nginx", "-g", "daemon off;"]
