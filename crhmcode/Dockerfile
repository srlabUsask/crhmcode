FROM ubuntu:18.04
RUN apt-get update
RUN apt-get install -y gcc
RUN apt-get install -y make
RUN apt-get install -y libboost-all-dev
COPY . /crhm
WORKDIR /crhm
RUN make
#ENTRYPOINT ./crhm
