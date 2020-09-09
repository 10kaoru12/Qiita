# 概要

dockerfileにshell関数を書きたいシュチュエーションがあったのでメモ

## エラーの発生したソースコード

```Dockerfile
RUN function sample(){
    yum install -y git \
    yum install -y httpd\
}
```

## 原因

;がない

## 対処したソースコード

```Dockerfile
RUN function sample(){
    yum install -y git; \
    yum install -y httpd;\
}
```

## 結論

一つ一つのコマンドを終了させる必要がある。

## 参考文献

- [Linuxコマンドを連続して使うには](https://qiita.com/egawa_kun/items/714394609eef6be8e0bf)