# 概要

[ApexでBlobからStringに変換しようとした時に起こったバグとその対処](https://qiita.com/10kaoru12/items/1594a28f5e15b3e02c15)
の記事で紹介したようなバグが発生するため、暗号化したBlobをbase64形式でencodeしてURLパラメーターに付与する。
その後、別ページでパラメーターを受け取った際、encodeした文字列に「+」記号が含まれていると空白に変換されてしまうバグ（？）が発生したのでその時の対処について記述する。

## 問題が発生したソースコード

```java
    Blob key = Crypto.generateAesKey(128);
    // 暗号化する文字列「00000」
    Blob data = Blob.valueOf('00000');
    Blob encryptedData = Crypto.encryptWithManagedIV('AES128', key, data);
    String encodedEncryptedData = EncodingUtil.base64Encode(encryptedData);
```

## 対処したソースコード

```java
    Blob key = Crypto.generateAesKey(128);
    // 暗号化する文字列「00000」
    Blob data = Blob.valueOf('00000');
    Blob encryptedData = Crypto.encryptWithManagedIV('AES128', key, data);
    String encodedEncryptedData = EncodingUtil.base64Encode(encryptedData);

    // URLパラメーターをUTF-8でエンコード
    encodedEncryptedData = EncodingUtil.urlEncode(encodedEncryptedData, 'UTF-8');
```

## 原因

URLのパラメーターに追加する際はURLエンコードしないと無効な形式になってしまうようです。
URLパラメーターを弄るsalesforce開発者の方は注意して開発して欲しいです。

## 参考文献

- (URL parameter Issue while having '+' sign in the url
)[https://salesforce.stackexchange.com/questions/205344/url-parameter-issue-while-having-sign-in-the-url?noredirect=1]
- (Hash symbol when binding variables in URL)[https://salesforce.stackexchange.com/questions/4704/hash-symbol-when-binding-variables-in-url]