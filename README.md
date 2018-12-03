# OTUS-CPP-W3: allocator

[![Build Status](https://travis-ci.org/olpotkin/OTUS-CPP-W3-allocator.svg?branch=master)](https://travis-ci.org/olpotkin/OTUS-CPP-W3-allocator)

## Environment
- `docker pull ubuntu:trusty`

In order to use <b>ltrace</b> from Docker image:
- `docker run -t -i --privileged image_id /bin/bash`

## Setup instructions
- `echo "deb https://dl.bintray.com/olpotkin/OTUS-CPP-COURSE trusty main" | sudo tee -a /etc/apt/sources.list`
- `apt update && apt install -y allocator`
- `apt install ltrace`

In case of the error "<i>The method driver /usr/lib/apt/methods/https could not be found.</i>":
- `cd /usr/lib/apt/methods`
- `ln -s http https`

## Final check
- `ltrace -e malloc -e free allocator`
