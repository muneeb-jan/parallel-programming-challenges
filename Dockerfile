FROM tudinfse/cds_server:latest
RUN apt update && apt upgrade -y
RUN apt install -y build-essential 

ADD ./mopp-2018-t0-harmonic-progression-sum /mopp-2018-t0-harmonic-progression-sum
RUN cd /mopp-2018-t0-harmonic-progression-sum && make
COPY ./cds_server.json /etc/cds_server.json