FROM tudinfse/cds_server:latest
RUN apt update && apt upgrade -y
RUN apt install -y build-essential 

ADD ./mopp-2018-t0-harmonic-progression-sum /mopp-2018-t0-harmonic-progression-sum
RUN cd /mopp-2018-t0-harmonic-progression-sum && make

ADD ./mopp-2017-t3-mandelbrot-set /mopp-2017-t3-mandelbrot-set
RUN cd /mopp-2017-t3-mandelbrot-set && make

ADD ./mopp-2017-t4-k-means-clustering /mopp-2017-t4-k-means-clustering
RUN cd /mopp-2017-t4-k-means-clustering && make

COPY ./cds_server.json /etc/cds_server.json