### INSTRUCTIONS ###
## Install docker:
    # $ snap install docker

## Create docker image:
    # $ docker build --tag proyecto1:latest .

## View docker images:
    # $ docker images

## Run tests:
    # $ docker run proyecto1:latest /usr/bin/run_unittest



# Define base OS
FROM ubuntu:20.04

#Define timezone
ENV TZ=America/Costa_Rica
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime \
    && echo $TZ > /etc/timezone

#Basic info
LABEL maintainers = "Ricardo Jiménez,Daniel Meseguer,Laura Rincón,Esteban Valverde"
LABEL version="1.0"
LABEL description = "Proyecto1 Docker Image for Unit Testing"

#Root and install required packages
USER root
RUN apt-get update \
    && apt-get --yes --no-install-recommends install \
        build-essential cmake libgtest-dev doxygen \
    && cd /usr/src/gtest/ \
    && cmake CMakeLists.txt \ 
    && make

#Make proyect dir
RUN mkdir -p /home/Proyecto1/

#Copy proyect directories
COPY include /home/Proyecto1/include
COPY src /home/Proyecto1/src
COPY test /home/Proyecto1/test
COPY debug /home/Proyecto1/debug
COPY doc /home/Proyecto1/doc
COPY CMakeLists.txt /home/Proyecto1/CMakeLists.txt
COPY Doxyfile /home/Proyecto1/Doxyfile
COPY README.md /home/Proyecto1/README.md

#Project creation (with documentation) and copy of executable
RUN cd /home/Proyecto1/ \
    && doxygen Doxyfile \
    && mkdir build \
    && cd build \
    && cmake .. \
    && make \
    && cp exe /usr/bin/run_unittest 

