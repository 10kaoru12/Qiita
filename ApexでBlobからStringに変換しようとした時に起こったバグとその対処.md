# 概要

ある文字列を暗号化してURLにパラメーターとして付与し、別ページでURLのパラメーターを受け取り復号化したいという状況

この際に、BLOb(Binary Large Object)からStringに変換する際、エンコード方式に制限があるようで、
「BLOB is not a valid UTF-8 string」
というエラーが出た。
その時の対処について記載する。

## エラーの発生したソースコード

```java
    Blob key=Crypto.generateAesKey(128);
    String encodedKey=key.toString();
    system.debug(encodedKey);
    Blob data=Blob.valueOf('00000');
    Blob encryptedData=Crypto.encryptWithManagedIV('AES128', key, data);
    String encodedEncryptedData=EncodingUtil.base64Encode(encryptedData);
    system.debug(encodedEncryptedData);
    Blob decodedEncryptedData=EncodingUtil.base64Decode(encodedEncryptedData);
    Blob decrypted=Crypto.decryptWithManagedIV('AES128', key, decodedEncryptedData);
    String toStringData=decrypted.toString();
    system.debug(toStringData);
```

## 原因部分

```java
    String encodedKey=key.toString();
```

## 対処したソースコード

```java
    Blob key=Crypto.generateAesKey(128);
    String encodedKey=EncodingUtil.base64Encode(key);
    system.debug(encodedKey);
    Blob data=Blob.valueOf('00000');
    Blob encryptedData=Crypto.encryptWithManagedIV('AES128', key, data);
    String encodedEncryptedData=EncodingUtil.base64Encode(encryptedData);
    system.debug(encodedEncryptedData);
    Blob decodedEncryptedData=EncodingUtil.base64Decode(encodedEncryptedData);
    Blob decrypted=Crypto.decryptWithManagedIV('AES128', key, decodedEncryptedData);
    String toStringData=decrypted.toString();
    system.debug(toStringData);
```

## 原因の推測

個人的には、generateAesKeyで生成されるBlob内にtoStringで変換するutf-8の形式に対応していない文字列が含まれているから変換できないのかな？と考えております。
Crypto.decryptWithManagedIVでdecryptoしたBlobをStringに変換することはできているので、generateAesKeyで生成されたBlobがutf-8で対応できない文字列を含んでいるのでできていないと考えました。
このエラーの原因がわかる方、推測できる方いらっしゃいましたらコメントなどで教えていただけると嬉しいです。

## 参考文献

- [How to deal with 'BLOB is not a valid UTF-8 string' error](https://developer.salesforce.com/forums/?id=906F00000008mCnIAI)
- [Getting error of 'BLOB is not a valid UTF-8 string'.](https://www.forcetalks.com/salesforce-topic/getting-error-of-blob-is-not-a-valid-utf-8-string/)
- [セキュリティを考慮した、可逆的暗号化の相互運用の仕組みを実現する方法(Salesforce編)](https://web.plus-idea.net/2017/04/salesforce-security-crypto/)