FROM amazonlinux

COPY hserver.c /home/lab7/hserver.c

COPY hclient.c /home/lab7/hclient.c

RUN yum update -y

RUN yum install -y nano

RUN yum install -y gcc

ENTRYPOINT bin/bash