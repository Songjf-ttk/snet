## snet

#### 安装依赖库
```
apt-get install build-essential cmake zlib1g-dev libssl-dev libgtest-dev libpoco-dev -y
```

#### 编译
```shell
cd snet
make
sudo make install
```

#### 配置
在 example/webserver/util.cc 的 SendEmail 函数中配置你的邮箱和密码

#### 编译webserver
```
make example
```

#### 运行webserver
```
cd example
./WebServer
```

