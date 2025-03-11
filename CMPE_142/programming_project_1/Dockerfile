FROM ubuntu:latest

RUN apt-get update && apt-get install -y \
	build-essential \
	gcc \
	git \
	vim \
	kmod \
	procps \
	strace \
	make \
	linux-headers-generic \
	dkms \
	&& rm -rf /var/lib/apt/lists/*

WORKDIR /app

RUN ["bash"]
