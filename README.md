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
在 example 的 config.txt 中放入邮箱和密码

#### 编译webserver
```
make example
```

#### 运行webserver
```
cd example
./WebServer
```

