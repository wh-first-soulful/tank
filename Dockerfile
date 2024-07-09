FROM ubuntu:24.04
ENV DEBIAN FRONTEND=noninteractive
ENV TZ=Asia/Shanghai
RUN ln -fs /usr/share/zoneinfo/$TZ/etc/localtime
RUN echo $TZ > /etc/timezone 
RUN apt-get update 
RUN apt-get install -y tzdata
WORKDIR /app
RUN apt-get update 
RUN apt-get install -y build-essential 
RUN apt-get install -y qt6-base-dev
RUN apt-get install -y qt6-base-dev-tools 
RUN apt-get install -y qt6-charts-dev 
RUN apt-get install -y  libmysqlclient-dev 
RUN rm -rf /var/lib/apt/lists/*
COPY . /app
RUN qmake6 untitled.pro
RUN make
CMD ["bash"]
